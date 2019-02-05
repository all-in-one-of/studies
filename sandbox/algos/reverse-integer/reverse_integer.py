#! /usr/bin/python

import math

def reverse(x):

    sign =  x/abs(x)
    x = abs(X)
    last_digit = x % 10
    base = int(x/10)

    if base == 0:
        return last_digit

    else:

        mult = math.pow(10,int(math.log10(x)))
        base = reverse(base)
        return int(last_digit*mult + base) * sign
