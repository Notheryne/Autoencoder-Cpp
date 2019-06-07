#include "NeuralNetwork.cpp"
#include <typeinfo>

int main(){
try
{    
    int datasize = 10000;

    string datapath = "/home/nothy/Desktop/projekt_cpp/Autoencoder-Cpp/t10k-images-idx3-ubyte";
    string labelspath = "/home/nothy/Desktop/projekt_cpp/Autoencoder-Cpp/t10k-labels-idx1-ubyte";

    auto images = ReadMNIST(datasize, datapath);
    auto labels = ReadMNIST_labels(datasize, labelspath);

    vector<int> nodes = { 784, 512, 256, 10 };
    double learning_rate = 0.1;
    NeuralNetwork ola(nodes, learning_rate);
    ola.load_weights("mnist_weights.txt");
    /*
    for(int i = 0; i < images.size() - 1000; ++i)
    {
        if( i % 100 == 0) {cout << i << endl; }
        normalize(255, images[i]);
        vector<double> l = one_hot( labels[i] , 10 );
        ola.train( images[i], l );
    }

    ola.save_weights("mnist_weights.txt");
    
    cout << "1000: " << labels[1000] << " 1500:" << labels[1500] << endl;
    ola.load_weights("mnist_weights.txt");
    cout << "1000:" << endl;
    result(ola.predict(images[1000]), true);
    create_img(images[1000], 28, 28, "1000(2).pmm");
    vector<MatrixXd> X = ola.predict(images[1200]);
    cout << X[ X.size() - 1 ] << endl << endl;

    cout << "1500:" << endl;
    result(ola.predict(images[1500]), true);
    create_img(images[1500], 28, 28, "1500.pmm");
    vector<MatrixXd> Y = ola.predict(images[1500]);
    cout << Y[ Y.size() - 1 ] << endl << endl;
    */
    vector<vector<double>> testset(images.begin() + 9000, images.end());
    vector<double> testlab(labels.begin() + 9000, labels.end());
    cout << testset[10][0];
    

    double acc = ola.calc_acc(testset, testlab);
    cout << acc;

    return 0;
}

catch(exception& e) {
    cerr << "Error: " << e.what() << '\n';
    return 1;
}

catch(char const* x){
    cerr << x << '\n';
}
catch(...) {
    cerr << "Unknown exception\n";
    return 2;
}
}