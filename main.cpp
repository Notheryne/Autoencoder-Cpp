#include "NeuralNetwork.cpp"

int main(){
try
{
    //vector<vector<double>> images;
    //ReadMNIST(10000, 784, images);

    //vector<int> nodes = { 784, 512, 256, 512, 784};
    vector<int> nodes = { 2, 2, 3};

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