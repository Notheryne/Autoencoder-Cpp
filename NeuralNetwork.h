
#include "matrix.h"

class NeuralNetwork{
public:
    NeuralNetwork(std::vector<int>, double);
    NeuralNetwork(std::vector<int>, double, bool);


    std::vector<int> neurons() { return nodes; }
    std::vector<Matrix> weight() { return weights; }
    double rates() { return rate; }
    void inf(bool);

    bool bias = true;

private:
    std::vector<int> nodes;
    double rate; 
    std::vector<Matrix> weights;
};
