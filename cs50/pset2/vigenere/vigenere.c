#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]) {
    
    // check number of args
    if (argc != 2) {
        printf("error: too many arguments, please supply one key\n");
        return 1;
    }

    // check for alphabetic key
    string k = argv[1];    
    for (int i=0; i<strlen(k); i++) { 
        if (!isalpha(k[i])) {
            printf("error: key must be alphabetic\n");
            return 1;
        }
    }
    
    printf("plaintext: ");
    string p = get_string();
    
    printf("ciphertext: ");
    
    //ascii table values
    int alpha_len = 26;
    int upper_min = 65;
    int lower_min = 97;
    
    //key index
    int j = 0;
    
    // step through characters of input p
    for (int i=0; i<strlen(p); i++) {
        
        // get the jth char in k, 
        // cycle index if we go over length of k
        // set to uppercase and normalize value
        int key = ( (int) toupper( k[j % strlen(k)] ) ) - upper_min;
        
        // if char is uppercase, chipher values should cycle through 65-91 ascii values
        if ( isupper(p[i]) ) {
            
            printf("%c", ((char) ( p[i] + key - upper_min ) % alpha_len + upper_min ));
            j++; 
            
        // if char is lowercase, chipher values should cycle through 97-123 ascii values            
        } else if ( islower(p[i]) ) {
            
            printf("%c", ((char) ( p[i] + key - lower_min ) % alpha_len + lower_min ));
            j++;
            
        // character is not alphabetic, print unchanged, do not increment key index
        } else {
            
            printf("%c", p[i]);
        
        }
        
    }
    
    printf("\n");
    
}