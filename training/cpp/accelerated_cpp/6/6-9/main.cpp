#include <string>
#include <vector>
#include <iostream>
#include <numeric>

#include "./ah_input/ah_input.h"

using namespace std;



int main(int argc, char* argv[]) {
    vector<string> input_v;
    string input_s;
    
    ah::get_input(argc, argv, input_v);
    
    input_s = accumulate(input_v.begin(), input_v.end(), input_s);
    
    cout << input_s << endl;
    
    return 0;
}