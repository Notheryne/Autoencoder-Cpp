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
}

vector<MatrixXd> NeuralNetwork::predict(vector<double> inputs)
{
    if (bias == true) { inputs.push_back(1.0); }

    if(neurons[0] == inputs.size() ){
    vector<MatrixXd> outputs;
    MatrixXd A ( inputs.size(), 1 );

    fill(A, inputs);


    outputs.push_back(A);

    for(int i = 1; i < weights.size() + 1; ++i){
        MatrixXd X = weights[i-1] * outputs[i-1];

        X = X.unaryExpr(&expit);

        outputs.push_back(X);
    }


        return outputs;
    } else {
        throw "Wrong input dimension!";
    }
}

void NeuralNetwork::train(vector<double> inputs, vector<double> targets)
{
    vector<MatrixXd> outputs = predict(inputs);

    MatrixXd targets_mat ( targets.size(), 1 );

    errors = {};
    fill(targets_mat, targets);

    errors.push_back( targets_mat - outputs[ outputs.size() - 1 ] );


    for(int i = 1; i < weights.size() + 1; ++i){
        errors.push_back( weights[ weights.size() - i ].transpose() * errors[ i-1 ] );
    }


    for(int i = 1; i < weights.size() + 1; ++i){

        MatrixXd p1 = outputs[ outputs.size() - i - 1 ].transpose();
        MatrixXd p2 = errors[ i - 1 ].cwiseProduct(outputs[ outputs.size() - i ]);
        MatrixXd p3 = outputs[ outputs.size() - i ].unaryExpr(&sminmat);

        weights[ weights.size() - i ] += (rate * ( ((p2.cwiseProduct(p3)) * p1) ) );
    }
}

void NeuralNetwork::save_weights(string filepath)
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
        throw "Unable to open file.";
    }
}

void NeuralNetwork::load_weights(string filepath)
{
    ifstream myfile (filepath);
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

}

void NeuralNetwork::mess_weights(){
    for(int i = 0; i < weights.size(); ++i)
    {
        MatrixXd A ( weights[i].rows(), weights[i].cols() );
        weights[i] = A;
    }
}
/*
u_char read_mnist_labels(string full_path, int& number_of_labels) {
    auto reverseInt = [](int i) {
        unsigned char c1, c2, c3, c4;
        c1 = i & 255, c2 = (i >> 8) & 255, c3 = (i >> 16) & 255, c4 = (i >> 24) & 255;
        return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
    };

    typedef unsigned char uchar;

    ifstream file(full_path, ios::binary);

    if(file.is_open()) {
        int magic_number = 0;
        file.read((char *)&magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);

        if(magic_number != 2049) throw runtime_error("Invalid MNIST label file!");

        file.read((char *)&number_of_labels, sizeof(number_of_labels)), number_of_labels = reverseInt(number_of_labels);

        uchar _dataset = new uchar[number_of_labels];
        for(int i = 0; i < number_of_labels; i++) {
            file.read((char*)&_dataset[i], 1);
        }
        return _dataset;
    } else {
        throw runtime_error("Unable to open file `" + full_path + "`!");
    }
}
*/
vector<int> read_mnist_labels(string full_path, int num_of_labels)
{
    ifstream file(full_path, ios::binary);

    if(file.is_open()){
        int magic_number = 0;
        file.read((char *) &magic_number , sizeof(magic_number));
        magic_number = ReverseInt(magic_number);

        if(magic_number != 2049) throw runtime_error("Invalid MNIST label file!");

        file.read((char *)&num_of_labels, sizeof(num_of_labels)), num_of_labels = ReverseInt(num_of_labels);

        vector<int> dataset (num_of_labels);
        for(int i = 0; i < num_of_labels; i++) {
            file.read((char*) &dataset[i], 1);        }
    
    return dataset;
    } else {
        throw "Unable to open file!";
    }
}