/*

Produced Permuted Index with the input phrases

Read each line of the input and generate a set of rotations of that line. 
Each rotation puts the next word of the input in the first position and 
rotates the previous first word to the end of the phrase. Of course, it 
will be important to know where the original phrase ends and where the 
rotated beginning begins.

//Sort the rotations.

Unrotate and write the permuted index, which involves finding the separator, putting
the phrase back together, and writing it properly formatted.
*/

#include <iostream>
#include <string>
#include <vector>

#include "permuted_rotation.h"

using std::cout; using std::cin;     using std::endl;
using std::string;
using std::vector;


int main() {
    
    //Read Lines
    string s;
    getline(cin,s);
    cout << s << endl;

    //Rotate Line for each word, return the rotations and the index of the original first word
    vector<permuted_rotation> perm_rotations = rotations(s);
    

    cout << "Some rotations: " << endl; 
    for(vector<permuted_rotation>::iterator iter1 = perm_rotations.begin();
        iter1!=perm_rotations.end(); ++iter1) {
            for(vector<string>::iterator iter2 = iter1->rotated.begin();
            iter2!=iter1->rotated.end(); ++iter2) 
                cout << *iter2 << " ";
        cout << endl;
    }
    
    cout << endl;

    //Outout the lines formated with the index seperated from the rest of the phrase
    //    rots_ittr
    //    print rots_itter.rotation[0] to rots_ittr.rotation[rots_itter.f_index]
    //    print tab
    //    print rots_itter.rotation[f_index] to rots_itter[end]
     
    return 0;
    
}
