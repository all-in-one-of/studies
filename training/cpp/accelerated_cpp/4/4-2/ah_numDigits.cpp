#include <sstream>
#include "ah_numDigits.h"

int num_digits(int number) {
    int digits = 1;
    while (number /= 10) ++digits; 
    return digits;
}

double num_digits(double number) {
    
    std::ostringstream strs;
    strs << number;
    std::string str = strs.str();

    return str.size();
}