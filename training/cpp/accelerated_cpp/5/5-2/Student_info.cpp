// source file for Student_info-related functions
#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Student_info.h"
#include "grade.h"
#include "split.h"

using namespace std;

bool compare(const Student_info& x, const Student_info& y) {
    return x.name < y.name;
}

istream& read(istream& is, Student_info& s) {
    // read and store the student's name and midterm and final exam grades
    is >> s.name >> s.midterm >> s.final;
    read_hw(is, s.homework); // read and store all the student's homework grades
    //add try catch domain_error
    try {
        s.grade = grade(s.midterm, s.final, s.homework);
    } catch (domain_error e) {
        cout << s.name << " " << e.what() << endl;
        s.grade = 0;
    }
    return is;
}

int read(ifstream myfile, Student_info& s) {
    string line;

    if (myfile.is_open()) {
        while ( getline (myfile,line) ) {
            
            //Assuming line is the format:
            //Name midterm final hw1 hw1 ... hwn
            vector<string> line_v = split(line);
            s.name = atof(line_v[0].c_str());
            s.midterm = atof(line_v[1].c_str());
            s.final = atof(line_v[2].c_str());
            for (int i = 3; i<line_v.size(); ++i) 
                s.homework.push_back(atof(line_v[i].c_str()));

            try {
                s.grade = grade(s.midterm, s.final, s.homework);
            } catch (domain_error e) {
                cout << s.name << " " << e.what() << endl;
                s.grade = 0;
            }
        }
        myfile.close();
        return 0;
    }
    
    return 0;
}

// read homework grades from an input stream into a 'vector'
istream& read_hw(istream& in, vector<double>& hw) {
    if (in) {
        
        // get rid of previous contents
        hw.clear();
        
        // read homework grades
        double x;
        while (in >> x) hw.push_back(x);
        
        // clear the stream so that input will work for the next student
        in.clear();
    }
    return in;
}
