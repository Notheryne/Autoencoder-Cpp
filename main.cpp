#include "NeuralNetwork.cpp"

int main(){
    vector<int> nodes = { 4, 2, 3, 4 };
    vector<double> inputs = { 1.1, 2.2, 3.3, 4.4 };
    NeuralNetwork nn( nodes, 0.3 );
    NeuralNetwork nb( nodes, 0.3 , false );
    MatrixXd A (3, 4);
    A << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12;

    nn.predict(inputs);
    nn.predict(inputs);
    cout << endl;
    return 0;
}