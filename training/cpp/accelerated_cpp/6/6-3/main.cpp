#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


int main (int argc, char *argv[]) {
  
    vector<int> u(10, 100);
    vector<int> v;
    vector <int>::iterator it;

    for(it = u.begin(); it!=u.end(); ++it) {
        cout << *it << endl;
    }

    copy(u.begin(), u.end(), back_inserter(v));

    for(it = v.begin(); it!=v.end(); ++it) {
        cout << *it << endl;
    }
    return 0;
}