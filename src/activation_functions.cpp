#include<cmath>
#include "activation_functions.h"

long double sigmoid(long double x) {
	return 1 / (1 + pow(std::exp(1.0), -x));
}
long double sigmoid_derivative(long double x) {
	return sigmoid(x) * (1 - sigmoid(x));
}

long double (*activations[])(long double) = {sigmoid};
long double (*derivatives[])(long double) = {sigmoid_derivative};