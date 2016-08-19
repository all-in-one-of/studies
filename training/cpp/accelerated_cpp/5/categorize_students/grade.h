#ifndef GUARD_grade_h
#define GUARD_grade_h

// grade.h
#include <vector>
#include <list>
#include "Student_info.h"
double grade(double, double, double);
double grade(double, double, const std::vector<double>&);
double grade(const Student_info&);
std::list<Student_info> extract_fails(std::list<Student_info>& students);
bool fgrade(const Student_info& s);

#endif