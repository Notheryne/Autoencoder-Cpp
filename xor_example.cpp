#include "NeuralNetwork.cpp"

int main()
{ try{
    vector<int> nodes = { 2, 3, 1 };
    double rate = 0.1;

    NeuralNetwork forxor (nodes, rate, true);
    //forxor.inf(true);
    /*
    vector<double> inputs1 = { 1, 1 };
    vector<double> inputs2 = { 1, 0 };
    vector<double> inputs3 = { 0, 1 };
    vector<double> inputs4 = { 0, 0 };

    vector<double> targets1 = { 0 };
    vector<double> targets2 = { 1 };
    vector<double> targets3 = { 1 };
    vector<double> targets4 = { 0 };

    for(int i = 0; i < 100000; ++i){
        forxor.train( inputs1, targets1 );
        forxor.train( inputs2, targets2 );
        forxor.train( inputs3, targets3 );
        forxor.train( inputs4, targets4 );
    }

    vector<MatrixXd> x1 = forxor.predict(inputs1);
    vector<MatrixXd> x2 = forxor.predict(inputs2);
    vector<MatrixXd> x3 = forxor.predict(inputs3);
    vector<MatrixXd> x4 = forxor.predict(inputs4);

    cout << x1[ x1.size() - 1 ] << endl;
    cout << x2[ x2.size() - 1 ] << endl;
    cout << x3[ x3.size() - 1 ] << endl;
    cout << x4[ x4.size() - 1 ] << endl << endl << endl;
    */


    return 0;
}
catch(excepti#include "NeuralNetwork.cpp"

int main()
{ try{
    vector<int> nodes = { 2, 3, 1 };
    double rate = 0.1;

    NeuralNetwork forxor (nodes, rate, true);
    //forxor.inf(true);
    /*
    vector<double> inputs1 = { 1, 1 };
    vector<double> inputs2 = { 1, 0 };
    vector<double> inputs3 = { 0, 1 };
    vector<double> inputs4 = { 0, 0 };

    vector<double> targets1 = { 0 };
    vector<double> targets2 = { 1 };
    vector<double> targets3 = { 1 };
    vector<double> targets4 = { 0 };

    for(int i = 0; i < 100000; ++i){
        forxor.train( inputs1, targets1 );
        forxor.train( inputs2, targets2 );
        forxor.train( inputs3, targets3 );
        forxor.train( inputs4, targets4 );
    }

    vector<MatrixXd> x1 = forxor.predict(inputs1);
    vector<MatrixXd> x2 = forxor.predict(inputs2);
    vector<MatrixXd> x3 = forxor.predict(inputs3);
    vector<MatrixXd> x4 = forxor.predict(inputs4);

    cout << x1[ x1.size() - 1 ] << endl;
    cout << x2[ x2.size() - 1 ] << endl;
    cout << x3[ x3.size() - 1 ] << endl;
    cout << x4[ x4.size() - 1 ] << endl << endl << endl;
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
    cerr << "#include "NeuralNetwork.cpp"

int main()
{ try{
    vector<int> nodes = { 2, 3, 1 };
    double rate = 0.1;

    NeuralNetwork forxor (nodes, rate, true);
    //forxor.inf(true);
    /*
    vector<double> inputs1 = { 1, 1 };
    vector<double> inputs2 = { 1, 0 };
    vector<double> inputs3 = { 0, 1 };
    vector<double> inputs4 = { 0, 0 };

    vector<double> targets1 = { 0 };
    vector<double> targets2 = { 1 };
    vector<double> targets3 = { 1 };
    vector<double> targets4 = { 0 };

    for(int i = 0; i < 100000; ++i){
        forxor.train( inputs1, targets1 );
        forxor.train( inputs2, targets2 );
        forxor.train( inputs3, targets3 );
        forxor.train( inputs4, targets4 );
    }

    vector<MatrixXd> x1 = forxor.predict(inputs1);
    vector<MatrixXd> x2 = forxor.predict(inputs2);
    vector<MatrixXd> x3 = forxor.predict(inputs3);
    vector<MatrixXd> x4 = forxor.predict(inputs4);

    cout << x1[ x1.size() - 1 ] << endl;
    cout << x2[ x2.size() - 1 ] << endl;
    cout << x3[ x3.size() - 1 ] << endl;
    cout << x4[ x4.size() - 1 ] << endl << endl << endl;
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
    return 1;#include "NeuralNetwork.cpp"

int main()
{ try{
    vector<int> nodes = { 2, 3, 1 };
    double rate = 0.1;

    NeuralNetwork forxor (nodes, rate, true);
    //forxor.inf(true);
    /*
    vector<double> inputs1 = { 1, 1 };
    vector<double> inputs2 = { 1, 0 };
    vector<double> inputs3 = { 0, 1 };
    vector<double> inputs4 = { 0, 0 };

    vector<double> targets1 = { 0 };
    vector<double> targets2 = { 1 };
    vector<double> targets3 = { 1 };
    vector<double> targets4 = { 0 };

    for(int i = 0; i < 100000; ++i){
        forxor.train( inputs1, targets1 );
        forxor.train( inputs2, targets2 );
        forxor.train( inputs3, targets3 );
        forxor.train( inputs4, targets4 );
    }

    vector<MatrixXd> x1 = forxor.predict(inputs1);
    vector<MatrixXd> x2 = forxor.predict(inputs2);
    vector<MatrixXd> x3 = forxor.predict(inputs3);
    vector<MatrixXd> x4 = forxor.predict(inputs4);

    cout << x1[ x1.size() - 1 ] << endl;
    cout << x2[ x2.size() - 1 ] << endl;
    cout << x3[ x3.size() - 1 ] << endl;
    cout << x4[ x4.size() - 1 ] << endl << endl << endl;
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
}
catch(char const* x){
    cerr << x << '\n';
}
catch(...) {
    cerr << "Unknown exception\n";
    return 2;
}
}