#include "small_utils.h"


int main()
{
    vector<double> test = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<double> data(test.begin() + 5, test.end());
    print_dou(test);
    print_dou(data);
}