#include <iostream>
#include <random>
#include <eigen3/Eigen/Dense>
#include <vector>
#include <fstream>

using namespace std;
using namespace Eigen;

//simple functions to print vectors of ints/doubles/matrices
void print_int(vector<int> vi)
{
    for(int i = 0; i < vi.size(); ++i){
        cout << vi[i] << ", ";
    }
    cout << endl;
}

void print_dou(vector<double> vd)
{
    for(int i = 0; i < vd.size(); ++i){
        cout << vd[i] << ", ";
    }
    cout << endl;
}

void print_mat(vector<MatrixXd> vm)
{
    for(int i = 0; i < vm.size(); ++i){
        cout << vm[i] << endl << endl;
    }
    cout << endl;
}

void fill(MatrixXd& A, vector<double> vd)
//helper function to fill a MatrixXd with elements of vector<double>
{
    if(A.size() == vd.size()){
        for(int i = 0; i < vd.size(); ++i){
            int x = i % A.cols();
            int y = i / A.cols();
            A( y, x ) = vd[i];
        }
    } else {
        throw "[fill] Wrong size!";
    }
}

void reversefill(MatrixXd A, vector<double>& vd)
//helper function to fill a vector<double> with elements of MatrixXd
{
    for(int i = 0; i < A.rows(); ++i){
        for(int j = 0; j < A.cols(); ++j){
            vd.push_back(A(i,j));
        }
    }
}

int ReverseInt(int i)
//A helper function used in reading mnist data
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return ((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}


vector<vector<double>> ReadMNIST(int NumberOfImages, string filepath)
/*
Function used to read mnist data
NumberOfImages - size of dataset
filepath - a path to mnist data, probably "... /train-images-idx3-ubyte"
*/
{
    vector<vector<double>> arr;
    arr.resize(NumberOfImages, vector<double>(784));
    ifstream file(filepath, ios::binary);
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
        return arr;
    } else {
        throw "[ReadMNIST] Wrong filepath.";
    }
}

vector<int> ReadMNIST_labels(int NumberOfLabels, string filepath)
/*
Function used to read mnist labels
NumberOfLabels - size of dataset
filepath - a path to mnist labels, probably "... /train-labels-idx3-ubyte"
*/
{
    ifstream file(filepath, ios::binary);

    if(file.is_open()){
        int magic_number = 0;
        file.read((char *) &magic_number , sizeof(magic_number));
        magic_number = ReverseInt(magic_number);

        if(magic_number != 2049) throw runtime_error("Invalid MNIST label file!");

        file.read((char *)&NumberOfLabels, sizeof(NumberOfLabels)), NumberOfLabels = ReverseInt(NumberOfLabels);

        vector<int> dataset (NumberOfLabels);
        for(int i = 0; i < NumberOfLabels; i++) {
            file.read((char*) &dataset[i], 1);        }
    
    return dataset;
    } else {
        throw "[ReadMNIST_labels] Unable to open file.";
    }
}


void create_img(vector<double> vec, int width, int height, string filepath)
/*
A function to save image as a file.
vec - vector with doubles corresponding to colors (0-255) of each pixel
filepath - a path where the image should be stored (preferably "... /image_name.pmm")
*/
{
    if (vec.size() != width * height)
    {
        throw "[create_img] Bad vector size for image.";
    }
    else
    {
        ofstream img(filepath);
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
/*
A helper function used to convert values in vector<double> from any range into a range of [0-1].
max - the biggest number that may be stored in vd (ex. 255 for mnist data)
vd - vector that has to be normalized
*/
{
    for(int i = 0; i < vd.size(); ++i){
        vd[i] = vd[i] / max;
    }
}

void reverse_normalize(double max, vector<double>& vd)
/*
A helper function used to convert values in vector<double> from range [0-1] to [0-max]
max - the biggest number that may be stored in vd
vd - vector that has to be reverse normalized
*/
{
    for(int i = 0; i < vd.size(); ++i){
        vd[i] *= max;
    }
}

vector<double> one_hot(int l, int max)
/*
A function tokenizing integers into vector of doubles.
l - a hot number
max - how many numbers are there in total
for example one_hot(2, 5) would return vector<double> {0.0, 0.0, 1.0, 0.0, 0.0}
*/
{
    if (l > max) { throw "[one_hot] Wrong input!"; }

    vector<double> tokens;
    for(int i = 0; i < max; i++){
        if(l == (double) i){
            tokens.push_back( 1.0 );
        }
        else{
            tokens.push_back( 0.0 );
        }
    }
    return tokens;
}

void result(vector <MatrixXd> vm)
/*
A simple function showing the result of prediction.
vm - a vector of matrices, should be returned by NeuralNetwork.train() method, shows the prediction and probability of it.
*/
{
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
    cout << endl << "Wynik: " << index << ", z prawdopobieństwem: " << max * 100 << "%." << endl;
}