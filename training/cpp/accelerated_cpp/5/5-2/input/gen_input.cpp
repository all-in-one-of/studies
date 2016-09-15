//Generate input for categorize students program
//Name MidTerm Exam HomeWork
//EG: Frank 100 82 90 87 65

// writing on a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>

using namespace std;

vector<string> get_names() {
    
    vector<string> names;
    names.push_back("Frank");
    names.push_back("George");
    names.push_back("Cindy");
    names.push_back("Lisa");
    return names;
}

int main () {
  ofstream myfile ("10000_students.txt");
  
  if (myfile.is_open()) {

    vector<string> names = get_names();
      
    for(int i=0;i<10000;++i) {
        srand(time(NULL)+i);
        
        int names_i = rand() % names.size();        
        int midterm = rand() % 100;
        int exam = rand() % 100;
        int hw1 = rand() % 100;
        int hw2 = rand() % 100;
        int hw3 = rand() % 100;

        myfile << names[names_i] << " " << midterm << " "
        << exam << " " << hw1 << " " << hw2 << " " << hw3 << "\n";
    }
    myfile.close();
    
  }
  else cout << "Unable to open file";
  return 0;
}