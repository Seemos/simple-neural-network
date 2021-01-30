#ifndef LAYERED_NETWORK_H
#define LAYERED_NETWORK_H

#include <vector>
#include <array>
#include "matrix.h"
#include "activation_functions.h"

typedef struct {
    bool is_built;
    unsigned n_outputs;
    unsigned f_outputs;
    std::vector<unsigned> topology_neurons;
    std::vector<unsigned> topology_functions;
    std::vector<matrix> weights;
    std::vector<matrix> outputs;
    std::vector<matrix> deltas;
    std::vector<matrix> errors;
}layered_network;

layered_network create_layered_network(unsigned n_inputs, unsigned n_outputs, unsigned activation);
void add_hidden_layer(layered_network& net, unsigned n_neurons, unsigned activation);
void build_layered_network(layered_network& net);

void train_layered_network(layered_network& net, matrix& input, const matrix& target, long double learning_rate);
matrix query_layered_network(layered_network& net, const matrix& input);

#endif