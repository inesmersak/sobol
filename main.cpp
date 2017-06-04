#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <functional>
#include "SobolGenerator.hpp"

using namespace std;

chrono::duration<double> time_generation(int N, unsigned D, unsigned disc, bool G, bool output) {
    chrono::system_clock::time_point t1, t2;
    chrono::duration<double> elapsed;
    t1 = chrono::system_clock::now();

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

    t2 = chrono::system_clock::now();  // we stop the clock
    elapsed = t2 - t1;  // calculation of the duration needed for the generation
    return elapsed;
}

double monte_carlo(function<double(double, double)> f, int N, pair<double,double> beg, pair<double,double> end) {
    unsigned discard = 100;
    double xlen = end.first-beg.first;
    double ylen = end.second - beg.second;
    double volume = xlen * ylen;
    SobolGenerator sob(2, discard, true, false);
    double sum = 0;
    vector<double> draw;
    for (int i = 0; i < N; ++i) {
        draw = sob.get_next();
        if (draw.size() < 2) {
            cerr << "Something went wrong, vector was not generated.";
            return 0;
        }
        draw[0] = draw[0] * xlen + beg.first;
        draw[1] = draw[1] * ylen + beg.second;
        sum += f(draw[0],draw[1]);
    }
    return volume / N * sum;
}

int main() {
    int it = 20000000;  // the number of vectors to generate
    unsigned dim = 4;  // the dimensionality of the vector to be generated
    unsigned discard = 100;  // how many of the initial draws to discard

    chrono::duration<double> time =  time_generation(it, dim, discard, true, false);
    cout << setprecision(12);
    cout << "Time needed for " << it << " iterations and " << dim << " dimensions: " << time.count() << endl;
    return 0;
}
