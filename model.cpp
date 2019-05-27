#include "matrix.cpp"
#include <typeinfo>
#include <vector>

using namespace std;


int main()
{
    try{
        Matrix A (10, 10);
        A.fill_with_random(-1, 1);
        cout << A;

    }
    catch(char const* msg){
        cerr << msg << endl;
    }
}