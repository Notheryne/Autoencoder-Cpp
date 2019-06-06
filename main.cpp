#include "NeuralNetwork.cpp"
#include <typeinfo>

int main(){
try
{    
    int datasize = 10000;

    string datapath = "/home/nothy/Desktop/projekt_cpp/Autoencoder-Cpp/t10k-images-idx3-ubyte";
    string labelspath = "/home/nothy/Desktop/projekt_cpp/Autoencoder-Cpp/t10k-labels-idx1-ubyte";


    auto images = ReadMNIST(datasize, datapath);
    auto ilabels = ReadMNIST_labels(datasize, labelspath);
    vector<double> labels(ilabels.begin(), ilabels.end());
    normalize(255, labels);

    vector<int> nodes = { 784, 512, 256, 10 };
    double learning_rate = 0.1;
    NeuralNetwork ola(nodes, learning_rate);

    for (int epoch = 0; epoch < 1; ++epoch){
        for(int i = 0; i < images.size() - 9000; ++i){
            if (i% 100 == 0 ) { 
             cout << "Epoch: " << epoch << " iter: " << i << endl; }
           
            normalize(255, images[i]);
            vector<double> l = one_hot( labels[i], 10 );
            ola.train( images[i], l );
        }
    }
    result(ola.predict(images[ images.size() - 1 ]));
    //ola.save_weights("first_epoch_labels.txt"); */
    /*
    NeuralNetwork ola (nodes, 0.1);
    cout << " JEDEN " << endl;
    ola.inf(true);
    ola.save_weights("weights.txt");
    ola.mess_weights();
    cout <<" DWA " << endl;
    ola.inf(true);
    ola.load_weights("weights.txt");
    cout <<" TRZY " << endl;
    ola.inf(true);
    */
    /*
    for(int i = 0; i < 10000; ++i)
    {
        if (i%1000 == 0) { cout << i << endl; }
        normalize(255, images[i]);
        ola.train( images[i] , images[i] );
    }
    
    //ola.inf(true);

    vector<MatrixXd> X = ola.predict( images[ images.size() - 1 ]);

    vector<double> res;
    reversefill(X[ X.size() - 1 ], res);
    reverse_normalize( 255, res );

    cout << endl;
    print_dou(res);
    create_img(res, 28, 28, "zdj/ola.pmm");
    */


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