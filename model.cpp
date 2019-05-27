#include "matrix.cpp"
#include <typeinfo>
#include <vector>

using namespace std;


void fill_from_vec(Matrix& A, vector<double> vd){
    if (A.size() == vd.size()){
        for(int i = 0; i < A.row(); ++i){
            for(int j = 0; j < A.col(); ++j){
                A(i, j) = vd[i * A.row() + j];
            }
        }
    }
    else{
        throw "Wrong size!";
    }
}


int main()
{
    try{
        vector<double> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
        Matrix A (3,3);
        cout << A << endl;
        fill_from_vec(A, vec);
        cout << A << endl;
        return 0;
    }
    catch(char const* msg){
        cerr << msg << endl;
    }
}