
/*
Take argc and argv
Process either file contents or open cin stream
return string or vector
*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

#include "../ah_strings/ah_split.h"

using namespace std;

namespace ah {
    void get_input(int argc, char *argv[], string& input) {
        
        if (argc > 1) {
            string line;
            fstream myfile (argv[1]);
              
            if (myfile.is_open()) {
                while ( getline (myfile,line) ) input+=line;
                myfile.close();
            } else 
                cout << endl << "Unable to open file: " << argv[1] << endl; 
            
        } else {
            cout << "If you would like to input a text file, ";
            cout << "pass the filepath as an argument to this program" << endl;
            cout << "Please enter some input: " << endl;
            getline (cin,input);
        }
        
        //cout << "argc: " << argc << endl;
        //for(int i=0;i<argc;++i) cout << " " << argv[i];
        //cout << endl;
        
    }

    void get_input(int argc, char *argv[], vector<string>& input_v) {
        string input_s; 
        get_input(argc, argv, input_s);
        vector <string> tmp = ah::split(input_s);
        copy(tmp.begin(), tmp.end(), back_inserter(input_v));
    }
    
}
