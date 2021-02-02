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

void build_layered_network(layered_network& net){
    net.topology_functions.push_back(net.f_outputs);
    net.topology_neurons.push_back(net.n_outputs);

    unsigned n_weights = net.topology_functions.size();

    net.weights.reserve(n_weights);
    net.errors.reserve(n_weights);
    net.deltas.reserve(n_weights);
    net.outputs.reserve(n_weights + 1);

    for (unsigned i = 0; i < n_weights; i++)
    {
        net.weights.push_back(create_random_matrix(net.topology_neurons[i], net.topology_neurons[i+1]));
    }
}

void train_layered_network(layered_network& net, matrix& input, const matrix& target, long double learning_rate){
    unsigned max_index = net.topology_functions.size() - 1;

    /*
    * Calculate the values of all layers.
    * by using the outputs of the layers before.
    * input matriy is treatened as output as well
    */
    net.outputs.push_back(input);
    for(unsigned i = 0; i <= max_index; i++){
        net.outputs.push_back(apply_function(dot(net.outputs[i], net.weights[i]), activations[net.topology_functions[i]]));
    }

    /*
    * Backpropagation 
    */
    net.errors.push_back(target - net.outputs[net.topology_functions.size() - 1]);

    for(unsigned i = 0; i <= max_index; i++){
        net.deltas.push_back(net.errors[i] * apply_function(net.errors[i], derivatives[net.topology_functions[max_index - i]]));
        net.errors.push_back(dot(net.deltas[i], transpose(net.weights[max_index - i])));
    }
    
    /*
    * weight updating
    */
    for(unsigned i = 0; i <= max_index; i++){
        net.weights[max_index - i] +=  dot(transpose(net.outputs[max_index - i]), net.deltas[i]) * learning_rate;
    }

    net.outputs.clear();
    net.errors.clear();
    net.deltas.clear();
}