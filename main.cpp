#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include "SobolGenerator.hpp"

using namespace std;


int main() {
    int it = 20;
    unsigned dim = 4;
    unsigned discard = 100;
    chrono::system_clock::time_point t1, t2;
    t1 = chrono::system_clock::now();

    SobolGenerator gen(dim, discard, true, true);
    for (int d = 0; d < it; ++d) {
        vector<unsigned> next_vec = gen.get_next();
        cout << "Iteration " << d+1 << ": ";
        for (vector<unsigned>::size_type i = 0; i < next_vec.size(); ++i) {
            cout << next_vec[i] / (pow(2,SobolGenerator::bits)) << ' ';
        }
        cout << endl;
    }

    t2 = chrono::system_clock::now();
    chrono::duration<double> elapsed = t2 - t1;
    cout << "Time needed for " << it << " iterations and " << dim << " dimensions: " <<  elapsed.count() << endl;
    return 0;
}
