// source file for Student_info-related functions
#include <algorithm>
#include <stdexcept>
#include <iostream>

#include "Student_info.h"
#include "grade.h"

using std::istream; using std::vector;
using std::list;    using std::domain_error;
using std::cout;    using std::endl;

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

bool did_all_hw(const Student_info& s) {
    return ((find(s.homework.begin(), s.homework.end(), 0))
            == s.homework.end());
}