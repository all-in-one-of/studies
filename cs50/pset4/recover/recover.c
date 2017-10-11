/*
    Recover Jpgs from a raw file
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


int main(int argc, char * argv[]){

    // ensure proper usage
    if (argc != 2) {
        fprintf(stderr, "Usage: ./recover raw.file\n");
        return 1;
    }
    
    char *raw_filename = argv[1];
    
    // open input file 
    FILE *raw_ptr = fopen(raw_filename, "r");
    if (raw_ptr == NULL) {
        fprintf(stderr, "Could not open %s.\n", raw_filename);
        return 2;
    }
    
    int jpg_count = 0;
    char jpg_filename[] = "000.jpg";
    FILE *jpg_ptr = NULL;
    uint8_t raw_buffer[512];
    
    // if 512 blocks are not returned we're at the end of file 
    while (fread(&raw_buffer, 1, 512, raw_ptr) == 512) {
        
        //find jpeg header: 0xff, 0xd8, 0xff, [0xe0,0xef]
        if (raw_buffer[0] == 0xff &&
            raw_buffer[1] == 0xd8 &&
            raw_buffer[2] == 0xff &&
            (raw_buffer[3] & 0xf0) == 0xe0 ) {
            
            // if we have a jpg open already close it
            if (jpg_ptr != NULL) {
                
                fclose(jpg_ptr);
                jpg_count++;
            }
         
            // open new jpg file
            sprintf(jpg_filename, "%03i.jpg", jpg_count);
            jpg_ptr = fopen(jpg_filename, "w");
        
            // write block to current jpg
            fwrite(&raw_buffer, 512, 1, jpg_ptr);
        
                
        } else if (jpg_ptr != NULL) {
            
            // write block to current jpg
            fwrite(&raw_buffer, 512, 1, jpg_ptr);
        
        }
    }
    
    if (jpg_ptr != NULL) {
         
        // end of raw file close open jpg file
        fclose(jpg_ptr);
    }
    
}