#include <iostream>
#include <string>
#include <vector>

#include "ah_input.h"

using namespace std;

int main(int argc, char *argv[]) {
    
    string input_s;
    vector<string> input_v;
    
    ah::get_input(argc, argv, input_s);
    cout << "string input: " << input_s << endl;

    ah::get_input(argc, argv, input_v);
    vector<string>::iterator it = input_v.begin();
    cout << "vector input: ";
    while(it<input_v.end()){
        cout << *it;
        ++it;
    }
    cout << endl;
    
    return 0;
}
