#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(vector<int> neurons_, double rate_)
        : neurons(neurons_), rate(rate_)
    {
        bias = true;

        neurons[0] += 1;

        for(int i = 0; i < neurons.size() - 1; ++i){
            MatrixXd weight = 0.5 * MatrixXd::Random(neurons[i+1], neurons[i]);
            weights.push_back(weight);
        }
    } 

NeuralNetwork::NeuralNetwork(vector<int> neurons_, double rate_, bool bias_)
        : neurons(neurons_), rate(rate_), bias(bias_)
    {
        if(bias == true){ neurons[0] += 1; }

        for(int i = 0; i < neurons.size() - 1; ++i){
            MatrixXd weight = 0.5 * MatrixXd::Random(neurons[i+1], neurons[i]);
            weights.push_back(weight);
        }
    }

void NeuralNetwork::inf(bool show_weights)
{
    cout << "Neurons: ";
    print_int(neurons);

    cout << "Learning rate: " << rate << endl;

    cout << "Biased: " << bias << endl;

    if(show_weights){
        print_mat(weights);
    }
    cout << endl;
}

void NeuralNetwork::predict(vector<double> inputs)
{
    if (bias == true) { inputs.push_back(1.0); }
    
    if(neurons[0] == inputs.size() ){
    vector<MatrixXd> outputs;
    MatrixXd A ( inputs.size(), 1 );
    fill(A, inputs);

    outputs.push_back(A);

    for(int i = 1; i < weights.size() + 1; ++i){
        MatrixXd X = weights[i-1] * outputs[i-1];

        X.unaryExpr(&expit);

        outputs.push_back(X);
    }
    }else{
        throw "Wrong input dimension!";
    }
}