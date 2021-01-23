#include<iostream>
#include<vector>
#include"io.h"
#include"matrix.h"
#include"activation_functions.h"
#include"neural_network.h"

int main() {
	matrix mat_input = create_matrix_from_vector(read_csv("./data/input.csv"));
	matrix mat_target = create_matrix_from_vector(read_csv("./data/output.csv"));
	matrix result;

	neural_network net = create_neural_network(3, 4, 1, SIGMOID, SIGMOID);
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