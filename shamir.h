#ifndef SHAMIR_H
#define SHAMIR_H

#include <string>

int shamirEncryptNumber(int message, int p, int Ca, int Cb);
void encryptFileShamir(const std::string& inputFile, const std::string& outputFile, int p, int Ca, int Cb);
void decryptFileShamir(const std::string& inputFile, const std::string& outputFile);

#endif