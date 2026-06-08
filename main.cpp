#include <iostream>
#include "fermat.h"
#include "extended_euclid.h"
#include "mod_inverse.h"
#include "shamir.h"
#include "utils.h"

using namespace std;

enum class MenuChoice {
    COMPARISON_BY_MODULE_1 = 1,
    EXTENDED_EUCLID_2 = 2,
    MOD_INVERSE_3 = 3,
    SHAMIR_4 = 4,
    MITM_5 = 5,
    EQUATION_6 = 6,
    EXIT = 0
};

int main() {
    int choice;
    
    do {
        cout << "   Практическая работа №2" << endl;
        cout << "1. a^x mod p (Ферма + бинарный)" << endl;
        cout << "2. Расширенный алгоритм Евклида" << endl;
        cout << "3. Обратный элемент по модулю" << endl;
        cout << "4. Протокол Шамира" << endl;
        cout << "5. Атака 'Человек посередине' (MITM)" << endl;
        cout << "6. Диофантово уравнение 275x + 145y = D" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите задание: ";
        cin >> choice;
        
        MenuChoice menuChoice = static_cast<MenuChoice>(choice);
        
        switch (menuChoice) {
            case MenuChoice::COMPARISON_BY_MODULE_1: {
                int a, x, p;
                cout << "\n=== Задание 1: a^x mod p ===" << endl;
                cout << "Введите a, x, p: ";
                cin >> a >> x >> p;
                
                if (isPrime(p)) {
                    cout << "p = " << p << " — простое число" << endl;
                    modPowFermat(a, x, p);
                } else {
                    cout << "p = " << p << " — не простое (теорема Ферма не применима)" << endl;
                }
                modPowBinary(a, x, p);
                break;
            }
            case MenuChoice::EXTENDED_EUCLID_2: {
                int a, b, x, y;
                cout << "\n=== Задание 2: Расширенный алгоритм Евклида ===" << endl;
                cout << "Введите a и b: ";
                cin >> a >> b;
                extendedGcd(a, b, x, y);
                break;
            }
            case MenuChoice::MOD_INVERSE_3: {
                int c, m;
                cout << "\n=== Задание 3: Обратный элемент по модулю ===" << endl;
                cout << "Введите c и m: ";
                cin >> c >> m;
                int inv = modInverse(c, m);
                if (inv != -1) {
                    cout << "Обратный элемент: " << inv << endl;
                }
                break;
            }
            case MenuChoice::SHAMIR_4: {
                int subChoice;
                cout << "\n=== Задание 4: Протокол Шамира ===" << endl;
                cout << "1. Шифрование числа" << endl;
                cout << "2. Шифрование файла" << endl;
                cout << "3. Расшифрование файла" << endl;
                cout << "Выберите режим: ";
                cin >> subChoice;
                
                if (subChoice == 1) {
                    int p, Ca, Cb, msg;
                    cout << "Введите p, Ca, Cb, сообщение: ";
                    cin >> p >> Ca >> Cb >> msg;
                    int result = shamirEncryptNumber(msg, p, Ca, Cb);
                    if (result != -1) {
                        cout << "\nРасшифрованное сообщение: " << result << endl;
                    }
                }
                else if (subChoice == 2) {
                    string inputFile, outputFile;
                    int p, Ca, Cb;
                    cout << "Входной файл: ";
                    cin >> inputFile;
                    cout << "Выходной файл: ";
                    cin >> outputFile;
                    cout << "Введите p, Ca, Cb: ";
                    cin >> p >> Ca >> Cb;
                    encryptFileShamir(inputFile, outputFile, p, Ca, Cb);
                }
                else if (subChoice == 3) {
                    string inputFile, outputFile;
                    cout << "Зашифрованный файл: ";
                    cin >> inputFile;
                    cout << "Выходной файл: ";
                    cin >> outputFile;
                    decryptFileShamir(inputFile, outputFile);
                }
                break;
            }
            case MenuChoice::MITM_5: {
                cout << "\n=== Задание 5: Атака 'Человек посередине' (MITM) ===" << endl;
                cout << "   на протокол Шамира" << endl;

                int p = 23;
                cout << "\n1. Открытые параметры:" << endl;
                cout << "   p = " << p << " (простое число)" << endl;

                int Ca = 7, Cb = 5;
                int da = modInverse(Ca, p - 1);
                int db = modInverse(Cb, p - 1);

                cout << "\n2. Законные стороны:" << endl;
                cout << "   Алиса: Ca = " << Ca << ", da = " << da << endl;
                cout << "   Боб:   Cb = " << Cb << ", db = " << db << endl;

                int m = 10;
                cout << "\n3. Алиса хочет передать Бобу сообщение: m = " << m << endl;

                cout << "\n   Обычный протокол (без атаки)" << endl;

                int x1 = modPowBinary(m, Ca, p);
                cout << "   Алиса → Боб: x1 = " << m << "^" << Ca << " mod " << p << " = " << x1 << endl;

                int x2 = modPowBinary(x1, Cb, p);
                cout << "   Боб → Алиса: x2 = " << x1 << "^" << Cb << " mod " << p << " = " << x2 << endl;

                int x3 = modPowBinary(x2, da, p);
                cout << "   Алиса → Боб: x3 = " << x2 << "^" << da << " mod " << p << " = " << x3 << endl;

                int dec = modPowBinary(x3, db, p);
                cout << "   Боб расшифровал: dec = " << dec << endl;

                cout << "\n   Атака MITM (Ева перехватывает сообщения)" << endl;

                int Ce1 = 3, Ce2 = 9;
                int de1 = modInverse(Ce1, p - 1);
                int de2 = modInverse(Ce2, p - 1);

                cout << "\nЕва выбирает свои ключи:" << endl;
                cout << "   Для связи с Алисой: Ce1 = " << Ce1 << ", de1 = " << de1 << endl;
                cout << "   Для связи с Бобом:   Ce2 = " << Ce2 << ", de2 = " << de2 << endl;

                int m1 = modPowBinary(m, Ca, p);
                cout << "\nШаг 1 (Алиса → Ева):   m1 = " << m << "^" << Ca << " mod " << p << " = " << m1 << endl;

                int m_decrypted = modPowBinary(m1, de1, p);
                cout << "   Ева расшифровала:   m = " << m1 << "^" << de1 << " mod " << p << " = " << m_decrypted << endl;

                int m1_fake = modPowBinary(m_decrypted, Ce2, p);
                cout << "   Ева → Боб (подмена): m1' = " << m_decrypted << "^" << Ce2 << " mod " << p << " = " << m1_fake << endl;

                int m2 = modPowBinary(m1_fake, Cb, p);
                cout << "\nШаг 2 (Боб → Ева):     m2 = " << m1_fake << "^" << Cb << " mod " << p << " = " << m2 << endl;

                int m2_decrypted = modPowBinary(m2, de2, p);
                cout << "   Ева расшифровала:   m2' = " << m2 << "^" << de2 << " mod " << p << " = " << m2_decrypted << endl;

                int m2_fake = modPowBinary(m2_decrypted, Ce1, p);
                cout << "   Ева → Алиса (подмена): m2' = " << m2_decrypted << "^" << Ce1 << " mod " << p << " = " << m2_fake << endl;

                int m3 = modPowBinary(m2_fake, da, p);
                cout << "\nШаг 3 (Алиса → Ева):   m3 = " << m2_fake << "^" << da << " mod " << p << " = " << m3 << endl;

                int m3_decrypted = modPowBinary(m3, de1, p);
                cout << "   Ева расшифровала:   m3' = " << m3 << "^" << de1 << " mod " << p << " = " << m3_decrypted << endl;

                int m3_fake = modPowBinary(m3_decrypted, de2, p);
                cout << "   Ева → Боб (подмена): m3' = " << m3_decrypted << "^" << de2 << " mod " << p << " = " << m3_fake << endl;

                int final_dec = modPowBinary(m3_fake, db, p);
                cout << "\nШаг 4 (Боб расшифровал): dec = " << m3_fake << "^" << db << " mod " << p << " = " << final_dec << endl;

                cout << "\n================================================" << endl;
                cout << "   Результат атаки" << endl;
                cout << "   Алиса отправила:   " << m << endl;
                cout << "   Ева прочитала:     " << m_decrypted << endl;
                cout << "   Боб получил:       " << final_dec << endl;
                cout << "\n   Вывод: Ева успешно перехватила и прочитала сообщение!" << endl;
                cout << "   Алиса и Боб даже не подозревают об атаке." << endl;
                break;
            }
            case MenuChoice::EQUATION_6: {
                int D, x0, y0;
                cout << "\n=== Задание 6: Диофантово уравнение 275x + 145y = D ===" << endl;
                cout << "Введите D: ";
                cin >> D;
                
                int g = extendedGcd(275, 145, x0, y0);
                
                if (D % g != 0) {
                    cout << "Решений нет, так как " << D << " не делится на " << g << endl;
                } else {
                    int x = x0 * (D / g);
                    int y = y0 * (D / g);
                    cout << "x = " << x << ", y = " << y << endl;
                    cout << "Проверка: 275*" << x << " + 145*" << y << " = " << (275 * x + 145 * y) << endl;
                }
                break;
            }
            case MenuChoice::EXIT:
                cout << "Выход" << endl;
                break;
            default:
                cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);
    
    return 0;
}