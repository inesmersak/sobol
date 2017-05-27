#include <iostream>
#include <fstream>
#include <bitset>
#include <limits>
#include "SobolGenerator.hpp"

using namespace std;

SobolGenerator::SobolGenerator(unsigned dimension, unsigned m = 100, bool gcode = true, bool dbg_msg=false) {
    /*
     * The constructor for the SobolGenerator object. Initialises the vectors for direction integers and polynomials.
     *
     * Input:
     * dimension - Represents how many dimensions we want to generate with each draw.
     * dbg_msg - If this boolean is set to true, debug messages will print to the console.
     */
    dim = dimension;
    draw = 0;
    discard = m;
    gray_code = gcode;
    debug = dbg_msg;

    // initialisations
    for (int i=0; i < dim; ++i) {
        vector< bitset<bits> > i_dim;
        dir_int.push_back(i_dim);

        pair<unsigned, bitset<bits> > dim_p;
        polynomial.push_back(dim_p);
    }

    if(debug) {
        cout << "Constructing instance of SobolGenerator." << endl;
    }
}

SobolGenerator::~SobolGenerator() {
    /*
     * The destructor for the SobolGenerator object.
     */
    if(debug) {
        cout << "Destroying instance of SobolGenerator." << endl;
    }
}

bitset<SobolGenerator::bits> SobolGenerator::gamma() {
    return bitset<bits>(draw);
}

void SobolGenerator::read_direction_integers(string filename) {
    /*
     * Reads the initial direction integers and primitive polynomials from file and stores them in SobolGenerator
     * members.
     *
     * Input:
     * filename - The name of the file where the data is stored.
     */
    ifstream inpfile;
    inpfile.open(filename,ios::in);
    if (!inpfile.is_open()) {
        throw ios_base::failure("Cannot open file with direction integers");
    }
    inpfile.ignore(numeric_limits<streamsize>::max(), '\n');
    int d;
    unsigned s, a;
    for(int i = 2; i <= dim; ++i) {
        inpfile >> d >> s >> a;
        polynomial[d-1].first = s;
        polynomial[d-1].second = bitset<bits>(a);
        polynomial[d-1].second <<= 1;
        polynomial[d-1].second.set(0,1);
        unsigned cur;
        for(int j = 0; j < s; ++j) {
            inpfile >> cur;
            bitset<bits> b(cur);
            b <<= bits-1-j;
            dir_int[d-1].push_back(b);
        }
    }
    inpfile.close();
}

vector<unsigned> SobolGenerator::get_next() {
    /*
     * Gets the next vector in the draw.
     */
    if (draw == 0) {
        set_first_dimension();
        if (debug) cout << "Reading direction integers from file ..." << endl;
        try {
            read_direction_integers("direction_integers.txt");
        }
        catch (const ios_base::failure& failmsg) {
            cerr << failmsg.what() << endl;
            return vector<unsigned>(dim-1,0);
        }
        calculate_dimension_integers();
    }
    vector<unsigned> numbers;
    do {
        numbers.clear();
        if (!gray_code) {
            for(int k=0; k < dim; ++k) {
                if (draw < discard) break;
                bitset<bits> gam = gamma();
                bitset<bits> num;
                for(int j=0; j < bits; ++j) {
                    if (gam.none()) break;
                    if (gam[0]) {
                        num ^= dir_int[k][j];
                    }
                    gam >>= 1;
                }
                numbers.push_back(static_cast<unsigned>(num.to_ulong()));
            }
        } else {
            for (int k=0; k < dim; ++k) {
                if (draw == 0) {
                    numbers.push_back(0);
                } else {
                    int bit = bit_gray_code();
                    numbers.push_back(static_cast<unsigned> ((bitset<bits>(previous_draw[k]) ^ dir_int[k][bit]).to_ulong
                            ()));
                }
            }
            previous_draw = numbers;
        }
        ++draw;
    } while (draw <= discard);
    return numbers;
}

ostream& operator<<(ostream& output, const SobolGenerator& Sob) {
    for(int i = 0; i < Sob.dim; ++i) {
        output << "dim " << i+1 << ": " << endl;
        output << "direction integers: ";
        for(int j = 0; j < Sob.dir_int[i].size(); ++j) {
            output << Sob.dir_int[i][j] << " ";
        }
        output << endl;
        output << "polynomial: degree " << Sob.polynomial[i].first << ", coefficients: " << Sob.polynomial[i].second
               << endl;
    }
    return output;
}

void SobolGenerator::set_first_dimension() {
    polynomial[0].first = 0;
    polynomial[0].second = bitset<bits>(0);
}

void SobolGenerator::calculate_dimension_integers() {
    for(int k = 0; k < dim; ++k) {
        unsigned pdeg = polynomial[k].first;
        for(unsigned l = pdeg; l < bits; ++l) {
            bitset<bits> v(0);
            if (k == 0) {
                v.set(bits-1-l,1);
                dir_int[k].push_back(v);
                continue;
            }
            v = dir_int[k][l-pdeg] >> pdeg;
            for (int j = 1; j <= pdeg; ++j) {
                if (polynomial[k].second[pdeg-j]) {
                    v ^= dir_int[k][l-j];
                }
            }
            dir_int[k].push_back(v);
        }
    }
}

int SobolGenerator::bit_gray_code(void) {
    bitset<bits> n(draw-1);
    int i;
    for(i=0; i < bits; ++i) {
        if (n[i]) break;
    }
    return i;
}
