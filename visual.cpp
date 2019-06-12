#include "helpers/NeuralNetwork.hpp"

//using namespace std;

string get_dir()
/* get current working directory using macro defined in small_utils.hpp */{
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  string current_working_dir(buff);
  return current_working_dir;
}

vector<string> check_dir(string add, bool fullpath)
/* find all files in given directory
add - what to add to current directory
fullpath - true to return full path, false for relative path */
{
    string path = get_dir();
    path += '/';
    path += add;
    DIR *dir;
    struct dirent *ent;
    
    vector<string> files;

    if((dir = opendir (path.c_str())) != NULL)
    {
        while((ent = readdir(dir)) != NULL)
        {
            string temp(ent->d_name);
            if(temp[0] == '.') { continue; }
            if(fullpath)
            {
                string file = path + temp;
                files.push_back(file);
                continue;
            } else { files.push_back(temp); }
            
        }
    }
    return files;
}

map<string, string> modelspaths; //maps models, name : full path
map<string, string> datapaths; // maps datasets, name : full_path

void config(map<string, string>& models, map<string, string>& data)
/* Function settomg up modelspaths and datapaths. */
{
    cout << "Creating config.\n";
    string current_dir = get_dir();
    vector<string> files = check_dir("models/", true);
    vector<string> names = check_dir("models/", false);
    vector<vector<int>> indexes;

    for(int i = 0; i < names.size(); ++i)
    {
        int a = names[i].find("_");
        int b = names[i].find(".");
        vector<int> pair = { a , b };
        indexes.push_back(pair);
    }

    for(int i = 0; i < indexes.size(); ++i)
    {
        string name = "";
        for(int j = indexes[i][0] + 1; j < indexes[i][1]; ++j)
        {
            name += names[i][j];
        }
        models[name] = files[i];
    }

    files = check_dir("datasets/", true);
    names = check_dir("datasets/", false);

    for(int i = 0; i < files.size(); ++i)
    {
        data[names[i]] = files[i];
    }
}

void center_text(string s)
/* Function to center the text in terminal. */
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
/* Function printing "-" for the whole width of terminal */
{
       struct winsize w;
       ioctl(0, TIOCGWINSZ, &w);
    for (int i =0; i<w.ws_col;i++){
        cout<<"-";
    }
}

void clean()
/* Function cleaning the terminal */
{
    printf("\033c");
}

void prompt()
{
    cout << "\n> ";
}

void make_title()
/* Prints the header of each screen. */
{
    clean();
    string title = "C++ Neural Network Demonstration";
    cout<<"\e[1m";
    center_text(title);
    line_break();
    cout<<"\e[0m" << "\n\n\n";
}

string steer()
/* Function to get input for navigation */
{
    string selection;
    prompt();
    cin >> selection;
    return selection;
}

string get_str(string text)
/* Function getting all string inputs */
{
    string str;
    cout << text;
    prompt();
    cin >> str;
    return str;
}

int get_int(string text)
/* Function getting all int inputs */
{
    int n;
    cout << text;
    prompt();
    cin >> n;
    if (n < 0)
    {
        cout << "This number can't be negative.";
        get_int(text);
    }
    return n;
}

double get_double(string text)
/* Function getting all double inputs */
{
    double d;
    cout << text;
    prompt();
    cin >> d;
    if (d < 0)
    {
        cout << "This number can't be negative.";
        get_double(text);
    }
    return d;
}


/* preview of screens and where they lead */

void main_screen();
    void test_screen();
        void test_mnist_screen();
            void test_mnist_screen2(NeuralNetwork nn, vector<vector<double>> img_set, vector<double> lab_set, int amount);
                void accuracy_test(NeuralNetwork nn, vector<vector<double>> img_set, vector<double> lab_set, int amount);
                void img_test(NeuralNetwork nn, vector<vector<double>> img_set, vector<double> lab_set, int amount);
    
        void test_gates_screen();

        void test_custom_screen();
            void test_custom_mnist_screen(NeuralNetwork nn);
                void test_mnist_screen2(NeuralNetwork nn, vector<vector<double>> img_set, vector<double> lab_set, int amount);
                    void accuracy_test(NeuralNetwork nn, vector<vector<double>> img_set, vector<double> lab_set, int amount);
                    void img_test(NeuralNetwork nn, vector<vector<double>> img_set, vector<double> lab_set, int amount);
            void test_custom_gates_screen(NeuralNetwork nn);

    void train_screen();
        void train_mnist_screen();
            void default_train_mnist_screen();
                void models_saved_screen(int epochs, int amount);

            void custom_train_mnist_screen();
                void custom_train_mnist_screen2(NeuralNetwork nn);
                    void models_saved_screen(int epochs, int amount);

        void train_gates_deforcus();
            void train_gates_screen();
                void train_gates_screen2(NeuralNetwork nn);




void gate_predict(NeuralNetwork nn)
{
    string gatename = get_str("What's your selection?");
    int selection = 0;
    if(gatename == "9") { test_screen(); }
    else if (gatename == "0") { 
        clean();
        exit(0);
    }

    else if (selection == 0)
    {
        for(auto model : modelspaths)
        {
            if(gatename == model.first)
            {
                load_nn( nn, model.second );
                selection = 1;
                break;
            }
        }
    }
    else
    {
        gate_predict(nn);
        return;
    }

    int m = get_int("First input.");
    int n = get_int("Second input.");
    
    if ( (m != 0 && m != 1) || (n != 0 && n != 1) )
    { 
        cout << "Wrong input.\n";
        gate_predict(nn);
        return;
    }

    vector<double> input = { (double) m, (double) n };
    result(nn.predict(input), true);
    return;
}

void mnist_train(NeuralNetwork& nn, vector<vector<double>> img_set, vector<double> lab_set, int epochs, int amount)
{
    for(int epoch = 0; epoch < epochs; ++epoch)
    {
        int counter = 1;
        bool showbar = true;
        string bar;
        if( amount < 100 )
        {
            bar = "Progress bar hidden due to low amount of images.";
            showbar = false;
        }
        else
        {
            bar = "[..................................................]";
        }

        for(int step = 0; step < amount; ++step)
        {
            make_title();
            cout << "Epoch number: " << epoch + 1 << ", current image index: " << step << "\nProgress: " << setw(2) << bar << endl;

            vector<double> label = one_hot( lab_set[ step ], 10 );
            nn.train(img_set[ step ], label );

            double part = (double) amount / 50.0;
            
            if( showbar && step % (int) part == 0 && counter < 52 )
            {
                bar[counter] = '#';
                counter += 1;
            }
        }
        if (showbar) { bar[ bar.size() - 2 ] = '#'; }
    }
    
    string modelspath = get_str("What should be the name of your model file? It will be saved as /model_{}.txt");
    while ( in_map(modelspath, modelspaths) ) { modelspath = get_str("This name is taken.\nWhat should be the name of your model file? It will be saved as /model_{}.txt"); }

    string new_path = "models/model_" + modelspath + ".txt";
    save_nn(nn, new_path);
    models_saved_screen(epochs, amount);
}

/* main screen */
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


/* second level screens */
void test_screen()
{
    make_title();

    center_text("1. MNIST");
    center_text("2. Logic gates");
    center_text("3. Custom test");
    center_text("9. Back");
    center_text("0. Exit");

    string selection = steer();

    if( selection == "1" ) { test_mnist_screen(); }
    else if( selection == "2") { test_gates_screen(); }
    else if( selection == "3") { test_custom_screen(); }
    else if( selection == "9") { main_screen(); }
    else if( selection == "0") {
        clean();
        exit(0);
        }
    else { test_screen(); }

}

void train_screen()
{
    make_title();
    center_text("1. Train on MNIST");
    center_text("2. Train on logic gates");
    center_text("9. Back");
    center_text("0. Exit");

    string selection = steer();

    if (selection == "1") { train_mnist_screen(); }
    else if (selection == "2") { train_gates_deforcus(); }
    else if( selection == "9") { main_screen(); }
    else if( selection == "0") {
        clean();
        exit(0);
        }
    else { train_screen(); }
}

/* third level screens - testing */
void test_mnist_screen()
{
    make_title();
    int datasize = 67000;

    int start = get_int("Where to start testing?");
    int end = get_int("Where to stop testing?");

    start = start % datasize;
    end = end % datasize;

    int amount = end - start;

    if(start > end)
    {
        cout << "Swapping values.";
        swap(start, end);
    }

    string mnist_path = datapaths["full_images"];
    //string mnist_path = get_str("Drag file or input path to MNIST images.");
    auto images = ReadMNIST(datasize, mnist_path);
    vector<vector<double>> img_set(images.begin() + start, images.begin() + end);
    cout << mnist_path << " succesfuly loaded!\n";

    string labels_path = datapaths["full_labels"];
    //string labels_path = get_str("Drag file or input path to MNIST labels.");
    auto labels = ReadMNIST_labels(datasize, labels_path);
    vector<double> lab_set(labels.begin() + start, labels.begin() + end);
    cout << labels_path << " succesfuly loaded!\n";

    NeuralNetwork nn;
    load_nn(nn, modelspaths["mnist"]);
    cout << modelspaths["mnist"] << " succesfuly loaded!\n";
    test_mnist_screen2(nn, img_set, lab_set, amount);
}

void test_mnist_screen2(NeuralNetwork nn, vector<vector<double>> img_set, vector<double> lab_set, int amount)
{
    make_title();

    center_text("1. Test accuracy.");
    center_text("2. Test a single image.");
    center_text("9. Back");
    center_text("0. Exit");

    string selection = steer();
    if (selection == "1") { accuracy_test(nn, img_set, lab_set, amount); }
    else if (selection == "2") { img_test(nn, img_set, lab_set, amount); }
    else if (selection == "9") { test_screen(); }
    else if (selection == "0") {
        clean();
        exit(0);
    }
    else { test_mnist_screen2(nn, img_set, lab_set, amount); }
}

void accuracy_test(NeuralNetwork nn, vector<vector<double>> img_set, vector<double> lab_set, int amount)
{
        make_title();
        cout << "\nNeural network parameters:\n";
        nn.inf(false);
        cout << "Calculating accuracy. . . (this may take some time)\n";
        double acc = nn.calc_acc(img_set, lab_set);
        cout << "Accuracy: " << acc << ", based on " << amount << " test images." << endl;
        cout << "Input anything to go back.";
        string s;
        cin >> s;
        test_mnist_screen2(nn, img_set, lab_set, amount);
}

void img_test(NeuralNetwork nn, vector<vector<double>> img_set, vector<double> lab_set, int amount)
{
    make_title();
    string q = get_str("Input the index of image you want to test (in your chosen range, -1 to go back).");
    int test;

    if( q == "-1") { test_mnist_screen2(nn, img_set, lab_set, amount); }
    else { test = stoi(q); }
    test = test % amount;
    vector<double> test_img = img_set[test];
    print_img(test_img);
    result(nn.predict(test_img), true);

    cout << "Do you want to save the picture in /images/{}.pmm? [y/n]";
    string selection2 = steer();
    if(selection2 == "y") {
        string filename = get_str("Input the name of your file.");
        filename += ".pmm";
        string filepath = "images/" + filename;
        create_img(test_img, 28, 28, filepath);
        cout << "Image succesfuly saved!\n";
        center_text("1. Back");
        center_text("Any. Again");

        string selection3 = steer();
        if( selection3 == "1" ){ test_mnist_screen2(nn, img_set, lab_set, amount); }
        else{ img_test(nn, img_set, lab_set, amount); }
    }
    else if(selection2 == "n") {
        center_text("1. Back");
        center_text("Any. Again");
        string selection3 = steer();
        if( selection3 == "1" ){ test_mnist_screen2(nn, img_set, lab_set, amount); }
        else { img_test(nn, img_set, lab_set, amount); }
    }
}


void test_gates_screen()
{
    make_title();
    center_text("Implemented gates:");
    center_text("and \t or \t xor");
    center_text("nor \t xnor \t nand");
    center_text("9. Back");
    center_text("0. Exit");

    vector<int> neurons = { 2, 4, 2 };
    NeuralNetwork nn(neurons, 0.1);
    gate_predict(nn);
    cout << '\n';

    center_text("1. Back");
    center_text("Any. Again");

    string selection = steer();
    if ( selection == "1" ) { test_screen(); }
    else { test_gates_screen(); }
}

void test_custom_screen()
{
    config(modelspaths, datapaths);
    make_title();
    cout << "Found models:\n";

    print_map(modelspaths, 'k');
    cout << endl;
    string selection = get_str("What's your choice? (9 to go back, 0 to exit)");
    NeuralNetwork nn;
    if ( selection == "9" ) { test_screen(); }
    else if ( selection == "0" ) {
        clean();
        exit(0);
    } else {
    while(!load_nn_safe(nn, modelspaths[ selection ])) {
        selection = get_str("What's your choice?");
    }
    center_text("1. MNIST");
    center_text("2. Logic gates");
    string selection2 = steer();
    if ( selection2 == "1" ) { test_custom_mnist_screen(nn); }
    else if ( selection2 == "2" ) { test_custom_gates_screen(nn); }
    else{ test_custom_screen(); }
    }
}

void test_custom_mnist_screen(NeuralNetwork nn)
{
    make_title();
    nn.inf(false);

    int datasize = 67000;

    int start = get_int("Where to start testing?");
    int end = get_int("Where to stop testing?");

    start = start % datasize;
    end = end % datasize;

    int amount = end - start;

    if(start > end)
    {
        cout << "Swapping values.";
        swap(start, end);
    }

    string mnist_path = datapaths["full_images"];
    //string mnist_path = get_str("Drag file or input path to MNIST images.");
    auto images = ReadMNIST(datasize, mnist_path);
    vector<vector<double>> img_set(images.begin() + start, images.begin() + end);
    cout << mnist_path << " succesfuly loaded!\n";

    string labels_path = datapaths["full_labels"];
    //string labels_path = get_str("Drag file or input path to MNIST labels.");
    auto labels = ReadMNIST_labels(datasize, labels_path);
    vector<double> lab_set(labels.begin() + start, labels.begin() + end);
    cout << labels_path << " succesfuly loaded!\n";

    test_mnist_screen2(nn, img_set, lab_set, amount);
}

void test_custom_gates_screen(NeuralNetwork nn)
{
    make_title();
    nn.inf(false);

    int m = get_int("First input.");
    int n = get_int("Second input.");
    
    if ( (m != 0 && m != 1) || (n != 0 && n != 1) )
    { 
        cout << "Wrong input.\n";
        test_custom_gates_screen(nn);
        return;
    }

    vector<double> input = { (double) m, (double) n };
    result(nn.predict(input), true);
    
    center_text("1. Back");
    center_text("Any. Again");

    string selection = steer();
    if ( selection == "1" ) { test_custom_screen(); }
    else { test_custom_gates_screen(nn); }
}

/* third level screens - training */
void train_mnist_screen()
{
    make_title();
    center_text("1. Default network");
    center_text("2. Custom network");
    string selection = steer();
    if( selection == "1" ) { default_train_mnist_screen(); }
    else if ( selection == "2" ) { custom_train_mnist_screen(); }
    else {  train_mnist_screen(); }
}

void custom_train_mnist_screen()
{
    make_title();
    int layers = get_int("How many layers should your network have? (must be more than one)");
    double learning_rate = get_double("What should the learning rate be? (must be in range (0, 1))");

    if (layers <= 1 || learning_rate > 1)
    { 
        cout << "Bad input.";
        train_mnist_screen();
    }

    vector<int> neurons;
    bool bias = true;
    string biased = get_str("Should the network be biased? [y/n]");
    while (biased != "y" && biased != "n") { biased = get_str("Should the network be biased? [y/n]"); }
    if (biased == "y") { bias = true; }
    else if(biased == "n") { bias = false; }

    int first_layer = get_int("How many neurons should there be on the 1st layer? (must match input size, 784 for mnist).");
    neurons.push_back(first_layer);

    for(int i = 1; i < layers - 1; ++i)
    {
        string question = "How many neurons should there be on ";
        if(i + 1 == 2) { question += to_string(i+1) + "nd layer?"; }
        else if(i+1 == 3) { question += to_string(i+1) + "rd layer?"; }
        else { question += to_string(i+1) + "th layer?"; }

        int ith_layer = get_int(question);
        neurons.push_back(ith_layer);
    }
    int last_layer = get_int("How many neurons should there be on the last layer? (must match output size, 10 for mnist)");
    neurons.push_back(last_layer);
    NeuralNetwork nn(neurons, learning_rate, bias);
    custom_train_mnist_screen2(nn);
}

void custom_train_mnist_screen2(NeuralNetwork nn)
{
    make_title();
    cout << "Neural network succesfuly built. Parameters:\n";
    nn.inf(false);
    cout << endl;

    int datasize = 67000;
    int amount = get_int("How many images do you want to load?");
    amount = amount % (datasize + 1);
    int start = 0;
    if(amount != datasize)
    {
        int start = get_int("On which image should the loading start?");
        start = start % (datasize);
    }

    string mnist_path = datapaths["full_images"];
    //string mnist_path = get_str("Drag file or input path to MNIST images.");
    auto images = ReadMNIST(datasize, mnist_path);
    vector<vector<double>> img_set(images.begin() + start, images.begin() + amount);
    cout << mnist_path << " succesfuly loaded!\n";

    string labels_path = datapaths["full_labels"];
    //string labels_path = get_str("Drag file or input path to MNIST labels.");
    auto labels = ReadMNIST_labels(datasize, labels_path);
    vector<double> lab_set(labels.begin() + start, labels.begin() + amount);
    cout << labels_path << " succesfuly loaded!\n";

    make_title();

    int epochs = get_int("How many epochs do you want to train the network on?");

    mnist_train(nn, img_set, lab_set, epochs, amount);
}

void default_train_mnist_screen()
{
    make_title();
    vector<int> neurons = { 784, 512, 256, 10 };
    double rate = 0.1;

    cout << "Default network parameters:\n";
    NeuralNetwork nn(neurons, rate);
    nn.inf(false);

    int datasize = 67000;
    int amount = get_int("How many images do you want to load?");
    amount = amount % (datasize + 1);
    int start = 0;
    if(amount != datasize)
    {
        int start = get_int("On which image should the loading start?");
        start = start % (datasize);
    }

    string mnist_path = datapaths["full_images"];
    //string mnist_path = get_str("Drag file or input path to MNIST images.");
    auto images = ReadMNIST(datasize, mnist_path);
    vector<vector<double>> img_set(images.begin() + start, images.begin() + amount);
    cout << mnist_path << " succesfuly loaded!\n";

    string labels_path = datapaths["full_labels"];
    //string labels_path = get_str("Drag file or input path to MNIST labels.");
    auto labels = ReadMNIST_labels(datasize, labels_path);
    vector<double> lab_set(labels.begin() + start, labels.begin() + amount);
    cout << labels_path << " succesfuly loaded!\n";

    make_title();
    int epochs = get_int("How many epochs do you want to train the network on?");

    mnist_train(nn, img_set, lab_set, epochs, amount);
}

void models_saved_screen(int epochs, int amount)
{
    make_title();
    cout << "Model succesfuly saved.\nThe network was learning for " << epochs << " epochs, with " << amount << " steps per epoch." << endl;
    center_text("1. Testing");
    center_text("2. Main menu");
    center_text("0. Exit");
    string selection = steer();

    if ( selection == "1" ) { test_screen(); }
    else if ( selection == "2" ) { main_screen(); }
    else if ( selection == "0" )
    {
        clean();
        exit(0);
    }
    else { models_saved_screen(epochs, amount); }
}

void train_gates_deforcus()
{
    make_title();
    center_text("1. Default network");
    center_text("2. Custom network");
    center_text("9. Back");
    center_text("0. Exit");

    NeuralNetwork nn({ 2, 4, 2 }, 0.1);
    string selection = steer();
    if( selection == "1" ) { train_gates_screen2(nn); }
    else if ( selection == "2" ) { train_gates_screen(); }
    else if ( selection == "9" ) { train_screen(); }
    else if ( selection == "0" ) { 
        clean();
        exit(0);
    } else { train_gates_deforcus(); }
}
void train_gates_screen()
{
    make_title();
    int layers = get_int("How many layers should your network have? (must be more than one)");
    double learning_rate = get_double("What should the learning rate be? (must be in range (0, 1))");

    if (layers <= 1 || learning_rate > 1)
    { 
        cout << "Bad input.";
        train_mnist_screen();
    }

    vector<int> neurons;
    bool bias = true;
    string biased = get_str("Should the network be biased? [y/n]");
    while (biased != "y" && biased != "n") { biased = get_str("Should the network be biased? [y/n]"); }
    if (biased == "y") { bias = true; }
    else if(biased == "n") { bias = false; }

    int first_layer = get_int("How many neurons should there be on the 1st layer? (must match input size).");
    neurons.push_back(first_layer);

    for(int i = 1; i < layers - 1; ++i)
    {
        string question = "How many neurons should there be on ";
        if(i + 1 == 2) { question += to_string(i+1) + "nd layer?"; }
        else if(i+1 == 3) { question += to_string(i+1) + "rd layer?"; }
        else { question += to_string(i+1) + "th layer?"; }

        int ith_layer = get_int(question);
        neurons.push_back(ith_layer);
    }
    int last_layer = get_int("How many neurons should there be on the last layer? (must match output size)");
    neurons.push_back(last_layer);
    NeuralNetwork nn(neurons, learning_rate, bias);
    train_gates_screen2(nn);
}

void train_gates_screen2(NeuralNetwork nn){
    make_title();
    nn.inf(false);

    cout << "The inputs will be:\n"
        <<"{ 0, 0 } \t { 0, 1 } \t { 1, 0 } \t {1, 1}\n\n";
    vector<vector<double>> inputs;
    inputs.push_back({ 0, 0 });
    inputs.push_back({ 0, 1 });
    inputs.push_back({ 1, 0 });
    inputs.push_back({ 1, 1 });

    vector<double> targets;
    vector<vector<double>> gate;
    int i = 0;
    while(targets.size() != 4) {
        cout << "{ " << inputs[i][0] << ", " << inputs[i][1] << " } should result in (0 or 1): ";
        double n;
        cin >> n;
        if ( n == 0.0 || n == 1.0) {
            targets.push_back(n);
            ++i; 
        }
    }


    for(int i = 0; i < targets.size(); ++i) {
        vector<double> tmp = one_hot(targets[i], 2);
        gate.push_back(tmp);
    }

    int epochs = get_int("How many epochs do you want to train the network on?");
    int steps_per_epoch = get_int("How many steps per epoch should there be?");

    for(int epoch = 0; epoch < epochs; ++epoch) {
        int counter = 1;
        bool showbar = true;
        string bar;
        if( steps_per_epoch < 100 ) {
            bar = "Progress bar hidden due to low steps per epoch.";
            showbar = false;
        }
        else { bar = "[..................................................]"; }

        for(int step = 0; step < steps_per_epoch; ++step) {
            make_title();
            cout << "Epoch number: " << epoch + 1 << ", current step: " << step << "\nProgress: " << setw(2) << bar << endl;
            nn.train(inputs[0], gate[0]);
            nn.train(inputs[1], gate[1]);
            nn.train(inputs[2], gate[2]);
            nn.train(inputs[3], gate[3]);

            double part = (double) steps_per_epoch / 50.0;
            
            if( showbar && step % (int) part == 0 && counter < 52 ) {
                bar[counter] = '#';
                counter += 1;
            }
        }
    }

    string modelspath = get_str("What should be the name of your model file? It will be saved as /model_{}.txt");
    while ( in_map(modelspath, modelspaths) ) { modelspath = get_str("This name is taken.\nWhat should be the name of your model file? It will be saved as /model_{}.txt"); }

    string new_path = "models/model_" + modelspath + ".txt";
    save_nn(nn, new_path);
    models_saved_screen(epochs, steps_per_epoch);
}

int main(){
    try{
        config(modelspaths, datapaths); //set the paths on any computer
        main_screen(); //start the main loop
        return 0;
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
