#include<cmath>
#include "activation_functions.h"

// SIGMOID
long double sigmoid(long double x) {
	return 1 / (1 + pow(EULER, -x));
}
long double sigmoid_derivative(long double x) {
	return sigmoid(x) * (1 - sigmoid(x));
}

// TANH
long double tanh_derivative(long double x){
	return 1 - pow(tanhl(x), 2);
}

// RELU
long double relu(long double x){
	return x > 0 ? x : 0;
}
long double relu_derivative(long double x){
	return x > 0 ? 1 : 0;
}

long double (*activations[])(long double) = {sigmoid, tanhl, relu};
long double (*derivatives[])(long double) = {sigmoid_derivative, tanh_derivative, relu_derivative};