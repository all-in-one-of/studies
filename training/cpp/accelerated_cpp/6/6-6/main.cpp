#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "grade.h"
#include "Student_info.h"

using std::cin;             using std::setprecision;
using std::cout;            using std::sort;
using std::streamsize;      using std::endl;            
using std::string;
using std::max;             using std::vector;
using std::list;

int main() {
    
    // students who did and didn't do all their homework
    vector<Student_info> did, didnt;
    
    // read the student records and partition them
    Student_info student;
    while (read(cin, student)) {
        if (did_all_hw(student))
            did.push_back(student);
        else
            didnt.push_back(student);
    }
    
    // verify that the analyses will show us something
    if (did.empty()) {
        cout << "No student did all the homework!" << endl;
        return 1;
    }
    if (didnt.empty()) {
        cout << "Every student did all the homework!" << endl;
        return 1;
    }
    
    // do the analyses
    write_analysis(cout, "median", grade_analysis, did, didnt, 0);
    write_analysis(cout, "average", grade_analysis, did, didnt, 1);
    write_analysis(cout, "median of homework turned in",
                   grade_analysis, did, didnt, 2);
    return 0;
}