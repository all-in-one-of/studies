#include <algorithm>    // std::sort
#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>

#include "str_vec.h" // split

using namespace std;

int main() {
    string s;
    
    // read and split each line of input
    getline(cin, s);
    vector<string> v = split(s);
    
    sort(v.begin(), v.end(), is_upper_word);
    
    for (vector<string>::size_type i = 0; i != v.size(); ++i) {
        cout << v[i] << endl;
    }
    
    return 0;
}