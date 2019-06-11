//#include "NeuralNetwork.h"


void add_vecs(vector<vector<double>>& m, vector<double> a, vector<double> b, vector<double> c, vector<double> d)
//small function to fill vector of vectors with vectors (works only for vectors of doubles)
{
    m.push_back(a);
    m.push_back(b);
    m.push_back(c);
    m.push_back(d);
}

void gate_train(NeuralNetwork& nn, string gatename, int epochs, int steps_per_epoch)
/*
Function for simple training on chosen gate, possible gatenames:
and, xor, or, nor, xnor, nand
*/
{
    for(int epoch = 0; epoch < epochs; ++epoch)
    {
        vector<double> in1 = {0, 0};
        vector<double> in2 = {0, 1};
        vector<double> in3 = {1, 0};
        vector<double> in4 = {1, 1};
        vector<vector<double>> input;
        add_vecs(input, in1, in2, in3, in4);

        vector<double> zero = one_hot(0, 2);
        vector<double> one = one_hot(1, 2);
        vector<vector<double>> gate;

        if(gatename == "and") { add_vecs(gate, zero, zero, zero, one); }
        else if (gatename == "xor") { add_vecs(gate, zero, one, one, zero); }
        else if (gatename == "or") { add_vecs(gate, zero, one, one, one); }
        else if (gatename == "nor") { add_vecs(gate, one, zero, zero, zero); }
        else if (gatename == "xnor") { add_vecs(gate, one, zero, zero, one); }
        else if (gatename == "nand") { add_vecs(gate, one, one, one, zero); }
        else
        {
            throw string("[gateway_train] There's no gate called " + gatename + ".\n");
        }
        vector<vector<double>> hot_gate;
        
        for(int step = 0; step < steps_per_epoch; ++step){
            //cout << "Epoch: " << epoch << ", step: " << step << '\r'; //tutaj fajnie jakby się konsola czyścila przed wypisaniem następnej rzeczy
            
            nn.train(input[0], gate[0]);
            nn.train(input[1], gate[1]);
            nn.train(input[2], gate[2]);
            nn.train(input[3], gate[3]);
        }
    }
}