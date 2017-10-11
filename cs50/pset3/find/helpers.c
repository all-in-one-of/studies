/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

int * subset(int array[], int start, int end);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    
    // handle base case, n is less than one
    if (n < 1) return false;
    
    // if n is one return if value is found or not
    if (n == 1) return (values[0] == value);

    // calculate mid index, handle case for odd array size
    int mid = (n/2);
    if (n%2 == 0) mid--;

    // if value is found return true
    if (values[mid] == value) {
        return true;

    } else {

        // if value is less than mid value, search subsequent values    
        if (values[mid] < value) {
            
            int *subset_values = subset(values, mid+1, n);
            int subset_n = n-(mid+1);
            return search(value, subset_values, subset_n);
        
        // else value is greater than mid value, search proceeding values
        } else {
            
            int *subset_values = subset(values, 0, mid);
            int subset_n = mid;
            return search(value, subset_values, subset_n);
        
        }

    }
    
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // bubble sort, calculate number of swap iterations we need to do
    int swaps = n-1;
    
    // keep sorting until we've completed all swap iterations
    while ( swaps > 0 ) {
    
        // loop over each value left in the current swap iteration
        for (int i=0; i<swaps; i++ ) {
            
            // if values are out of order swap them
            if (values[i] > values[i+1]) {
            
                int lrg_val = values[i];
                int sml_val = values[i+1];
            
                values[i] = sml_val;
                values[i+1] = lrg_val;
            } 
            
        }
        
        // swap iteration complete, decrement number of swaps to do
        swaps--;
        
    }
    
    return;
}

// return a subset of the input array with the range: [start, end)
int * subset(int array[], int start, int end) {
    
    // allocate memory for subset
    int *subset = malloc((end-start)*sizeof(int));
    
    for (int i=start; i<end; i++) {
        subset[i-start] = array[i];
    }
    
    return subset;
}
