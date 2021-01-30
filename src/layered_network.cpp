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
