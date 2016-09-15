#ifndef GUARD_grade_h
#define GUARD_grade_h

// grade.h
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include "Student_info.h"

double grade(double, double, double);
double grade(double, double, const std::vector<double>&);
double grade(const Student_info&);
double grade_aux(const Student_info& s);
double average_grade(const Student_info& s);

bool fgrade(const Student_info& s);
std::list<Student_info> extract_fails(std::list<Student_info>& students);

double median(const std::vector<double>&);
double average(const std::vector<double>&);
double optimistic_median(const Student_info& s);

double grade_analysis(const std::vector<Student_info>& students, int type);
void write_analysis(std::ostream& out, 
                    const std::string& name,
                    double analysis(const std::vector<Student_info>&, int type),
                    const std::vector<Student_info>& did,
                    const std::vector<Student_info>& didnt,
                    int type);

#endif