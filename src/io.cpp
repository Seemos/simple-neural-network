#include "io.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

std::vector<std::vector<long double>> read_csv(const char* input_file, char delimiter) {
	std::ifstream input_stream(input_file);
	std::stringstream line_stream;
	std::string line;
	std::string value;
	std::vector<std::vector<long double>> output;
	char* p_end;

	while (std::getline(input_stream, line)) {
		line_stream = std::stringstream(line);
		std::vector<long double> line_values;
		while (std::getline(line_stream, value, delimiter)) {
			line_values.push_back( std::strtold(value.data(), &p_end) );
		}
		output.push_back(line_values);
	}

	return output;
}

void write_csv(std::vector<std::vector<long double>> values, const char* output_file, char delimiter) {
	std::ofstream output_stream(output_file);
	for (unsigned i = 0; i < values.size(); ++i) {
		for (unsigned j = 0; j < values[i].size(); ++j) {
			output_stream << values[i][j];
			if (j != (values[i].size() - 1)) output_stream << delimiter;
		}
		output_stream << "\n";
	}
}