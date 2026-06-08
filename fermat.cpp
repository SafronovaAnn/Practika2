#include "fermat.h"
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int modPowFermat(int a, int x, int p) {
    cout << "\n=== АЛГОРИТМ 1: ТЕОРЕМА ФЕРМА ===" << endl;
    
    if (!isPrime(p)) {
        cerr << "Ошибка: p = " << p << " не простое!" << endl;
        return -1;
    }
    
    int base = a % p;
    if (base < 0) base += p;
    
    if (base == 0) {
        cout << "Основание кратно p → результат: 0" << endl;
        return 0;
    }
    
    int exp = x % (p - 1);
    int res = 1;
    
    cout << "По теореме Ферма: " << a << "^" << x << " mod " << p 
         << " = " << base << "^(" << x << " mod " << (p-1) << ") = " << base << "^" << exp << endl;
    cout << "Вычисляем " << base << "^" << exp << " mod " << p << ":\n";
    
    for (int i = 0; i < exp; i++) {
        res = (res * base) % p;
        cout << "  шаг " << (i + 1) << ": " << base << "^" << (i + 1) << " mod " << p << " = " << res << endl;
    }
    cout << "Результат (Ферма): " << res << endl;
    return res;
}

int modPowBinary(int a, int b, int p) {
    if (p == 1) return 0;
    int result = 1;
    int base = a % p;
    int exp = b;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % p;
        base = (base * base) % p;
        exp >>= 1;
    }
    return result;
}
