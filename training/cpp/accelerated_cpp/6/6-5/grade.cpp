#include <algorithm>    // to get the declaration of sort
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <vector>

#include "grade.h"
#include "Student_info.h"

using namespace std;

// definitions for the grade functions from §4.1/52, §4.1.2/54 and §4.2.2/63

// compute a student's overall grade from midterm and final exam grades and homework grade
double grade(double midterm, double final, double homework)  {
    return 0.2 * midterm + 0.4 * final + 0.4 * homework; 
}

// compute a student's overall grade from midterm and final exam grades
// and vector of homework grades.
// this function does not copy its argument, because median does so for us.
double grade(double midterm, double final, const vector<double>& hw) {
     if (hw.size() == 0)
     throw domain_error("student has done no homework");
     return grade(midterm, final, median(hw));
}

double grade(const Student_info& s)  {
    return grade(s.midterm, s.final, s.homework);
}

// version 4: use list instead of vector
list<Student_info> extract_fails(list<Student_info>& students) {
     list<Student_info> fail;
     list<Student_info>::iterator iter = students.begin();
     while (iter != students.end()) {
         if (fgrade(*iter)) {
             fail.push_back(*iter);
             iter = students.erase(iter);
        } else ++iter;
     }
    return fail;
}

bool fgrade(const Student_info& s) {
    return grade(s) < 60;
}

double grade_aux(const Student_info& s) {
    try {
        return grade(s);
    } catch (domain_error) {
        return grade(s.midterm, s.final, 0) ;
    }
}

double median(vector<double> vec) {
    typedef vector<double>::size_type vec_sz;
    vec_sz size = vec.size();
    if (size == 0)
    throw domain_error("median of an empty vector");
    sort(vec.begin(), vec.end());
    vec_sz mid = size / 2;
    
    return size % 2 == 0 ? (vec[mid] + vec[mid-1]) / 2 : vec[mid];
}

double median_analysis(const vector<Student_info>& students) {
     vector<double> grades;
     transform(students.begin(), students.end(),
     back_inserter(grades), grade_aux);
     return median(grades);
}

double average(const vector<double>& v) {
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double average_grade(const Student_info& s) {
    return grade(s.midterm, s.final, average(s.homework));
}

double average_analysis(const vector<Student_info>& students) {
    vector<double> grades;
    transform(students.begin(), students.end(),
    back_inserter(grades), average_grade);
    return average(grades);
}

// median of the nonzero elements of s.homework, or 0 if no such elements exist
double optimistic_median(const Student_info& s) {
    vector<double> nonzero;
    remove_copy(s.homework.begin(), s.homework.end(),
    back_inserter(nonzero), 0);
    
    if (nonzero.empty())
    return grade(s.midterm, s.final, 0);
    else
    return grade(s.midterm, s.final, median(nonzero));
}

double optimistic_median_analysis (const vector<Student_info>& students) {
    vector<double> grades;
    transform(students.begin(), students.end(),
    back_inserter(grades), grade_aux);
    return median(grades);
}

void write_analysis(ostream& out, const string& name,
    double analysis(const vector<Student_info>&),
    const vector<Student_info>& did,
    const vector<Student_info>& didnt) {
    out << name << ": median(did) = " << analysis(did) <<
        ", median(didnt) = " << analysis(didnt) << endl;
}