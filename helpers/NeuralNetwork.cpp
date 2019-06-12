#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork()
{
    bias = true;

    neurons = { -1, -1, -1 };
    rate = 0.1;
}
NeuralNetwork::NeuralNetwork(vector<int> neurons_, double rate_)
        : neurons(neurons_), rate(rate_)
/*
Standard constructor, if it's used bias is automatically set to true      
*/
    {
        bias = true;

        neurons[0] += 1; //because bias is true, but no point in making an if-statement

        for(int i = 0; i < neurons.size() - 1; ++i){
            MatrixXd weight = 0.5 * MatrixXd::Random(neurons[i+1], neurons[i]); 
            //weights are generated randomly using Eigen::MatrixXd::Random (in range [-0.5, 0.5])
            weights.push_back(weight);
        }
    } 

NeuralNetwork::NeuralNetwork(vector<int> neurons_, double rate_, bool bias_)
        : neurons(neurons_), rate(rate_), bias(bias_)
/*
Another constructor, if we need to specify bias.
*/
    {
        if(bias == true){ neurons[0] += 1; }

        for(int i = 0; i < neurons.size() - 1; ++i){
            MatrixXd weight = 0.5 * MatrixXd::Random(neurons[i+1], neurons[i]);
            //weights are generated randomly using Eigen::MatrixXd::Random (in range [-0.5, 0.5])  
            weights.push_back(weight);
        }
    }

void NeuralNetwork::inf(bool show_weights)
/*
Helper function used to print information about the network, takes boolean variable.
true - print weights (may be really long)
false - don't print weights
*/
{
    cout << "Neurons: ";
    print_int(neurons);

    cout << "Learning rate: " << rate << endl;

    cout << "Biased: " << bias << endl;

    if(show_weights){
        print_mat(weights);
    }
}

double expit(double num)
//Activation function for the neural network
{
    return 1 / (1 + exp(-1.0 * num));
}

double sminmat(double x)
//Simple function helping with calculating weights
{
    return 1.0 - x;
}


vector<MatrixXd> NeuralNetwork::predict(vector<double> inputs)
/*
Method used to predict outputs and store them into a vector of matrices.
inputs - vector of doubles, it's size must be equal to number of neurons on the first layer (without bias)
returns a vector of matrices called outputs
*/
{
    if (bias == true) { inputs.push_back(1.0); } // to compensate for adding neuron to the first layer

    if(neurons[0] == inputs.size() ){
    vector<MatrixXd> outputs;

    MatrixXd A ( inputs.size(), 1 ); //create matrix with 1 column and a row for each element of inputs
    fill(A, inputs);                 //fill it with elements of inputs
                                     //this equals transposing a vector

    outputs.push_back(A); //store it in a vector

    for(int i = 1; i < weights.size() + 1; ++i){
        MatrixXd X = weights[i-1] * outputs[i-1]; //next element of outputs is weights multiplied by outputs

        X = X.unaryExpr(&expit); //use activation function on every element

        outputs.push_back(X); //store it in a vector
    }

        return outputs;
    } else {
        throw "Wrong input dimension!";
    }
}


void NeuralNetwork::train(vector<double> inputs, vector<double> targets)
/*
Method used to train the network.
inputs - vector of doubles, it's size must be equal to number of neurons on the first layer (without bias)
targets - vector of doubles with an expected response to input
*/
{
    vector<MatrixXd> outputs = predict(inputs); //we need outputs to correct the weights

    MatrixXd targets_mat ( targets.size(), 1 );
    fill(targets_mat, targets); //transpose targets vector

    errors = {}; //clean errors from previous uses of train

    errors.push_back( targets_mat - outputs[ outputs.size() - 1 ] ); //first element of errors is the difference of targets_mat and outputs


    for(int i = 1; i < weights.size() + 1; ++i){
        errors.push_back( weights[ weights.size() - i ].transpose() * errors[ i-1 ] ); //fill errors
    }


    for(int i = 1; i < weights.size() + 1; ++i){

        MatrixXd p1 = outputs[ outputs.size() - i - 1 ].transpose();  //transposing outputs (otherwise multiplication wouldn't be possible)

        MatrixXd p2 = errors[ i - 1 ].cwiseProduct(outputs[ outputs.size() - i ]); //multiplication element-wise of errors and outputs

        MatrixXd p3 = outputs[ outputs.size() - i ].unaryExpr(&sminmat); //for every element (a_ij) of a matrix, make it (1 - a_ij)

        weights[ weights.size() - i ] += (rate * ( ((p2.cwiseProduct(p3)) * p1) ) ); //update weights
    }
}
/*
void NeuralNetwork::save_weights(string filepath)
/*
Functions to store weights, because training takes time.
filepath - path to the file to save weights (preferably .txt)
*/ /*
{
    ofstream myfile (filepath);
    if (myfile.is_open())
    {
        for(int i = 0; i < weights.size(); ++i)
        {
            for(int j = 0; j < weights[i].rows(); ++j)
            {
                for(int k = 0; k < weights[i].cols(); ++k){
                    myfile << weights[i](j, k) << ",";
                }
            }
            myfile <<  "\n";
        }
        myfile.close();
    } else {
        throw "[save_weights] Unable to open file.";
    }
}

void NeuralNetwork::load_weights(string filepath)
*/
/*
Load weights from previously saved file.
filepath - a path to the file, where weights are stored (preferably .txt)

may be upgraded, because for now it reads each character and stores them into a vector if ',' is found.
*/
/*
{
    ifstream myfile (filepath);
    if(myfile.is_open()){
    string line;
    int i = 0;
        while( getline(myfile, line) ) 
        {
            string tmp;
            vector<double> vd;

            for(char& c : line){
                if (c != ','){
                    tmp += c;
                } else {
                    double d = stod(tmp);
                    vd.push_back(d);
                    tmp = "";
                }
            }
            fill(weights[i], vd);
            ++i;
        }
    } else { throw "[load_weights] Unable to open file."; }
}
*/
/*
void NeuralNetwork::mess_weights()
/*
A helper function to initialize weights again, just for testing.
*/
/*
{
    for(int i = 0; i < neurons.size() - 1; ++i){
    MatrixXd weight = 0.5 * MatrixXd::Random(neurons[i+1], neurons[i]);
    //weights are generated randomly using Eigen::MatrixXd::Random (in range [-0.5, 0.5])  
    weights.push_back(weight);
    }
} */

double NeuralNetwork::calc_acc(vector<vector<double>> inputs, vector<double> targets)
{
    int good_labels = 0;
    if(inputs.size() == targets.size()){
        for(int i = 0; i < inputs.size(); ++i)
        {
            int answer = result(predict(inputs[i]), false);
            if (answer == (int) targets[i]) { good_labels += 1; }
        }
        double accuracy = (double) good_labels / (double) inputs.size();
        return accuracy;
    } else {
        throw "[calc_acc] Bad sizes!";
    }
}

void save_nn(NeuralNetwork nn, string filepath)
{
    ofstream ofs (filepath);
    if (ofs.is_open()) { 
        boost::archive::text_oarchive ar(ofs);
        ar & nn;
    } else { throw "[save_nn] Unable to open file.";}
}

void load_nn(NeuralNetwork& nn, string filepath)
{
    ifstream ifs(filepath);
    if (ifs.is_open()) {
        boost::archive::text_iarchive ar(ifs);
        ar & nn;
    } else { throw "[load_nn] Unable to open file."; }
}

bool load_nn_safe(NeuralNetwork& nn, string filepath)
{
    ifstream ifs(filepath);
    if(ifs.is_open()) {
        boost::archive::text_iarchive ar(ifs);
        ar & nn;
        return true;
    } else {
        return false;
    }
}