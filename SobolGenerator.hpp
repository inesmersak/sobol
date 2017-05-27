#ifndef MATRAC_SOBOL_GENERATOR_HPP
#define MATRAC_SOBOL_GENERATOR_HPP

#include <string>
#include <vector>
#include <bitset>
#include <iostream>

using namespace std;

class SobolGenerator {
public:
    const static int bits = 32;
private:
    unsigned dim;
    unsigned draw;
    unsigned discard;
    vector< vector< bitset<bits> >> dir_int;
    vector< pair<unsigned, bitset<bits> >> polynomial;
    vector<unsigned> previous_draw;
    bool gray_code;
    bool debug;
    void set_first_dimension();
    void read_direction_integers(std::string);
    bitset<bits> gamma(void);
    int bit_gray_code(void);
    void calculate_dimension_integers(void);
public:
    // constructor
    SobolGenerator(unsigned, unsigned, bool, bool);
    // destructor
    ~SobolGenerator(void);
    friend ostream& operator<<(ostream&, const SobolGenerator&);
    vector<unsigned> get_next(void);
};


#endif //MATRAC_SOBOL_GENERATOR_HPP
