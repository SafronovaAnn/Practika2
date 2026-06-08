#include "mod_inverse.h"
#include "extended_euclid.h"
#include <iostream>
using namespace std;
int modInverse(int c, int m) {
    int x, y;
    int g = extendedGcd(c, m, x, y);
    if (g != 1) return -1;
    int res = (x % m + m) % m;
    cout << c << "^{-1} mod " << m << " = " << res << endl;
    return res;
}