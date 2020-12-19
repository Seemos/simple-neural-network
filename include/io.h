#ifndef IO_H
#define IO_H

#include <vector>
#include <string>
#include <sstream>

std::vector<std::vector<long double>> read_csv(const char* input_file, char delimiter = ',');
void write_csv(std::vector<std::vector<long double>> values, const char* output_file, char delimiter = ',');

#endif // !IO_H