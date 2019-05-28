#include "NeuralNetwork.h"

using namespace std;

double expit(double x){
    return 1 / (1 + exp(-1. * x));
}

NeuralNetwork::NeuralNetwork(vector<int> nodes_, double rate_)
        : nodes(nodes_), rate(rate_)
{
    nodes[0] += 1;
    for(int i = 0; i < nodes.size() - 1; ++i){
        Matrix W (nodes[i+1], nodes[i]);
        W.fill_with_random(-0.5, 0.5);
        weights.push_back(W);
    }
}

NeuralNetwork::NeuralNetwork(vector<int> nodes_, double rate_, bool bias_)
        :nodes(nodes_), rate(rate_), bias(bias_)
        {
            if(bias == true){
                nodes[0] += 1;
            }
        for(int i = 0; i < nodes.size() - 1; ++i){
            Matrix W (nodes[i+1], nodes[i]);
            W.fill_with_random(-0.5, 0.5);
            weights.push_back(W);
        }
    }
        


void NeuralNetwork::inf(bool show_weights){
    NeuralNetwork nn(*this);
    cout << "Neurons: ";
    for(int i = 0; i < nn.neurons().size(); ++i){
        cout << setw(5) << nn.neurons()[i];
    }
    cout << "\nLearning rate: " << nn.rates() << endl;
    cout << "Biased: " << bias << endl;
    if(show_weights == true){
        for(int i = 0; i < nn.neurons().size(); ++i){
            cout << nn.weights[i] << endl;
        }
    }
}

