#include "small_utils.h"

class NeuralNetwork{
public:
    NeuralNetwork(vector<int>, double);
    NeuralNetwork(vector<int>, double, bool);
    ~NeuralNetwork() { };

    void inf(bool);

    void predict(vector<double>);

private:
    vector<int> neurons;
    double rate;
    vector<MatrixXd> weights;
    bool bias;
    vector<MatrixXd> outputs;
};