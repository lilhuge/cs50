#include <stdio.h>
#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)            // Runs through each row of pixels
    {
        for (int j = 0; j < width; j++)         // Runs through each column of pixels
        {
            float average = round((float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;        // Calculates average RGB value and rounds up
            image[i][j].rgbtRed = average;          // Sets new RGB values to calculated average (all equal values)

            //printf("%i  %i  %i    ", image[i][j].rgbtBlue, image[i][j].rgbtGreen, image[i][j].rgbtRed);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)            // Runs through each row of pixels
    {
        for (int j = 0; j < width / 2; j++)         // Runs through each column of pixels until middle of image
        {
            RGBTRIPLE temp = image[i][j];                   // Swaps first pixel with last pixel and continues until middle of image
            image[i][j] = image[i][width - (1 + j)];
            image[i][width - (1 + j)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)            // Runs through each row of pixels
    {
        for (int j = 0; j < width; j++)             // Runs through each column of pixels
        {
            if (i == 0 && j > 0 && j < width - 1)
            {
                int average_blue = round((float)(image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                                 image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6);
                new_image[i][j].rgbtBlue = average_blue;

                int average_green = round((float)(image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                                  image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6);
                new_image[i][j].rgbtGreen = average_green;

                int average_red = round((float)(image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                                image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6);
                new_image[i][j].rgbtRed = average_red;
            }                                                   // Top row of image

            else if (i == 0 && j == 0)
            {
                int average_blue = round((float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                                 image[i + 1][j + 1].rgbtBlue) / 4);
                new_image[i][j].rgbtBlue = average_blue;

                int average_green = round((float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                                  image[i + 1][j + 1].rgbtGreen) / 4);
                new_image[i][j].rgbtGreen = average_green;

                int average_red = round((float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed +
                                                image[i + 1][j + 1].rgbtRed) / 4);
                new_image[i][j].rgbtRed = average_red;
            }                                                   // Top left corner of image

            else if (i == 0 && j == width - 1)
            {
                int average_blue = round((float)(image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                                 image[i + 1][j].rgbtBlue) / 4);
                new_image[i][j].rgbtBlue = average_blue;

                int average_green = round((float)(image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                                  image[i + 1][j].rgbtGreen) / 4);
                new_image[i][j].rgbtGreen = average_green;

                int average_red = round((float)(image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                                image[i + 1][j].rgbtRed) / 4);
                new_image[i][j].rgbtRed = average_red;
            }                                                   // Top right corner of image



            else if (i == height - 1 && j > 0 && j < width - 1)
            {
                int average_blue = round((float)(image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                                 image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue) / 6);
                new_image[i][j].rgbtBlue = average_blue;

                int average_green = round((float)(image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                                  image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen) / 6);
                new_image[i][j].rgbtGreen = average_green;

                int average_red = round((float)(image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                                image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed) / 6);
                new_image[i][j].rgbtRed = average_red;
            }                                                   // Bottom row of image

            else if (i == height - 1 && j == 0)
            {
                int average_blue = round((float)(image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue +
                                                 image[i][j + 1].rgbtBlue) / 4);
                new_image[i][j].rgbtBlue = average_blue;

                int average_green = round((float)(image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j].rgbtGreen +
                                                  image[i][j + 1].rgbtGreen) / 4);
                new_image[i][j].rgbtGreen = average_green;

                int average_red = round((float)(image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed +
                                                image[i][j + 1].rgbtRed) / 4);
                new_image[i][j].rgbtRed = average_red;
            }                                                   // Bottom left corner of image

            else if (i == height - 1 && j == width - 1)
            {
                int average_blue = round((float)(image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                                                 image[i][j].rgbtBlue) / 4);
                new_image[i][j].rgbtBlue = average_blue;

                int average_green = round((float)(image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                                                  image[i][j].rgbtGreen) / 4);
                new_image[i][j].rgbtGreen = average_green;

                int average_red = round((float)(image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed +
                                                image[i][j].rgbtRed) / 4);
                new_image[i][j].rgbtRed = average_red;
            }                                                   // Bottom right corner of image




            else if (i > 0 && i < height - 1 && j == 0)
            {
                int average_blue = round((float)(image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue +
                                                 image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6);
                new_image[i][j].rgbtBlue = average_blue;

                int average_green = round((float)(image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j].rgbtGreen +
                                                  image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6);
                new_image[i][j].rgbtGreen = average_green;

                int average_red = round((float)(image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed +
                                                image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6);
                new_image[i][j].rgbtRed = average_red;
            }                                                   // Leftmost column of image

            else if (i > 0 && i < height - 1 && j == width - 1)
            {
                int average_blue = round((float)(image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                                                 image[i][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 6);
                new_image[i][j].rgbtBlue = average_blue;

                int average_green = round((float)(image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                                                  image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 6);
                new_image[i][j].rgbtGreen = average_green;

                int average_red = round((float)(image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed +
                                                image[i][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) / 6);
                new_image[i][j].rgbtRed = average_red;
            }                                                   // Rightmost column

            else                // Anything else
            {
                int average_blue = round((float)(image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                                 image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + 
                                                 image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9);
                new_image[i][j].rgbtBlue = average_blue;

                int average_green = round((float)(image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                                  image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + 
                                                  image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9);
                new_image[i][j].rgbtGreen = average_green;

                int average_red = round((float)(image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                                image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + 
                                                image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9);
                new_image[i][j].rgbtRed = average_red;
            }

        }
    }
    for (int i = 0; i < height; i++)            // Runs through each row of pixels
    {
        for (int j = 0; j < width; j++)             // Runs through each column of pixels
        {
            image[i][j].rgbtBlue = new_image[i][j].rgbtBlue;
            image[i][j].rgbtGreen = new_image[i][j].rgbtGreen;
            image[i][j].rgbtRed = new_image[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_image[height + 2][width + 2];            // Create temp image for black border
    RGBTRIPLE new_image[height][width];                     // Create new image

    int Gx_Kernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}; // Define Gx kernel
    int Gy_Kernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}}; // Define Gy kernel



    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 || i == height + 1 || j == 0 || j == width + 1)
            {
                temp_image[i][j].rgbtBlue = 0;          // Add black border to temp image
                temp_image[i][j].rgbtGreen = 0;
                temp_image[i][j].rgbtRed = 0;
            }
            else
            {
                temp_image[i][j].rgbtBlue = image[i - 1][j - 1].rgbtBlue;   // Copy rest of image to temp image
                temp_image[i][j].rgbtGreen = image[i - 1][j - 1].rgbtGreen;
                temp_image[i][j].rgbtRed = image[i - 1][j - 1].rgbtRed;
            }
        }
    }

    for (int i = 1; i < height + 1; i++)            // Run through temp image
    {
        for (int j = 1; j < width + 1; j++)
        {
            int Gx_Blue = 0;
            int Gy_Blue = 0;
            int Gx_Green = 0;
            int Gy_Green = 0;
            int Gx_Red = 0;
            int Gy_Red = 0;

            for (int ki = 0; ki < 3; ki++)
            {
                for (int kj = 0; kj < 3; kj++)
                {
                    Gx_Blue += temp_image[i - 1 + ki][j - 1 + kj].rgbtBlue * Gx_Kernel[ki][kj]; 
                    Gx_Green += temp_image[i - 1 + ki][j - 1 + kj].rgbtGreen * Gx_Kernel[ki][kj];
                    Gx_Red += temp_image[i - 1 + ki][j - 1 + kj].rgbtRed * Gx_Kernel[ki][kj];

                    Gy_Blue += temp_image[i - 1 + ki][j - 1 + kj].rgbtBlue * Gy_Kernel[ki][kj];
                    Gy_Green += temp_image[i - 1 + ki][j - 1 + kj].rgbtGreen * Gy_Kernel[ki][kj];
                    Gy_Red += temp_image[i - 1 + ki][j - 1 + kj].rgbtRed * Gy_Kernel[ki][kj];

                }   // Sum up Gx and Gy values using kernel

            }

            int Gxy_Blue = round(sqrt((float)(pow(Gx_Blue, 2) + pow(Gy_Blue, 2))));
            int Gxy_Green = round(sqrt((float)(pow(Gx_Green, 2) + pow(Gy_Green, 2))));
            int Gxy_Red = round(sqrt((float)(pow(Gx_Red, 2) + pow(Gy_Red, 2))));

            if (Gxy_Blue > 255)         // Calculate Gxy values and cap at 255
            {
                Gxy_Blue = 255;
            }
            if (Gxy_Green > 255)
            {
                Gxy_Green = 255;
            }
            if (Gxy_Red > 255)
            {
                Gxy_Red = 255;
            }

            new_image[i - 1][j - 1].rgbtBlue = Gxy_Blue;  // Set values to new image
            new_image[i - 1][j - 1].rgbtGreen = Gxy_Green;
            new_image[i - 1][j - 1].rgbtRed = Gxy_Red;

        }
    }

    for (int i = 0; i < height; i++)            // Runs through each row of pixels
    {
        for (int j = 0; j < width; j++)             // Runs through each column of pixels
        {
            image[i][j].rgbtBlue = new_image[i][j].rgbtBlue;    // Copy new image to image
            image[i][j].rgbtGreen = new_image[i][j].rgbtGreen;
            image[i][j].rgbtRed = new_image[i][j].rgbtRed;
        }
    }

    return;
}
