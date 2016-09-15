#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

//Using indicies
bool is_palindrome(const string &s) {
    
    for (int i=0; i<(s.size()/2); ++i) 
        if (s[i]!=s[s.size() - i - 1]) return false;

    return true;
}

/*
//Using Iterators
//Allows tricks, like efficiently being able to compare
//a container to a reversed version
bool is_palindrome(const string& s) {
    return equal(s.begin(), s.end(), s.rbegin());
}*/