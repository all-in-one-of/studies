
#include <iostream>
#include <string>
#include <vector>

#include "permuted_rotation.h"
#include "split.h"

using std::cout;    using std::cin;     using std::endl;
using std::string;
using std::vector;


vector<permuted_rotation> rotations(const string& s) {

    vector<permuted_rotation> perm_rotations;
    vector<string> s_vec;
    
    s_vec = split(s);

    for (vector<string>::iterator iter = s_vec.begin();
        iter != s_vec.end(); ++iter) {

        string f_element = *(s_vec.begin());
        vector<string> rot_vec(1, f_element);

        s_vec.erase(s_vec.begin());
        rot_vec += s_vec;
    
        perm_rotations.rotated.push_back(rot_vec);        
    }
    
    return perm_rotations
    
}

string rotate(const string& s)