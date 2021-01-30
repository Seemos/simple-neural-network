#include <iostream>
#include "layered_network.h"

layered_network create_layered_network(unsigned n_inputs, unsigned n_outputs, unsigned activation){
    layered_network net;
    net.is_built = false;
    net.topology_neurons.push_back(n_inputs);
    net.n_outputs = n_outputs;
    net.f_outputs = activation;
    return net;
}

void add_hidden_layer(layered_network& net, unsigned n_neurons, unsigned activation){
    net.is_built = false;
    net.topology_neurons.push_back(n_neurons);
    net.topology_functions.push_back(activation);
}
