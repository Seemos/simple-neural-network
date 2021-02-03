#include<iostream>
#include<vector>
#include"io.h"
#include"matrix.h"
#include"activation_functions.h"
#include"neural_network.h"
#include"layered_network.h"

int main() {
	matrix mat_input = create_matrix_from_vector(read_csv("./data/input.csv"));
	matrix mat_target = create_matrix_from_vector(read_csv("./data/output.csv"));
	matrix result;

	layered_network net = create_layered_network(3,1, SIGMOID);
	add_hidden_layer(net, 4, SIGMOID);
	build_layered_network(net);

	for (unsigned i = 0; i < 100; i++)
	{
		train_layered_network(net, mat_input, mat_target, 0.1);
	}

	print_matrix(query_layered_network(net, mat_input));
	
	printf("----------Input------------\n");
	print_matrix(mat_input);
	printf("----------Target-----------\n");
	print_matrix(mat_target);
	printf("----------Result-----------\n");
	print_matrix(query_layered_network(net, mat_input));
}