#include <iostream>
#include <random>
#include <eigen3/Eigen/Dense>
#include <vector>
#include <fstream>

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
    } else {
        throw "Wrong size!";
    }
}

void reversefill(MatrixXd A, vector<double>& vd){
    for(int i = 0; i < A.rows(); ++i){
        for(int j = 0; j < A.cols(); ++j){
            vd.push_back(A(i,j));
        }
    }
}
double sminmat(double x){
    return 1.0 - x;
}




int ReverseInt(int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return ((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}


void ReadMNIST(int NumberOfImages, int DataOfAnImage, vector<vector<double>> &arr)
{
    arr.resize(NumberOfImages, vector<double>(DataOfAnImage));
    ifstream file("/home/avienir/Programowanie/Autoencoder-Cpp/t10k-images-idx3-ubyte", ios::binary);
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char *)&magic_number, sizeof(magic_number));
        magic_number = ReverseInt(magic_number);
        file.read((char *)&number_of_images, sizeof(number_of_images));
        number_of_images = ReverseInt(number_of_images);
        file.read((char *)&n_rows, sizeof(n_rows));
        n_rows = ReverseInt(n_rows);
        file.read((char *)&n_cols, sizeof(n_cols));
        n_cols = ReverseInt(n_cols);
        for (int i = 0; i < number_of_images; ++i)
        {
            for (int r = 0; r < n_rows; ++r)
            {
                for (int c = 0; c < n_cols; ++c)
                {
                    unsigned char temp = 0;
                    file.read((char *)&temp, sizeof(temp));
                    arr[i][(n_rows * r) + c] = (double)temp;
                }
            }
        }
    } else {
        throw "Wrong filepath.";
    }
}

void create_img(vector<double> vec, int width, int height, string filename)
{
    if (vec.size() != width * height)
    {
        cout << "bad vector size for image";
    }
    else
    {
        ofstream img(filename);
        img << "P3" << endl;
        img << width << " " << height << endl;
        img << "255" << endl;

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int r = vec[width * y + x];
                int g = vec[width * y + x];
                int b = vec[width * y + x];
                img << r << " " << g << " " << b << endl;
            }
        }
    }
}

void normalize(double max, vector<double>& vd)
{
    for(int i = 0; i < vd.size(); ++i){
        vd[i] = vd[i] / max;
    }
}

void rnormalize(double max, vector<double>& vd)
{
    for(int i = 0; i < vd.size(); ++i){
        vd[i] *= max;
    }
}

vector<double> one_hot(double l, int max){
    vector<double> table;
    for(int i=0;i<max;i++){
        if(l==(double)i){
            table.push_back(1.0);
        }
        else{
            table.push_back(0.0);
        }
        
    }
    return table;

}

void result(vector <MatrixXd> vm){
    double max = 0;
    int index = 0;
    MatrixXd X = vm[ vm.size() - 1 ];

    for(int i=0; i < X.rows(); ++i)
    {
        for(int j = 0; j < X.cols(); ++j){
            if (X(i,j) > max) 
            {
            max = X(i,j);
            index = i; 
            }
        }

    }
    cout << endl << "Wynik: " << index << ", z prawdopobieństwem: " << max << '.' << endl;
}