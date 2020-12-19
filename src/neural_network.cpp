#include <stdlib.h>
#include <fstream>
#include "neural_network.h"
#include "activation_functions.h"
#include "matrix.h"

neural_network create_neural_network(unsigned size_input, unsigned size_hidden, unsigned size_output) {
	neural_network net;
	net.synapses_ih = create_random_matrix(size_input, size_hidden);
	net.synapses_ho = create_random_matrix(size_hidden, size_output);
	return net;
}

void train_neural_network(neural_network& net, const matrix& input, const matrix& target, long double learning_rate) {
	//input layer
	net.layer_input = input;

	//calculate the hidden layer
	net.layer_hidden = dot(net.layer_input, net.synapses_ih);
	net.layer_hidden = apply_function(net.layer_hidden, sigmoid);

	//calculate the output layer
	net.layer_output = dot(net.layer_hidden, net.synapses_ho);
	net.layer_output = apply_function(net.layer_output, sigmoid);

	//backpropagating the output layer
	net.error_output = target - net.layer_output;
	net.delta_output = net.error_output * apply_function(net.error_output, sigmoid_derivative);

	//backpropagating the hidden layer
	net.error_hidden = dot(net.delta_output, transpose(net.synapses_ho));
	net.delta_hidden = net.error_hidden * apply_function(net.error_hidden, sigmoid_derivative);

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

void save_neural_network(neural_network& net, const char* file_path) {
	FILE* output;
	output = fopen(file_path, "wb");
	fwrite(&net, sizeof(&net), 1, output);
	fclose(output);
}

neural_network load_neural_network(const char* file_path) {
	neural_network net;
	FILE* input;
	input = fopen(file_path, "rb");
	fread(&net, sizeof(&net), 1, input);
	fclose(input);
	return net;
}