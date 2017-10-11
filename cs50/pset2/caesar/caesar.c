#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]) {
    
    if (argc != 2) {
        printf("err");
        return 1;
    }
    
    char *ref;
    int key = (int) strtol(argv[1], &ref, 10);
    
    printf("plaintext: ");
    string p = get_string();
    
    printf("ciphertext: ");
    
    //ascii table values
    int alpha_len = 26;
    int upper_min = 65;
    int lower_min = 97;    
    
    // step through characters of input s
    for (int i=0; i<strlen(p); i++) {
        
        // if char is uppercase, chipher values should cycle through 65-91 ascii values
        if ( isupper(p[i]) ) {
            
            printf("%c", ((char) ( p[i] + key - upper_min ) % alpha_len + upper_min ));
            
        // if char is lowercase, chipher values should cycle through 97-123 ascii values            
        } else if ( islower(p[i]) ) {
            
            printf("%c", ((char) ( p[i] + key - lower_min ) % alpha_len + lower_min ));
            
        // character is not alphabetic, print unchanged
        } else {
            
            printf("%c", p[i]);
        
        }
        
    }
    
    printf("\n");
    
}