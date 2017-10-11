/**
 * Resizes a BMP.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bmp.h"

void resizeBMPHeader( BITMAPFILEHEADER *bf, BITMAPINFOHEADER *bi,
                     int *padding, float scaleFactor );

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    // remember inputs
    float f = atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];
    
    // error check f
    if (f <= 0.0 || f > 100.0)
    {
        fprintf(stderr, "Scale factor (f) needs to be in the range: (0.0, 100.0].\n");
        return 2;
    }

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int out_padding = padding;

    BITMAPFILEHEADER out_bf = bf;
    BITMAPINFOHEADER out_bi = bi;

    resizeBMPHeader(&out_bf, &out_bi, &out_padding, f);    
        
    // write outfile's headers
    fwrite(&out_bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&out_bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // if f equals 1 write out an exact copy of the image
    if (f == 1.0) {

        // iterate over rows of scanlines in infile
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++) {
            
            // iterate over pixels in scanline
            for (int j = 0; j < out_bi.biWidth; j++) {
                
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
    
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);
    
            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++) {
                fputc(0x00, outptr);
            }
        }
    
    // if f is greater than 1 we'll scale the image up. Avoid extra memory 
    // expense by only sampling and storing the current scanline
    } else if (f > 1.0) {
        
        // iterate over rows of scanlines in infile
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++) {
        
            // temp storage for current scanline RGB data
            RGBTRIPLE scanline[bi.biWidth];
            
            // multiply scanline f times    
            for (int k = 0; k < f; k++ ) {
            
                // iterate over pixels in scanline
                for (int j = 0; j < bi.biWidth; j++) {
                    
                    // read pixel RGB value
                    if (k == 0)
                        fread(scanline + j, sizeof(RGBTRIPLE), 1, inptr);

                    // mutliply pixel f times
                    for (int l = 0; l < f; l++ )
                        fwrite(scanline + j, sizeof(RGBTRIPLE), 1, outptr);
                }
                
                // write padding
                for (int p = 0; p < out_padding; p++)
                    fputc(0x00, outptr);
            }
            
            // set inptr to next scanline, skip padding
            fseek(inptr, padding, SEEK_CUR);
        }

    // if f is less than 1 we'll scale the image down. Avoid extra memory 
    // expense by only sampling and storing the current scanline
    } else {

        int scale = bi.biWidth/out_bi.biWidth;
        int sampleArea = (bi.biWidth * scale) / bi.biWidth;
        int numSamples = pow(sampleArea,2);

        // temp storage for current scanline pixel data samples
        PIXELSAMPLE sample[out_bi.biWidth];
        memset(sample, 0, sizeof(PIXELSAMPLE) * out_bi.biWidth);

        // iterate over rows of scanlines in infile
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++) {
            
            // iterate over pixels in scanline, sampling values
            for (int j = 0; j < bi.biWidth; j++) {
        
                // sample index
                int index = (int) j / scale;
                if (index >= out_bi.biWidth) break;
        
                // sample pixels 
                RGBTRIPLE in_triple;
                fread(&in_triple, sizeof(RGBTRIPLE), 1, inptr);
                
                sample[index].r += in_triple.rgbtRed;
                sample[index].g += in_triple.rgbtGreen;
                sample[index].b += in_triple.rgbtBlue;
    
                // on the last sample, write out the averaged pixel sample to outfile
                if (i % (int) sampleArea == sampleArea-1 && j % (int) sampleArea == sampleArea-1) {
                    
                    RGBTRIPLE out_triple;
                    
                    // assert, averaged sample values range from 0 - 255
                    out_triple.rgbtRed  = (BYTE) (sample[index].r / numSamples);
                    out_triple.rgbtGreen  = (BYTE) (sample[index].g / numSamples);
                    out_triple.rgbtBlue  = (BYTE) (sample[index].b / numSamples);
                    
                    fwrite(&out_triple, sizeof(RGBTRIPLE), 1, outptr);

                    // reset sample values to start sampling next row
                    sample[index].r = 0;
                    sample[index].g = 0;
                    sample[index].b = 0;
                    
                } 
                
                // end of row - write padding
                if (i % (int) sampleArea == sampleArea-1 && j == biHeight-1)
                    
                    for (int p = 0; p < out_padding; p++)
                        fputc(0x00, outptr);
                
            }

            // set inptr to next scanline, skip padding
            fseek(inptr, padding, SEEK_CUR);

        }
        
    }
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

// manipulate necessary header data to resize a bmp. This assumes that bf and bi 
// have already been initialized with valid bmp header data 
void resizeBMPHeader( BITMAPFILEHEADER *bf, BITMAPINFOHEADER *bi,
                     int *padding, float scaleFactor ) {
    
    if(scaleFactor != 1.0 ) {                     
        
        // height (h) and width (w) in pixels
        double h = round(bi->biHeight * scaleFactor);
        double w = round(bi->biWidth * scaleFactor);
        
        // clamp minimum dimensions to one pixel
        if(h < 1 && h > -1) h = 1 * h/fabs(h);
        if(w < 1) w = 1;
    
        bi->biHeight = (LONG) h;
        bi->biWidth = (LONG) w; 
    
        // size of padding, in bytes
        *padding = (4 - (bi->biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
        // biSizeImage, total size of image in bytes, including padding
        bi->biSizeImage = (DWORD) ( (sizeof(RGBTRIPLE) * bi->biWidth) + *padding) * abs( bi->biHeight);
    
        // bfSize, total size of file in bytes
        bf->bfSize = (DWORD) bi->biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    }
}