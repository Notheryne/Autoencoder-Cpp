#include <stdlib.h>
#include <iostream>
#include <sys/ioctl.h>
#include <cmath>
#include <sys/ioctl.h>
#include <stdio.h>
#include "NeuralNetwork.cpp"


using namespace std;

void center_text(string s)
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    for (int i =0; i<floor(w.ws_col/2)-floor(s.size()/2);i++){
        cout<<"I";
    }
    cout<<"\e[2K";
    cout<<s<<'\n';

}
void line_break()
{
       struct winsize w;
       ioctl(0, TIOCGWINSZ, &w);
    for (int i =0; i<w.ws_col;i++){
        cout<<"-";
    }
}
void margin_text(int n, string s)
{
    for (int i =0;i<n;i++){
        cout<<"I";
    }
      cout<<"\e[2K";
      cout<<s<<'\n';

}

void clean()
{
    printf("\033c");
}
void prompt()
{
    cout << "> ";
}

void make_title(){
    clean();
    string title = "C++ Neural Network Demonstration";
    cout<<"\e[1m";
    center_text(title);
    line_break();
    cout<<"\e[0m" << "\n\n\n" <<"\e[1;4m";
    center_text("Menu:");
    cout<<"\e[0m";
}

string steer(){
    string selection;
    prompt();
    cin >> selection;
    return selection;
}
//functions placeholders

void main_scren();
void test_screen();
void train_screen();
void mnist_screen();
void gates_screen();

void main_screen()
{
    make_title();

    center_text("1. Test");
    center_text("2. Train");
    center_text("0. Exit");

    string selection = steer();

    if( selection == "1" ) { test_screen(); }
    else if( selection == "2") { train_screen(); }
    else if( selection == "0") {
        clean();
        exit(0);
        }
    else { main_screen(); }
}

void test_screen(){
    make_title();

    center_text("1. MNIST");
    center_text("2. Logic gates");
    center_text("9. Back");
    center_text("0. Exit");

    string selection = steer();

    if( selection == "1" ) { mnist_screen(); }
    else if( selection == "2") { gates_screen(); }
    else if( selection == "9") { main_screen(); }
    else if( selection == "0") {
        clean();
        exit(0);
        }
    else { test_screen(); }

}

void train_screen(){
    clean();
    cout<<"\e[1m";
    string s;
    
    center_text(s);
    line_break();
    cout<<"\n\n\n";
    cout<<"\e[1;4m";
    center_text("Input path to mnist file:");
    cout<<"\e[0m";
    string s2;
    cin>>s2;
    cout<<s;
    char c;
    cin>>c;
}

string get_str(string text)
{
    string str;
    cout << text << '\n';
    prompt();
    cin >> str;
    return str;
}

int get_int(string text)
{
    int n;
    cout << text << '\n';
    prompt();
    cin >> n;
    return n;
}
void mnist_screen()
{
    make_title();

    //string mnist_path = get_str("Input path to MNIST images.");
    //string labels_path = get_str("Input path to MNIST labels.");
    int datasize = 10000;

    string weights_path = get_str("Input path for weights.");
    int num = get_int("Input the number of images you want to test on.");
    string mnist_path = "/home/nothy/Desktop/projekt_cpp/Autoencoder-Cpp/t10k-images-idx3-ubyte";
    string labels_path = "/home/nothy/Desktop/projekt_cpp/Autoencoder-Cpp/t10k-labels-idx1-ubyte";
    make_title();

    vector<int> neurons = { 784, 512, 256, 10 };
    cout << "Neruons ok\n";
    NeuralNetwork nn (neurons, 0.1);
    cout << "Network ok\n";

    auto images = ReadMNIST(datasize, mnist_path);
    auto labels = ReadMNIST_labels(datasize, labels_path);

    //nn.load_weights(weights_path);



}

void gates_screen(){
    center_text("gates");
}
int main(){
    main_screen();
    return 0;
}
