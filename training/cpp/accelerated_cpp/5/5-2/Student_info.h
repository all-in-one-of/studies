#ifndef GUARD_Student_info
#define GUARD_Student_info

// Student_info.h header file
#include <iostream>
#include <string>
#include <vector>
#include <list>

struct Student_info {
    std::string name;
    double midterm, final;
    std::vector<double> homework;
    double grade;
};

bool compare(const Student_info&, const Student_info&);
std::istream& read(std::istream&, Student_info&);
int read(std::string, Student_info&);
std::istream& read_hw(std::istream&, std::vector<double>&);

#endif