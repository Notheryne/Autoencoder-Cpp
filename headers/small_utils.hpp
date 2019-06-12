#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <cmath>
#include <stdio.h>
#include <regex>
#include <map>
#include <algorithm>
#include <iterator>
#include <dirent.h>


//for getting the current directory
#include <unistd.h>
#define GetCurrentDir getcwd

#include "eigen_boost_serialization.hpp"

using namespace std;
using namespace Eigen;

/* simple function to print vectors of types */
template <typename T>
void print(const std::vector<T>& v, const char * const separator = " ")
{
    if(!v.empty())
    {
        std::copy(v.begin(), --v.end(), std::ostream_iterator<T>(std::cout, separator));
        std::cout << v.back() << "\n";
    }
}

void print_map(map<string,string> m, char steer)
/* simple function to print maps,
m - map to print
steer - 'a', 'k', or 'v'. a for all, k for keys, v for values */
{
    if ( steer == 'a' ) {
        for( auto item : m) {
            cout << item.first << " : " << item.second << endl;
        }

    } else if ( steer == 'k' ) {
        for (auto item : m) {
            cout << item.first << '\t';
        }
    } else if ( steer == 'v' ) {
        for (auto item : m) {
            cout << item.second << endl;
        }
    } else { throw "[print_mat] Wrong argument!"; }
}

void fill(MatrixXd& A, vector<double> vd)
/* helper function to fill a MatrixXd with elements of vector<double> */
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
/* helper function to fill a vector<double> with elements of MatrixXd */
{
    for(int i = 0; i < A.rows(); ++i){
        for(int j = 0; j < A.cols(); ++j){
            vd.push_back(A(i,j));
        }
    }
}

int ReverseInt(int i)
/* A helper function used in reading mnist data */
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return ((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

vector<vector<double>> ReadMNIST(int NumberOfImages, string filepath)
/* Function used to read mnist data
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

vector<double> ReadMNIST_labels(int NumberOfLabels, string filepath)
/* Function used to read mnist labels
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
    
    vector<double> data(dataset.begin(), dataset.end());
    return data;
    } else {
        throw "[ReadMNIST_labels] Unable to open file.";
    }
}

void create_img(vector<double> vec, int width, int height, string filepath)
/* A function to save image as a file.
vec - vector with doubles corresponding to grey value (0-255) of each pixel
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
/* A helper function used to convert values in vector<double> from any range into a range of [0 - 1].
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
A helper function used to convert values in vector<double> from range [0 - 1] to [0 - max]
max - the biggest number that may be stored in vd
vd - vector that has to be reverse normalized
*/
{
    for(int i = 0; i < vd.size(); ++i){
        vd[i] *= max;
    }
}

vector<double> one_hot(int l, int max)
/* A function tokenizing integers into vector of doubles.
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

int result(vector <MatrixXd> vm, bool verbose)
/* A simple function showing the result of prediction.
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
    if(verbose) {
        cout << endl << "Result: " << index << ", probability: " << max * 100 << "%." << endl;
        return index;
    } else {
        return index;
    }
}

void print_img(vector<double> img)
/* Used for printing approximation of what the image look like into the console.
img - vector with doubles corresponding to grey value (0-255) of each pixel */
{
    for(int i = 1; i < img.size() + 1; ++i)
    {
        if (img[i] == 0) { cout << " "; }
        else { cout << setw(2) << "\u25AA"; }
        if(i % 28 == 0 && i != img.size()) { cout << "\n"; }
    }
}

bool in_map(string key, map<string, string> m)
/* check if given key is in map, return boolean */
{
    for( auto item : m ) {
        if (item.first == key) { return true; }
    }
    return false;
}