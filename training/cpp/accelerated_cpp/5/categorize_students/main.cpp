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
    
    list<Student_info> students;
    list<Student_info> fails;
    Student_info record;
    string::size_type maxlen = 0; // the length of the longest name
    
    // read and store all the students data.
    // Invariant: students contains all the student records read so far
    // maxlen contains the length of the longest name in students
    
    cout << "For each student, please enter their info:" << endl;
    cout << "Name, midterm, final, homework" << endl;
    
    while (read(cin, record)) {
        // find length of longest name
        maxlen = max(maxlen, record.name.size());
        students.push_back(record);
    }
    
    fails = extract_fails(students);
    
    // alphabetize the student records
    students.sort(compare);
    
    cout << endl << "Your student results are:" << endl;
    cout << "Failed students (grade < 60), have been exluded" << endl;
    
    // write the names and grades
    for (list<Student_info>::iterator iter = students.begin();
    iter != students.end(); ++iter) {
        
        // write the name, padded on the right to maxlen + 1 characters
        cout << iter->name
        << string(maxlen + 1 - iter->name.size(), ' ');
        
        // compute and write the grade
        streamsize prec = cout.precision();
        cout << setprecision(3) << iter->grade << setprecision(prec) << endl;
    }
    return 0;
}