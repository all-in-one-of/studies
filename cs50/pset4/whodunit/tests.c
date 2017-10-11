#include <stdio.h>
#include <stdint.h>


typedef struct
{
    uint8_t rgbtBlue;
    uint8_t rgbtGreen;
    uint8_t rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;

int main(void){
    
    printf("size of RGBTRIPLE: %ld\n", sizeof(RGBTRIPLE));
    
    return 1;
}