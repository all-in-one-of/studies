#!/usr/bin/python

import math


print "a\t\t\t", "b\t\t\t", "c\t\t\t", "d\t\t\t", "e\t\t\t"

for n in range(1,25):
    #a: 2^log(n)
    exp = math.log(n,2)
    one = math.pow(2, exp)
    
    #b: 2^2^log(n)
    exp1 = math.log(n,2)
    exp2 = math.pow(2, exp)
    two = math.pow(2,exp2)

    #c: n^(5/2)
    exp = (5/2.0)
    three = math.pow(n,exp)

    #d: 2^n^2
    exp = math.pow(n,2)
    four = math.pow(2,exp)
    
    #e: n^2*log(n)

    five = math.pow(n,2) * math.log(n,2)

    print one, "\t\t\t", two, "\t\t\t", three, "\t\t\t", four, "\t\t\t", five