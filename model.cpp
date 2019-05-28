#include "matrix.cpp"
#include <typeinfo>
#include <vector>

using namespace std;

class NeuralNetwork{
public:
    NeuralNetwork(vector<double>, double);
    NeuralNetwork(vector<double>, double, bool);


    vector<double> neurons() { return nodes; }
    double rates() { return rate; }
    void inf();
    bool bias = true;

private:
    vector<double> nodes;
    double rate; 
   
};

NeuralNetwork::NeuralNetwork(vector<double> nodes_, double rate_)
        : nodes(nodes_), rate(rate_)
{

   nodes[0] += 1;
}

NeuralNetwork::NeuralNetwork(vector<double> nodes_, double rate_, bool bias_)
        :nodes(nodes_), rate(rate_), bias(bias_) { }


void NeuralNetwork::inf(){
    NeuralNetwork nn(*this);
    cout << "Neurons: ";
    for(int i = 0; i < nn.neurons().size(); ++i){
        cout << setw(5) << nn.neurons()[i];
    }
    cout << "\nLearning rate: " << nn.rates() << endl;
    cout << "Biased: " << bias << endl;
}



int main()
{
    try{
        cout << "compilated" << endl;
        vector<double> neurons = {784, 100, 100, 10};
        NeuralNetwork nn (neurons, 0.3);
        NeuralNetwork nb (neurons, 0.5, false);

        nn.inf();
        nb.inf();


        Matrix A (10, 10);
        vector<double> x;
        cout << endl << "Rozmiar macierzy: " << A.size() << '\n' << "Rozmiar wektora: " << x.size() << endl;
        A.fill_with_random(-5, 5);
        cout << "Macierz A:\n" << A << endl << endl;
        A.fill_vec(x);
        cout << "Vector x: " << endl;
        for(int i = 0; i < x.size(); ++i) { cout << x[i] << ", "; }

        cout << endl << x.size() << endl;
        return 0;
        }
    catch(char const* msg){
        cerr << msg << endl;
    }
}