#include "NeuralNetwork.cpp"
#include <typeinfo>
#include <cxxabi.h>
#include <stdlib.h>
int main(){
try
{    
    int x = 10000;
    vector<vector<double>> images;
    ReadMNIST(x, 784, images);
    //int test = 9234;
    create_img(images[ images.size() - 1 ], 28, 28, "zdj/ostatnie.pmm");
    vector<int> nodes = { 784, 512, 256, 10 };
   
    //auto dataset = read_mnist_labels("/home/nothy/Desktop/projekt_cpp/Autoencoder-Cpp/t10k-labels-idx1-ubyte", x);
    auto dataset = read_mnist_labels("/home/avienir/Programowanie/Autoencoder-Cpp/t10k-labels-idx1-ubyte", x);
    vector<double> labels(dataset.begin(), dataset.end());
    //print_dou(labels);

    NeuralNetwork ola(nodes, 0.1);
    //normalize(255, labels);
    //ola.load_weights("first_epoch_labels.txt");
    //vector<MatrixXd> X = ola.predict(images[1000]);
    create_img(images[1000], 28, 28, "1000.pmm");
    //print_mat(X);

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
    rnormalize( 255, res );

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