#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "neural_network.h"
#include "activation_functions.h"
#include "matrix.h"

neural_network create_neural_network(unsigned size_input, unsigned size_hidden, unsigned size_output, unsigned function_hidden, unsigned function_output) {
	neural_network net;
	net.synapses_ih = create_random_matrix(size_input, size_hidden);
	net.synapses_ho = create_random_matrix(size_hidden, size_output);
	net.activation_hidden = activations[function_hidden];
	net.activation_output = activations[function_output];
	net.derivative_hidden = derivatives[function_hidden];
	net.derivative_output = derivatives[function_output];
	return net;
}

void train_neural_network(neural_network& net, const matrix& input, const matrix& target, long double learning_rate) {
	//input layer
	net.layer_input = input;

	//calculate the hidden layer
	net.layer_hidden = dot(net.layer_input, net.synapses_ih);
	net.layer_hidden = apply_function(net.layer_hidden, net.activation_hidden);

	//calculate the output layer
	net.layer_output = dot(net.layer_hidden, net.synapses_ho);
	net.layer_output = apply_function(net.layer_output, net.activation_output);

	//backpropagating the output layer
	net.error_output = target - net.layer_output;
	net.delta_output = net.error_output * apply_function(net.error_output, net.derivative_output);

	//backpropagating the hidden layer
	net.error_hidden = dot(net.delta_output, transpose(net.synapses_ho));
	net.delta_hidden = net.error_hidden * apply_function(net.error_hidden, net.derivative_hidden);

	//adjusting the weights
	net.synapses_ho += dot(transpose(net.layer_hidden), net.delta_output) * learning_rate;
	net.synapses_ih += dot(transpose(net.layer_input), net.delta_hidden) * learning_rate;
}

matrix query_neural_network(neural_network& net, const matrix& input) {
	//input layer
	net.layer_input = input;

	//calculate the hidden layer
	net.layer_hidden = dot(net.layer_input, net.synapses_ih);
	net.layer_hidden = apply_function(net.layer_hidden, sigmoid);

	//calculate the output layer
	net.layer_output = dot(net.layer_hidden, net.synapses_ho);
	net.layer_output = apply_function(net.layer_output, sigmoid);

	//returning the calculated values
	return net.layer_output;
}

long double get_error(neural_network& net, const matrix& input, const matrix& target){
	matrix mat_error =  target - query_neural_network(net, input);
	long double error = 0;
	for(unsigned i = 0; i < mat_error.n_rows; i++){
		for(unsigned j = 0; j < mat_error.n_cols; j++){
			error += pow(mat_error.values[i][j], 2);
		}
	}
	error/=(mat_error.n_cols*mat_error.n_rows);
	return error;
}

void save_neural_network(neural_network& net, const char* file_path) {
	FILE* output;
	output = fopen(file_path, "wb");
	if(!output) {
		std::cerr << "Error: could not open file " << file_path << std::endl;
		exit(1);
	}
	fwrite(&net, sizeof(&net), 1, output);
	fclose(output);
}

neural_network load_neural_network(const char* file_path) {
	neural_network net;
	FILE* input;
	input = fopen(file_path, "rb");
	if(!input) {
		std::cerr << "Error: could not open file " << file_path << std::endl;
		exit(1);
	};
	fread(&net, sizeof(&net), 1, input);
	fclose(input);
	return net;
}