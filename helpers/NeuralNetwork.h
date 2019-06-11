#include "small_utils.h"

class NeuralNetwork{
public:
    //constructors (see .cpp)
    NeuralNetwork();
    NeuralNetwork(vector<int>, double);
    NeuralNetwork(vector<int>, double, bool);
    //destructor
    ~NeuralNetwork() { };

    //operators
    NeuralNetwork& operator=(NeuralNetwork nn){ return *this; }

    //helper functions
    void inf(bool);
    void mess_weights();
    vector<MatrixXd> show_errors() { return errors; };

    //saving/loading weights to file
    void save_weights(string);
    void load_weights(string);

    //main functions
    void train(vector<double>, vector<double>);
    vector<MatrixXd> predict(vector<double>);
    double calc_acc(vector<vector<double>>, vector<double>);
private:
    vector<int> neurons; // number of neurons on each layer, first should match input size, last should match output size
    double rate; //learning rate of the network
    vector<MatrixXd> weights; //weights (probabilities) of response
    bool bias; //"extra" neuron storing value of 1 on the first layer
    vector<MatrixXd> errors; //errors calculated by the network

    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & neurons & rate & weights &  bias & errors;
    }

};