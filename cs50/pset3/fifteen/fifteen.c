/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

// utilities
int * find_tile(int tile);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(300000);
        }

        // sleep thread for animation's sake
        usleep(300000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(1500000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int n = d*d;
    
    for (int i=0; i<d; i++) {
        for (int j=0; j<d; j++) {
            board[i][j] = (n - 1) - (j + (i*d)); 
        }
        
        if (d%2 == 0) { 
            board[d-1][d-2] = 2;
            board[d-1][d-3] = 1;
        }
        
    }
    
}

/**
 * Prints the board in its current state.
 */
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

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    
    int n = d*d;
    
    // ensure that we're trying to move a tile withen the boards tile range
    if (tile < 1 || tile >= n) return false;
    
    // search board for tile pos
    int *t_pos = find_tile(tile);
    
    // search board for empty tile pos
    int *e_pos = find_tile(0);
    
    // if tile and empty tile are on the same row, check that empty tile is also beside tile
    // otherwise tile and empty tile are on the same col, check that empty tile is either above or below
    if ( (t_pos[0] == e_pos[0] && ( t_pos[1] - 1 == e_pos[1] || t_pos[1] + 1 == e_pos[1]))
      || (t_pos[1] == e_pos[1] && ( t_pos[0] - 1 == e_pos[0] || t_pos[0] + 1 == e_pos[0])) ) {
    
        // swap tile and empty tile
        board[e_pos[0]][e_pos[1]] = tile;
        board[t_pos[0]][t_pos[1]] = 0;
    
        return true;
    
    } 
    
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{

    // init board length and index variable
    int n = d*d;
    int index = 0;

    // loop over board rows
    for (int i=0; i<d; i++) {
        
        // loop over board columns
        // cut loop short, we dont need to compare to last value on the board
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

// given a tile number, return the row and col position of the tile
int * find_tile(int tile) {
    
    // intialize pointer to pos array 
    int *pos = malloc(2*sizeof(int));
    
    // perform linear search of board
    for (int i=0; i<d; i++) {
        for (int j=0; j<d; j++) {
            if (board[i][j] == tile) {
                pos[0] = i;
                pos[1] = j;
            }
            
        }
    }

    return pos;
    
}