#include <iostream>
#include <string>

#include "ah_input.h"

using namespace std;

int main(int argc, char *argv[]) {
    
    string input = ah::get_input(argc, argv);
   
    cout << input << endl;
    
    return 0;
}