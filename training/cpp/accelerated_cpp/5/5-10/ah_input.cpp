#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
Take argc and argv
Process either file contents or open cin stream
return string or vector
*/

namespace ah {
    string get_input(int argc, char *argv[]) {
        
        string ret_str;
        
        if (argc > 1) {
            string line;
            fstream myfile (argv[1]);
              
            if (myfile.is_open()) {
                while ( getline (myfile,line) ) ret_str+= " " + line;
                myfile.close();
            } else 
                cout << endl << "Unable to open file: " << argv[1] << endl; 
            
        } else {
            cout << "If you would like to input a text file, ";
            cout << "pass the filepath as an argument to this program" << endl;
            cout << "Please enter some input: " << endl;
            getline (cin,ret_str);
        }
        
        //cout << "argc: " << argc << endl;
        //for(int i=0;i<argc;++i) cout << " " << argv[i];
        //cout << endl;
        
        return ret_str;
    }
}