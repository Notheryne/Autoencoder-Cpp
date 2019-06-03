#include "small_utils.h"

class NeuralNetwork{
public:
    NeuralNetwork(vector<int>, double);
    NeuralNetwork(vector<int>, double, bool);
    ~NeuralNetwork() { };

    void inf(bool);
    vector<MatrixXd> show_errors() { return errors; };
    vector<MatrixXd> predict(vector<double>);
    void train(vector<double>, vector<double>);
    void save_weights(string);
    void load_weights(string);
    void mess_weights();
private:
    vector<int> neurons;
    double rate;
    vector<MatrixXd> weights;
    bool bias;
    vector<MatrixXd> errors;
};