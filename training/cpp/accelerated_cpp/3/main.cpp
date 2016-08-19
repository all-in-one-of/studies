//TODO: test calculating quartile indices 
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::sort;
using std::endl;
using std::unique;

int main() {
    
    //Get Values from user input
    vector<string> values;      string x;
    cout << "Enter some numbers, Press Ctrl-D when done: " << endl ;
    while(cin>>x) values.push_back(x);
    cout << "The numbers you entered are: " << endl;
    for(int i = 0; i <= values.size()-1; i++)
        cout << values[i] << " ";
    cout << endl << endl;
    
    //Calc longest and shortest strings
    unsigned int longest = 0;
    unsigned int shortest = 999999;
    for(int i = 0; i <= values.size()-1; i++) {
        const string::size_type length = values[i].length();
        if (length > longest) longest = length;
        else if (length < shortest) shortest = length;
    }
    cout << "Shortest string: " << shortest << " digits" << endl;
    cout << "Longest string: " << longest << " digits" << endl << endl;
    
    //Sort Values
    sort(values.begin(), values.end());
    cout << "The numbers once sorted are: " << endl;
    for(int i = 0; i <= values.size()-1; i++)
        cout << values[i] << " ";
    cout << endl << endl;
    
    //Remove repeated Values
    values.erase(unique(values.begin(), values.end()) , values.end()  );
    cout << "The numbers once unique are: " << endl;
    for(int i = 0; i <= values.size()-1; i++)
        cout << values[i] << " ";
    cout << endl;
    
    return 0;
}
