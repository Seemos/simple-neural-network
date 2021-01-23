#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "matrix.h"
#include "activation_functions.h"

typedef struct {
	//layers
	matrix layer_input;
	matrix layer_hidden;
	matrix layer_output;

	//weights
	matrix synapses_ih;
	matrix synapses_ho;

	//errors
	matrix error_output;
	matrix error_hidden;

	//gradients
	matrix delta_output;
	matrix delta_hidden;

	//activation functions
	long double (*activation_hidden)(long double);
	long double (*activation_output)(long double);

	//derivatives
	long double (*derivative_hidden)(long double);
	long double (*derivative_output)(long double);
}neural_network;


/*
* Providing functionality of creating training and using the instance
*/
neural_network create_neural_network(unsigned size_input, unsigned size_hidden, unsigned size_output, unsigned function_hidden, unsigned function_output);
void train_neural_network(neural_network& net, const matrix& input, const matrix& target, long double learning_rate);
void save_neural_network(neural_network& net, const char* file_path);
neural_network load_neural_network(const char* file_path);
matrix query_neural_network(neural_network& net, const matrix& input);

#endif