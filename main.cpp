#include "helpers/NeuralNetwork.cpp"
#include "helpers/gates.cpp"

int main(){
try
{  
    NeuralNetwork nn({ 2, 4, 2 }, 0.1);

    nn.load_weights("/home/nothy/Desktop/projekt_cpp/Autoencoder-Cpp/weights/weights_xor.txt");

    nn.inf(false);

    save_nn(nn, "/home/nothy/Desktop/projekt_cpp/Autoencoder-Cpp/models/model_xor.txt");
}

catch(exception& e) {
    cerr << "Error: " << e.what() << '\n';
    return 1;
}

catch(char const* x){
    cerr << x << '\n';
    return 2;
}
catch(string x){
    cerr << x << '\n';
    return 3;
}
catch(...) {
    cerr << "Unknown exception\n";
    return 4;
}
}