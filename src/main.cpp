#include<iostream>
#include<vector>
#include"matrix.h"
#include"activation_functions.h"
#include"neural_network.h"

std::vector<std::vector<long double>> input = {
	{0,0,0},
	{1,0,0},
	{1,0,1},
	{1,1,0},
};

std::vector<std::vector<long double>> output = {
	{0},
	{0},
	{1},
	{1}
};


int main() {
	matrix mat_input = create_matrix_from_vector(input);
	matrix mat_target = create_matrix_from_vector(output);
	matrix result;

	neural_network net = create_neural_network(3, 4, 1);

	printf("The untrained predictions:\n");
	result = query_neural_network(net, mat_input);
	print_matrix(result);

	printf("Starting training...\n");
	for (unsigned i = 0; i < 1000; i++) {
		train_neural_network(net, mat_input, mat_target, 1);
	}

	printf("The values should be 0,0,1,1\n");
	result = query_neural_network(net, mat_input);
	print_matrix(result);

	printf("Saving the net to a file\n");
	save_neural_network(net, "net.dat");

	printf("Create a copy of the net from a file\n");
	neural_network net_loaded = load_neural_network("net.dat");

	printf("Query copied net\n");
	print_matrix(query_neural_network(net, mat_input));
}