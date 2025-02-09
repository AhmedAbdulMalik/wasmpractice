
#include "helpers.h"
#include <math.h>

// sepia constants for Red
#define SEPIA_RED_1 0.393
#define SEPIA_RED_2 0.769
#define SEPIA_RED_3 0.189

// sepia constants for Green
#define SEPIA_GREEN_1 0.349
#define SEPIA_GREEN_2 0.686
#define SEPIA_GREEN_3 0.168

// sepia constants for Blue
#define SEPIA_BLUE_1 0.272
#define SEPIA_BLUE_2 0.534
#define SEPIA_BLUE_3 0.131

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE *image)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int index = i * width + j;
            float sum = image[index].rgbtBlue + image[index].rgbtRed + image[index].rgbtGreen;
            int avg = (int) round(sum / 3.0);
            image[index].rgbtBlue = avg;
            image[index].rgbtRed = avg;
            image[index].rgbtGreen = avg;
        }
    }
}



// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE *image)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int index = i * width + j;

            int sepiaRed = round(SEPIA_RED_1 * image[index].rgbtRed +
                                 SEPIA_RED_2 * image[index].rgbtGreen +
                                 SEPIA_RED_3 * image[index].rgbtBlue);
            int sepiaGreen = round(SEPIA_GREEN_1 * image[index].rgbtRed +
                                   SEPIA_GREEN_2 * image[index].rgbtGreen +
                                   SEPIA_GREEN_3 * image[index].rgbtBlue);
            int sepiaBlue = round(SEPIA_BLUE_1 * image[index].rgbtRed +
                                  SEPIA_BLUE_2 * image[index].rgbtGreen +
                                  SEPIA_BLUE_3 * image[index].rgbtBlue);

            // Ensure values do not exceed 255
            image[index].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[index].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[index].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
}

// Reflect image horizontally

// helper function
void swaprgb(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE temp = *a;
    *a = *b;
    *b = temp;
}
//going use it later

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE *image)
{
    int middle = width / 2;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < middle; j++)
        {
            int leftIndex = i * width + j;
            int rightIndex = i * width + (width - j - 1);

            // Use swaprgb() to swap pixels
            swaprgb(&image[leftIndex], &image[rightIndex]);
        }
    }
}


// Blur image
void blur(int height, int width, RGBTRIPLE *image)
{
    // Create a copy of the image
    RGBTRIPLE copy[height * width];

    for (int i = 0; i < height * width; i++)
    {
        copy[i] = image[i];
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0, count = 0;
            int index = i * width + j;

            // Iterate through neighboring pixels
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Check if within bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        int neighborIndex = ni * width + nj;
                        sumRed += copy[neighborIndex].rgbtRed;
                        sumGreen += copy[neighborIndex].rgbtGreen;
                        sumBlue += copy[neighborIndex].rgbtBlue;
                        count++;
                    }
                }
            }

            // Compute the blurred pixel values
            image[index].rgbtRed = round((float) sumRed / count);
            image[index].rgbtGreen = round((float) sumGreen / count);
            image[index].rgbtBlue = round((float) sumBlue / count);
        }
    }
}


