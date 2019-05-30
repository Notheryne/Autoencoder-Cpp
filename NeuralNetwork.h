
#include "matrix.h"

class NeuralNetwork{
public:
    NeuralNetwork(std::vector<int>, double);
    NeuralNetwork(std::vector<int>, double, bool);
    ~NeuralNetwork() { };

    std::vector<int> neurons() { return nodes; }
    std::vector<Matrix> weight() { return weights; }
    double rates() { return rate; }
    void inf(bool);

    std::vector<double> predict (std::vector<double>);
    bool bias = true;

private:
    std::vector<int> nodes;
    double rate; 
    std::vector<Matrix> weights;
    double activation_function;
};
