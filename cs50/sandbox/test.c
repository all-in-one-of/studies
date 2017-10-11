#include <stdlib.h>
#include <stdio.h>

int main() {
    
    long * head = malloc(sizeof(long) * 16); 
    long * tail = head;
    
    printf("sizeOfHead %lu \n", sizeof(long) * 16);
    
    int posOfTail = (head - tail);
    printf("posOfTail %d \n", posOfTail);
    

    // populate list    
    //while (tail - head < (16 * sizeof(*head))) {
    
    int v = 2;
    
    while (tail - head < 16) {
          
        *tail = v; 

        posOfTail = (tail - head);
        
        printf("index %d ", (int) (posOfTail));
        printf("posOfTail %d \n", posOfTail);

        tail += 1;//sizeof(*head);
        v*=2;

    }

    printf("\n");
    
    for (int i = 0; i<16; i++) {
        
        long offset = *(head + i);
        printf("offset %d: %ld \n", i, offset);
        printf("index  %d: %ld \n", i, head[i]);

    }

    
    free(head);

    return 0;
    
}