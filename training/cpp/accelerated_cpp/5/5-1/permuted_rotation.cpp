
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
    
    for (int i=0; i<s_vec.size(); ++i) {

        permuted_rotation rotation;
        string l_element = s_vec[s_vec.size()-1];
        
        vector<string> t_vec(1, l_element);
    
        t_vec.insert(t_vec.end(), s_vec.begin(), s_vec.end()-1);
        s_vec = t_vec;
        
        rotation.rotated = s_vec;       
        rotation.f_index = 0;
        perm_rotations.push_back(rotation);
    }
    cout << endl;
    return perm_rotations;
    
}
