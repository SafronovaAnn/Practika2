#ifndef UTILS_H
#define UTILS_H

#include <string>

std::string readFile(const std::string& filename);
void writeFile(const std::string& filename, const std::string& data);

#endif