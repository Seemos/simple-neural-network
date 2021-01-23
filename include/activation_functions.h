#ifndef ACTIVATION_FUNCTIONS_H
#define ACTIVATION_FUNCTIONS_H

#include <cmath>
#include <utility>

const unsigned SIGMOID = 0;

long double sigmoid(long double x);
long double sigmoid_derivative(long double x);

extern long double (*activations[])(long double);
extern long double (*derivatives[])(long double);

#endif