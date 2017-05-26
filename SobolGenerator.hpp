#ifndef MATRAC_SOBOL_GENERATOR_HPP
#define MATRAC_SOBOL_GENERATOR_HPP

#include <string>
#include <vector>
#include <bitset>
#include <iostream>

using namespace std;

class SobolGenerator {
private:
    const static int bits = 32;
    int dim;
    int draw;
    vector< vector< bitset<bits> >> dir_int;
    vector< pair<unsigned, bitset<bits> >> polynomial;
    bool debug;
    void set_first_dimension();
    void read_direction_integers(std::string filename);
    int gamma();
    void calculate_dimension_integers();
public:
    // constructor
    SobolGenerator(int dimension, bool dbg_msg);
    // destructor
    ~SobolGenerator();
    friend ostream& operator<<(ostream& output, const SobolGenerator& Sob);
    int get_next();
};


#endif //MATRAC_SOBOL_GENERATOR_HPP
