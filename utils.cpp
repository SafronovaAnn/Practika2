#include "utils.h"
#include <fstream>
#include <iostream>
using namespace std;

string readFile(const string& filename) {
    ifstream f(filename, ios::binary);
    if (!f.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        return "";
    }
    string content((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
    f.close();
    return content;
}

void writeFile(const string& filename, const string& data) {
    ofstream f(filename, ios::binary);
    if (!f.is_open()) {
        cerr << "Ошибка: не удалось записать файл " << filename << endl;
        return;
    }
    f << data;
    f.close();
}