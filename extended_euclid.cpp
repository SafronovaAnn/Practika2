#include "extended_euclid.h"
#include <iostream>
using namespace std;

int extendedGcd(int a, int b, int& x, int& y) {
    int r0 = a, r1 = b, r2;
    int u0 = 1, u1 = 0, u2;
    int v0 = 0, v1 = 1, v2;
    int q;
    
    cout << "Расширенный алгоритм Евклида для " << a << " и " << b << endl;
    
    while (r1 != 0) {
        q = r0 / r1;
        r2 = r0 - q * r1;
        u2 = u0 - q * u1;
        v2 = v0 - q * v1;
        
        cout << "  q = " << q << ", r2 = " << r2 << ", u2 = " << u2 << ", v2 = " << v2 << endl;
        
        r0 = r1; r1 = r2;
        u0 = u1; u1 = u2;
        v0 = v1; v1 = v2;
    }
    
    x = u0;
    y = v0;
    return r0;
}