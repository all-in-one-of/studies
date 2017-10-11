#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void clear(void); 
void quit();
char * get_string(char *);


int main() {
    
    char * input = "";
    char * exit_signal_0 = "exit";
    char * exit_signal_1 = "quit";
    char * prompt = "Please Enter a string ('exit' or 'quit' to end)";
    
    int cmp_0;
    int cmp_1;
    cmp_0 = strcmp(input, exit_signal_0);
    cmp_1 = strcmp(input, exit_signal_1);

    while(cmp_0 != 0 && cmp_1 != 0) {
        clear();
        input = get_string(prompt);
        printf("Your string is: %s\n", input);
        cmp_0 = strcmp(input, exit_signal_0);
        cmp_1 = strcmp(input, exit_signal_1);
        sleep(2);
    }
    
    free(input); 

}

void clear(void) {
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

void quit() {
    fprintf(stderr, "memory exhausted\n");
    exit(1);
}

char * get_string(char * prompt) {

    int max = 20;
    char* name = (char*) malloc(max); /* allocate buffer */
    if (name == 0) quit();

    printf("%s: ", prompt);

    while (1) { /* skip leading whitespace */
        int c = getchar();
        if (c == EOF) break; /* end of file */
        if (!isspace(c)) {
             ungetc(c, stdin);
             break;
        }
    }

    int i = 0;
    while (1) {
        int c = getchar();
        if (isspace(c) || c == EOF) { /* at end, add terminating zero */
            name[i] = 0;
            break;
        }
        name[i] = c;
        if (i == max - 1) { /* buffer full */
            max += max;
            name = (char*) realloc(name, max); /* get a new and larger buffer */
            if (name == 0) quit();
        }
        i++;
    }

    return name;
}