#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void init(void);
void draw(void);
bool won(void);

int board[9][9];
int d = -1;

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2) {
        printf("Usage: test d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    
    init();
    draw();
    
    if (won()) printf("WON\n");
    
}

void init(void) {
    
    int n = d*d;
    
    for (int i=0; i<d; i++) {
        for (int j=0; j<d; j++) {
        
            board[i][j] = ((j + (i*d))+2)%n; 
        }
        
    }
    
}

void draw(void)
{
    for (int i=0; i<d; i++) {
        for (int j=0; j<d; j++) {
            
            // print values, ignore 0
            if( board[i][j] == 0) printf("    ");
            else printf("%2d  ", board[i][j]); 
            
            // if we're at the end of a row print newline
            if (j == d-1) printf("\n");
        
        }
    }
}


bool won(void)
{

    int n = d*d;
    int index = 0;

    for (int i=0; i<d; i++) {
        
        for(int j=0; j<d && index<n-3; j++ ) {

            index = (j + (i*d));
            
            int r = (index+1) / d;
            int c = (index+1) % d;
            
            // if value at index+1 is smaller than current index, board is not yet in order
            if (board[r][c] < board[i][j]) return false;
            
        }
    }
    
    return true;
}
