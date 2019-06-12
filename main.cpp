#include "helpers/NeuralNetwork.cpp"
#include "helpers/gates.cpp"

int main() {
try
{

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