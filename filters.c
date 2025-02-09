#include <emscripten.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"

EMSCRIPTEN_KEEPALIVE
void apply_filter(char filter, unsigned char *bmpData, int dataSize)
{
    BITMAPFILEHEADER *bf = (BITMAPFILEHEADER *)bmpData;
    BITMAPINFOHEADER *bi = (BITMAPINFOHEADER *)(bmpData + sizeof(BITMAPFILEHEADER));
    
    int height = abs(bi->biHeight);
    int width = bi->biWidth;
    
    // Image pixel data starts after bfOffBits
    RGBTRIPLE *image = (RGBTRIPLE *)(bmpData + bf->bfOffBits);


    // Apply filter
    switch (filter)
    {
    case 'b': blur(height, width, image); break;
    case 'g': grayscale(height, width, image); break;
    case 'r': reflect(height, width, image); break;
    case 's': sepia(height, width, image); break;
    default:
    fprintf(stderr, "Invalid filter choice.\n");
        return ;
    }
}
