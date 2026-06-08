#include "shamir.h"
#include "fermat.h"
#include "mod_inverse.h"
#include "utils.h"
#include <iostream>
#include <fstream>

using namespace std;

int shamirEncryptNumber(int message, int p, int Ca, int Cb) {
    cout << "\n=== Протокол Шамира (число) ===" << endl;
    cout << "Исходное сообщение: " << message << endl;
    cout << "p = " << p << ", Ca = " << Ca << ", Cb = " << Cb << endl;

    int da = modInverse(Ca, p - 1);
    int db = modInverse(Cb, p - 1);

    if (da == -1 || db == -1) return -1;

    cout << "da = " << da << ", db = " << db << endl;

    int x1 = modPowBinary(message, Ca, p);
    cout << "x1 = " << message << "^" << Ca << " mod " << p << " = " << x1 << endl;

    int x2 = modPowBinary(x1, Cb, p);
    cout << "x2 = " << x1 << "^" << Cb << " mod " << p << " = " << x2 << endl;

    int x3 = modPowBinary(x2, da, p);
    cout << "x3 = " << x2 << "^" << da << " mod " << p << " = " << x3 << endl;

    int dec = modPowBinary(x3, db, p);
    cout << "dec = " << x3 << "^" << db << " mod " << p << " = " << dec << endl;

    return dec;
}

void encryptFileShamir(const string& inputFile, const string& outputFile, int p, int Ca, int Cb) {
    string data = readFile(inputFile);
    if (data.empty()) {
        cerr << "Ошибка: файл " << inputFile << " пуст" << endl;
        return;
    }

    int da = modInverse(Ca, p - 1);
    if (da == -1) {
        cerr << "Ошибка: невозможно вычислить da" << endl;
        return;
    }

    cout << "\n=== Шифрование файла ===" << endl;
    cout << "p = " << p << ", Ca = " << Ca << ", Cb = " << Cb << ", da = " << da << endl;

    ofstream out(outputFile);
    out << p << " " << Ca << " " << Cb << endl;

    for (unsigned char ch : data) {
        int m = (int)ch;
        int x1 = modPowBinary(m, Ca, p);
        int x2 = modPowBinary(x1, Cb, p);
        int x3 = modPowBinary(x2, da, p);
        out << x3 << " ";
    }
    out.close();
    cout << "Файл зашифрован: " << outputFile << endl;
}

void decryptFileShamir(const string& inputFile, const string& outputFile) {
    ifstream in(inputFile);
    if (!in.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << inputFile << endl;
        return;
    }

    int p, Ca, Cb;
    in >> p >> Ca >> Cb;

    int db = modInverse(Cb, p - 1);
    if (db == -1) {
        cerr << "Ошибка: невозможно вычислить db" << endl;
        return;
    }

    cout << "\n=== Расшифрование файла ===" << endl;
    cout << "p = " << p << ", Cb = " << Cb << ", db = " << db << endl;

    string decrypted;
    int x3;
    while (in >> x3) {
        int dec = modPowBinary(x3, db, p);
        decrypted.push_back((char)dec);
    }
    in.close();

    writeFile(outputFile, decrypted);
    cout << "Файл расшифрован: " << outputFile << endl;
}