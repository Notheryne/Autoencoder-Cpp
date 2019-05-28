#include "matrix.cpp"
#include "neuralnetwork.cpp"

using namespace std;



int main()
{
    try{
        //vector<int> neurons = {784, 100, 100, 10};
        vector<int> neurons = {1,2, 3, 4};
        NeuralNetwork nn (neurons, 0.3);
        NeuralNetwork nb (neurons, 0.5, false);

        nn.inf(false);

        nb.inf(false);
        cout << expit(2) << endl;
        return 0;
        }
    catch(char const* msg){
        cerr << msg << endl;
    }
}