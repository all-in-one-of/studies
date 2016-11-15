#include <iostream>
#include <string>

using std::cout;    using std::cin;     using std::endl;
using std::string;

int main() {
    
    string s1;
    cout << "Get input using simple cin: " << endl;
    cin >> s1;
    cout << "Input: " << s1 << endl;
    cin.clear();
    
    string s2;
    cout << "Get input using getline(): " << endl;
    getline(cin, s2);
    cout << "Input: " << s2 << endl;
    
    string s3;
    cout << "Get while testing for EOF: " << endl;
    while(cin>>s3) 
        cout << "Input: " << s3 << endl;
    cin.clear();
    
    return 0;
}