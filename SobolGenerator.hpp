#ifndef MATRAC_SOBOL_GENERATOR_HPP
#define MATRAC_SOBOL_GENERATOR_HPP

#include <string>
#include <vector>
#include <bitset>
#include <iostream>

using namespace std;

class SobolGenerator {
public:
    const static int bits = 32; // how many bits in an integer
private:
    unsigned dim;  // number of dimensions to be generated each draw
    unsigned draw;  // number of the draw
    unsigned discard;  // how many of the generated vectors to discard in the next draw
    vector< vector< bitset<bits> >> dir_int;  // vector containing direction numbers for each dimension
    vector< pair<unsigned, bitset<bits> >> polynomial;  // vector containing primitive polynomial modulo 2 for each
    // dimension
    vector<unsigned> previous_draw;  // vector containing the previous draw
    bool gray_code;  // determines whether to use gray code
    bool debug;  // determines whether to print debug messages
    void read_direction_integers(std::string);
    void set_first_dimension();
    void calculate_dimension_integers();
    bitset<bits> gamma();
    int bit_gray_code();
public:
    // constructor
    SobolGenerator(unsigned, unsigned, bool, bool);
    // destructor
    ~SobolGenerator();
    friend ostream& operator<<(ostream&, const SobolGenerator&);
    vector<unsigned> get_next();
};


#endif //MATRAC_SOBOL_GENERATOR_HPP
