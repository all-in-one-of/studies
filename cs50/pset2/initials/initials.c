#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
   
    // prompt for user's name
    string s = get_string();
    
    // step through characters of user's name
    for (int i=0; i<strlen(s); i++) {
    
        // check if currect char is the begining of a word
        if ( !isspace(s[i]) && (i==0 || isspace(s[i-1])) ){
            
            // print uppercase intial
            printf("%c", toupper(s[i]));
            
        }
        
    }
    
    printf("\n");
}
