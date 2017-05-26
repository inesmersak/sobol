#include <iostream>
#include "SobolGenerator.hpp"

using namespace std;

int main() {
    SobolGenerator gen(4, true);
    gen.get_next();
    gen.get_next();
    cout << gen;
    return 0;
}
