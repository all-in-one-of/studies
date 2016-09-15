
#include <iostream>
#include <vector>

#include "ah_input.h"
#include "ah_split.h"
#include "palindrome.h"

using namespace std;

int main (int argc, char * argv[]) {
    
    string input_s = ah::get_input(argc, argv);
    //cout << input_s << endl;
    vector<string> input_v = ah::split(input_s);
    
    int count = 0;
    for(int i=0; i<input_v.size();i++) 
        if( is_palindrome(input_v[i]) ) {
            ++count;
            cout << input_v[i] << endl;
        }
    cout << "The supplied input has " << count << " palindromes." << endl;
}
