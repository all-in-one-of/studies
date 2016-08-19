#include <iostream>
#include <iomanip>
#include <cmath>
#include "ah_numDigits.h"
//main

int main () {
    double i = 0.0;
    double value = i*i; 
    
    //invariant we have output i squares so far
    while (value < 1000.0) {
        
        //calc num digits for width offset
        double v_d = num_digits(value);
        double i_d = num_digits(i);
        
        std::cout << i << std::setw(8 + v_d - i_d) << value << " " << v_d << " " << i_d 
                  << std::endl << std::setw(0);
                  
        ++i;
        value = (i*i);
                  
    }
    
    return 0;
                
}