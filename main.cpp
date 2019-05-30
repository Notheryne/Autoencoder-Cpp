#include "matrix.cpp"
#include "neuralnetwork.cpp"

using namespace std;



int main()
{
    try{
        //vector<int> neurons = {784, 100, 100, 10};
        vector<int> neurons = {4,2, 3, 4};
        NeuralNetwork nn (neurons, 0.3);
        NeuralNetwork nb (neurons, 0.5, false);
        vector<double> inputs = { 1.1, 2.2, 3.3, 4.4 };
        cout << "Biased:";
        nb.predict(inputs);
        cout << endl << endl << endl;

        nn.predict(inputs);
        return 0;
        }
    catch(char const* msg){
        cerr << msg << endl;
    }
}