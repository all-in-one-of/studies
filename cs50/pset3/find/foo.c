#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

int main(int argc, string argv[]){

    // allocate memory for subset
    int *values = malloc((argc-1)*sizeof(int));
    int n = argc-1;
    
    for (int i=1;i<argc;i++) values[i-1] = atoi(argv[i]);

    printf("Presorted: ");
    for (int i=0;i<n;i++) printf("%d ", values[i]);
    printf("\n");

    /*
    sort(values, n);
    printf("Sorted: ");
    for (int i=0;i<n;i++) printf("%d ", values[i]);
    printf("\n");
    */
    
    printf("Subset: ");
    int start = 2;
    int end = n-2;
    printf("start: %d, end: %d - ", start, end);
    int *subset_values = subset(values, start, end);
    for (int i=0;i<end-start;i++) printf("%d ", subset_values[i]);
    printf("\n");
    
    
}