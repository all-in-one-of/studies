#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "grade.h"
#include "Student_info.h"

using namespace std;

int main() {
    
    //Vector or List
    typedef list<Student_info> s_info_vec;
    //typedef vector<Student_info> s_info_vec;
    
    //input file, or input stream
    string filename = "10000_students";
    fstream input ("./input/"+filename+".txt");
    cout << "Reading input from "+filename+".txt ... " << endl;
    //istream input = cin;
    //cout << "Please enter student info: " << endl;
    //cout << "Name, midterm, final, homework"
    
    s_info_vec students;
    s_info_vec fails;
    Student_info record;
    string::size_type maxlen = 0; // the length of the longest name
    
    clock_t starttime = clock();

    //Process Input
    while (read(input, record)) {
        // find length of longest name
        maxlen = max(maxlen, record.name.size());
        students.push_back(record);
    }
    
    clock_t endtime = clock();
    double timediff = double(endtime - starttime); // CLOCKS_PER_SEC
    
    fails = extract_fails(students, 20);
    
    //Output
    
    // alphabetize the student records
    //students.sort(compare);
    
    /*cout << endl << "Your student results are:" << endl;
    cout << "(Failed students have been exluded)" << endl;
    
    // write the names and grades
    for (vector<Student_info>::iterator iter = students.begin();
    iter != students.end(); ++iter) {
        
        // write the name, padded on the right to maxlen + 1 characters
        cout << iter->name
        << string(maxlen + 1 - iter->name.size(), ' ');
        
        // compute and write the grade
        streamsize prec = cout.precision();
        cout << setprecision(3) << iter->grade << setprecision(prec) << endl;
    }*/
    
    cout << "List: " << timediff << endl;
    
    return 0;
}