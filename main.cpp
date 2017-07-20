#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <functional>
#include <random>
#include "SobolGenerator.hpp"

using namespace std;

chrono::duration<double> time_generation(int N, unsigned D, unsigned disc, bool G, bool output) {
    /*
     * Returns the time needed to generate N D-dimensional vectors, discarding the first disc.
     *
     * Input:
     * N - The number of vectors (draws) to be generated.
     * D - The dimensionality of the vectors to be generated.
     * disc - The first disc vectors are to be discarded.
     * G - If set to true, gray code is used to generate.
     * output - If set to true, vectors generated are printed to the standard output.
     *
     * Output:
     * elapsed - The time (in seconds) we needed in order to generate N D-dimensional vectors.
     */
    chrono::system_clock::time_point t1, t2;
    chrono::duration<double> elapsed;
    t1 = chrono::system_clock::now();  // we start timing

    SobolGenerator gen(D, disc, G, false);
    for (int d = 0; d < N; ++d) {
        // GENERATION
        vector<double> next_vec = gen.get_next();
        if (next_vec.size() < D) {
            cerr << "Something went wrong, vector was not generated." << endl;
            return elapsed;
        }

        // OUTPUT
        if (output) {
            cout << setprecision(12);  // sets precision of the output
//            cout << "Iteration " << d+1 << ": ";
            for (vector<double>::size_type i = 0; i < next_vec.size(); ++i) {
                cout << next_vec[i] << ' ';
            }
            cout << endl;
        }
    }

    t2 = chrono::system_clock::now();  // we stop timing
    elapsed = t2 - t1;  // calculation of the duration needed for the generation
    return elapsed;
}

void test_time(unsigned D, unsigned disc, bool G) {
    /*
     * Times generation for certain Ns (where N is the number of vectors to be generated) that are equally spaced on
     * in the log scale in order to prepare data for a loglog plot. Prints time needed for each N to standard output.
     *
     * Input:
     * D - The dimensionality of the vectors to be generated.
     * disc - The first disc vectors are to be discarded.
     * G - If set to true, gray code is used to generate.
     */
    vector<unsigned> Ns {101,133,176,233,309,410,543,720,955,1265,1677,2223,2948,3907,5180,6867,9103,12068,15999,21210,
                         28118,37276,49418,65513,86852,115140,152642,202359,268270,355649,471487,625056,828643,1098542,
                         1456349,1930698,2559548,3393222,4498433,5963624,7906044,10481132,13894955,18420700,24420531,
                         32374576,42919343,56898661,75431201,100000000};

    cout << setprecision(12);
    for (int i = 0; i < Ns.size(); ++i) {
        chrono::duration<double> time =  time_generation(Ns[i], D, disc, G, false);
        cout << Ns[i] << ' ' << time.count() << endl;
    }
}

double monte_carlo(function<double(double, double)> f, int N, pair<double,double> beg, pair<double,double> end, bool
quasi) {
    /*
     * Monte Carlo integration method.
     *
     * Input:
     * f - A two-dimensional function to integrate.
     * N - Number of samples.
     * beg - The beginning point of the area that we are integrating on.
     * end - The ending point of the area that we are integrating on.
     * quasi - If set to true, Sobol generator is used to generate points. Otherwise, a Mersenne twister is used.
     *
     * Output:
     * An approximation of the integral of f over the rectangle given by beg and end.
     */
    unsigned discard = 100;
    double xlen = end.first-beg.first;  // the length of the interval in the direction x
    double ylen = end.second - beg.second;  // the length of the interval in the direction y
    double volume = xlen * ylen;  // volume of our area (rectangle)

    // for quasi-random Monte Carlo
    SobolGenerator sob(2, discard, true, false);

    // for pseudo-random Monte Carlo
    mt19937 gen(42);
    uniform_real_distribution<double> distr(0.0,1.0);

    double sum = 0;
    vector<double> draw(2);
    for (int i = 0; i < N; ++i) {
        if (quasi) {
            draw = sob.get_next();
        } else {
            draw[0] = distr(gen);
            draw[1] = distr(gen);
        }
        if (draw.size() < 2) {
            cerr << "Something went wrong, vector was not generated.";
            return 0;
        }
        // we scale the coordinates appropriately according to out rectangle
        draw[0] = draw[0] * xlen + beg.first;
        draw[1] = draw[1] * ylen + beg.second;

        sum += f(draw[0],draw[1]);
    }
    return volume / N * sum;
}

double f (double x, double y) {
    /*
     * The two-dimensional function to use for testing Monte Carlo integration.
     */
//    return x+y;
    return sin(10 * pow(x,2) * (1-y));
}

void test_monte_carlo() {
    /*
     * Prints the approximation of the integral of f to standard output for certain sample sizes N that are equally
     * spaced on in the log scale in order to prepare data for a loglog plot.
     */
    vector<unsigned> Ns {11,14,18,24,31,41,55,72,96,127,168,223,295,391,518,687,911,1207,1600,2121,2812,3728,4942,
                         6552,8686,11514,15265,20236,26827,35565,47149,62506,82865,109855,145635,193070,2555955,
                         339323,449844,596363,790605,1048114,1389496,1842070,2442054,3237458,4291935,5689867,7543121,
                         10000000};
    cout << setprecision(12);
    for (int i = 0; i < Ns.size(); ++i){
        cout << Ns[i] << " ";
//        cout << "Quasi-random Monte Carlo: ";
        cout << monte_carlo(f, Ns[i], pair<double, double>(0,0), pair<double, double>(1,1), true) << " ";
//        cout << "Pseudo-random Monte Carlo: ";
        cout << monte_carlo(f, Ns[i], pair<double, double>(0,0), pair<double, double>(1,1), false) << endl;
    }
}


int main() {
    unsigned dim = 4;  // the dimensionality of the vector to be generated
    unsigned discard = 100;  // how many of the initial draws to discard

    int it = 20000000;  // the number of vectors to generate
    chrono::duration<double> time =  time_generation(it, dim, discard, true, false);
    cout << "Time needed for " << it << " iterations and " << dim << " dimensions: " << time.count() << endl;

//    test_time(dim, discard, true);
//    test_monte_carlo();

    return 0;
}
