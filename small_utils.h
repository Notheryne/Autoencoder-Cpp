#include <iostream>
#include <random>
#include <eigen3/Eigen/Dense>
#include <vector>

using namespace std;
using namespace Eigen;

void print_int(vector<int> vi){
    for(int i = 0; i < vi.size(); ++i){
        cout << vi[i] << ", ";
    }
    cout << endl;
}

void print_dou(vector<double> vd){
    for(int i = 0; i < vd.size(); ++i){
        cout << vd[i] << ", ";
    }
    cout << endl;
}

void print_mat(vector<MatrixXd> vm){
    for(int i = 0; i < vm.size(); ++i){
        cout << vm[i] << endl << endl;
    }
    cout << endl;
}

double expit(double num){
    return 1 / (1 + exp(-1.0 * num));
}

void fill(MatrixXd& A, vector<double> vd){
    if(A.size() == vd.size()){
        for(int i = 0; i < vd.size(); ++i){
            int x = i % A.cols();
            int y = i / A.cols();
            A( y, x ) = vd[i];
        }
    }else{
        throw "Wrong size!";
    }
}