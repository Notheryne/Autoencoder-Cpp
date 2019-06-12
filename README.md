# Autoencoder-Cpp
## C++ final project

### Authors: Bartosz Rydziński, Aleksander Obuchowski

This is a tool to set your Neural Network using simple and intuitive TUI/CUI, then train and test it on MNIST database or logic gates (even those not real!).
May not work on Windows.

### Directories:
- datasets - contains [MNIST](http://yann.lecun.com/exdb/mnist/) databases.
-- full - 67000 images/labels, test - 10000 images/labels
- headers - contains NeuralNetwork class, other utility functions used in code and [Eigen Serialization header](https://gist.github.com/mtao/5798888)
- images - default folder to save .pmm images used to test (printing them in terminal is only an approximation)
- models - folder where models are stored, with a naming convention "model_{name}.txt"
-- default models: and, nand, or, nor, xor, xnor, mnist

### Requirements:
- make
- g++
- [Boost serialization](https://www.boost.org/)
- [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page)
- [dirent.h](https://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html)


### Running the program:
When you have met all the requirements simply clone this directory, go to its directory and in your terminal type:  
`make`  
You should see this:  
`g++ visual.cpp -o visual -g \`  
`-lboost_serialization -lboost_system -lboost_filesystem \`  
`-lboost_iostreams \`  
`-lstdc++ -lm -std=c++14`  
After it's done just type:
`./visual`  
