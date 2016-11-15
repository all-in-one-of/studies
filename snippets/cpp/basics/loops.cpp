#include <vector>
using std::vector;

#include <iostream>
using std::cout;    using std::cin;     using std::endl;

int main() {

    vector v;

    //Loop over a container using indices
    for (vector<string>::size_type i = 0; i != v.size(); ++i)
        cout << v[i] << endl;
 
    //Loop over a container using iterator
    for (vector<string>::iterator iter = v.begin();
         iter != v.end(); ++iter)
        cout << *iter << endl;
}