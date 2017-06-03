#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>
#include "SobolGenerator.hpp"

using namespace std;


int main() {
    int it = 20000000;  // the number of vectors to generate
    unsigned dim = 4;  // the dimensionality of the vector to be generated
    unsigned discard = 100;  // how many of the initial draws to discard

    // we begin to time the vector generation
    chrono::system_clock::time_point t1, t2;
    t1 = chrono::system_clock::now();

    SobolGenerator gen(dim, discard, true, false);
    for (int d = 0; d < it; ++d) {
        // GENERATION
        vector<unsigned> next_vec = gen.get_next();

        // OUTPUT
//        cout << setprecision(12);  // sets precision of the output
//        cout << "Iteration " << d+1 << ": ";
//        for (vector<unsigned>::size_type i = 0; i < next_vec.size(); ++i) {
//            cout << next_vec[i] / (pow(2,SobolGenerator::bits)) << ' ';
//        }
//        cout << endl;
    }

    t2 = chrono::system_clock::now();  // we stop the clock
    chrono::duration<double> elapsed = t2 - t1;  // calculation of the duration needed for the generation
    cout << "Time needed for " << it << " iterations and " << dim << " dimensions: " <<  elapsed.count() << endl;
    return 0;
}
