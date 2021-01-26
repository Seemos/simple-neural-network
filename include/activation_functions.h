#ifndef ACTIVATION_FUNCTIONS_H
#define ACTIVATION_FUNCTIONS_H

#include <cmath>
#include <utility>

const double EULER     = std::exp(1.0);
const unsigned SIGMOID = 0;
const unsigned TANH    = 1;
const unsigned RELU    = 2;

long double sigmoid(long double x);
long double sigmoid_derivative(long double x);

long double tanh_derivative(long double x);

long double relu(long double x);
long double relu_derivative(long double x);

extern long double (*activations[])(long double);
extern long double (*derivatives[])(long double);

#endif