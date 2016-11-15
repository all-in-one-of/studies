#!/usr/bin/python

""" usage: maths.py -f function_name -i input_value """

import math

def decimal_to_binary(number):
    """ convert a decimal number to binary number """
    
    binary_num = []

    while (number > 0):
        #Find the largest power of two that is smaller than the number. 
        largest_pow2 = int(math.floor(math.log(number,2)))
        
        #establish number of digits in binary_num
        if (len(binary_num) == 0):
            binary_num = [0 for i in range(largest_pow2+1)]

        #Put a 1 in the digit place for that power of two and 
        #subtract that power of two from the decimal number. 
        binary_num[(len(binary_num)-1)-largest_pow2] = 1;
        number -= math.pow(2,largest_pow2)
        
    return binary_num
    
def decimal_to_hex():
    pass
    
def decimal_to_octal():
    pass
    
def binary_to_octal():
    pass

def binary_to_hex():
    pass

def binary_to_decimal():
    pass

print decimal_to_binary(123)

