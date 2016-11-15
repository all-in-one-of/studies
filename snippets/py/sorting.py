#!/usr/bin/python

""" 

Todo, Clean up arguments, input from the command line vs input file


"""

import argparse

def main():

    parser = argparse.ArgumentParser()
    
    parser.add_argument('-f', action='store', dest='function_name',
                        help='Function to run')
    parser.add_argument('-i1', dest='input1',
                        default=[], nargs='*',
                        help='Array input1',
                        type=int
                        )
    parser.add_argument('-i2', dest='input2',
                        default=[], nargs='*',
                        help='Array input2',
                        type=int
                        )
    
    parser.add_argument('-if',  action='store', dest='input_file',
                        help='File path')
                        
                        
    results = parser.parse_args()

    input1 = []
    input2 = results.input2

    if results.input_file:
        content = []
        with open(results.input_file) as file:
            content = file.readline()
        
        input1 = content.split()
        input1 = [int(x) for x in input1] 
        print "input sample: ", input1[0], input1[-1] 
    else: 
        input1 = results.input1
    
    if results.function_name == "merge":
        print merge(input1, input2)

    elif results.function_name == "merge_sort":
        print merge_sort(input1)
        
    elif results.function_name == "quick_sort":
        A = input1
        n=len(A)
        print quick_sort(A)[1]
    elif results.function_name == "partition":
        A = input1
        n = len(A)
        print partition(A, 0, n)

    elif results.function_name == "get_med_index":
        A = input1
        
        print get_med_index(A, input2[0],input2[1],input2[2])


def quick_sort(A,m=0):
    r=len(A)
    l=0

    #Basecase
    if r-l <= 1: return A, m

    m += (r-l)-1
    
    A, i = partition(A,l,r)

    L, m = quick_sort( A[0:i], m ) # left side

    R, m = quick_sort( A[i+1:r], m ) # right side

    A = L+[A[i]]+R
    
    return A, m

def partition(A,l,r):
    
    # First
    fi = l 
    
    #Last
    li = r-1 

    #Median
    mi=0
    if((l-r)%2==0): mi = l + ((l-r)/2-1)
    else:            mi = l + ((l-r)/2)
    medi = get_med_index(A,fi,mi,li)    
    
    ind = li
        
    p = A[ind]
    A = swap(A, l, ind)
    
    i = l+1
    n = range(l+1,r)
    
    for j in n:
        if A[j] < p:
            A = swap(A,j,i)
            i+=1
            
    A = swap(A, l, i-1)

    return A, i-1

def swap(A,i1,i2):
    tmp = A[i1]
    A[i1] = A[i2]
    A[i2] = tmp
    return A
    

def get_med_index(A,fi,mi,li):
    
    if (
        A[fi] < A[mi] and A[mi] < A[li]
    or  A[fi] > A[mi] and A[mi] > A[li] ): 
        return mi
    elif (
        A[mi] < A[fi] and A[fi] < A[li]
    or  A[mi] > A[fi] and A[fi] > A[li] ): 
        return fi
    elif (
        A[mi] < A[li] and A[li] < A[fi]
    or  A[mi] > A[li] and A[li] > A[fi] ): 
        return li
    else: return mi
    
def merge_sort(A):
    """ Merge Sort the supplied Interger Array """
    
    n = len(A);
    
    #Check Basecase
    if n < 2: return A
    
    #split array into two: B, Ci
    B = A[:n/2]
    C = A[n/2:]

    if len(B) > 1: B = merge_sort(B)
    if len(C) > 1: C = merge_sort(C)

    return merge(B, C)
    
def merge(A1, A2):
    
    """ Merge two interger arrays in order of smallest to largest"""
    
    j = 0
    k = 0
    B = []
    
    for i in range(len(A1+A2)):
        if A1[j] <= A2[k]:
            B.append(A1[j])
            j+=1
            #No more elements to loop over
            if j == len(A1): break
        
        elif A2[k] < A1[j]:
            B.append(A2[k])
            k+=1
            #No more elements to loop over
            if k == len(A2): break
    
    #if elements are still remaining in either array, append 
    B += A1[j:]
    B += A2[k:]
    return B

def merge_sort_count_inversions(A, num_inversions):
    """ Merge Sort the supplied Interger Array """
    
    #Initialize
    n = len(A)
    left_inversions = right_inversions = split_inversions = 0
    
    #Check Basecase
    if n <= 1: return (A, 0)
    
    #Divide
    B = A[:n/2]
    C = A[n/2:]
    
    #Recursion
    if len(B) > 1: B, left_inversions = merge_sort_count_inversions(B, 0)
    if len(C) > 1: C, right_inversions = merge_sort_count_inversions(C, 0)

    #Merge
    A, split_inversions =  merge_count_inversions(B, C, num_inversions)
    
    num_inversions = split_inversions + left_inversions + right_inversions

    return (A, num_inversions)

def merge_count_inversions(A1, A2, num_inversions):
    """ Merge two interger arrays in order of smallest to largest"""
    
    j = 0
    k = 0
    num_inversions = 0
    B = []
    
    for i in range(len(A1+A2)):
        if A1[j] <= A2[k]:
            B.append(A1[j])
            j+=1
            
            #No more elements to loop over
            if j == len(A1): break
        
        elif A2[k] < A1[j]:
            B.append(A2[k])
            k+=1
            
            #count inversions
            num_inversions += len(A1[j:])
            
            #No more elements to loop over
            if k == len(A2): break

    #if elements are still remaining in either array, append 
    B += A1[j:]
    B += A2[k:]
    
    return B, num_inversions

if __name__ == "__main__":
    main()
    
    
