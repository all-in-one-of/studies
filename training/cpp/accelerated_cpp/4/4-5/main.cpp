//Write a function that reads words from an input stream and stores them in a 
//vector. Use that function both to write programs that count the number of 
//words in the input, and to count how many times each word occurred.

#include <iostream>
#include <string>
#include <vector>

using std::cout;    using std::cin;
using std::istream; using std::vector;
using std::string;  using std::endl;

struct Input_Words {
    string word;
    int num_occurances;
};

bool compare(const Input_Words& x, Input_Words& y) {
    return x.word < y.word;
}

istream& read(istream& in, vector<Input_Words>& s) {
    // read input and store it into supplied vector
    
    Input_Words x;
    while(in >> x.word) {
    
        x.num_occurances = 0;
        s.push_back(x);
    }
    
    sort(s.begin(), s.end(), compare);
    vector<int>::iterator itEnd;

    //itEnd = std::adjacent_find (vect.begin() vect.end());
    
    for(int i=0; i<s.size();i++)
        for(int j=0; j<s.size();j++)
            if(s[i].word == s[j].word) ++s[i].num_occurances;

    in.clear();
    return in;
}

int main () {
    
    vector<Input_Words> input;
    read(cin, input);
    
    for(int i=0; i<input.size();i++) {
        cout << input[i].word << " ";
        cout << input[i].num_occurances << endl;
    }
    
    return 0;
    
}