#include "helpers/NeuralNetwork.hpp"

int main()
{
    int datasize = 67000;
    auto images = ReadMNIST(datasize, "/home/nothy/Desktop/projekt_cpp/Autoencoder-Cpp/datasets/full_images");
    auto labels = ReadMNIST_labels(datasize, "/home/nothy/Desktop/projekt_cpp/Autoencoder-Cpp/datasets/full_labels");
    vector<int> neurons = { 784, 512, 256, 10 };
    NeuralNetwork nn (neurons, 0.1);
    for(int i = 0; i < images.size(); ++i)
    {
        cout << i << endl;
        vector<double> l = one_hot(labels[i], 10);
        nn.train(images[i], l);
    }
    save_nn(nn, "model_big.txt");

}