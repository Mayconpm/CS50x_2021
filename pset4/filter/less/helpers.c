#include <math.h>
#include "helpers.h"

int cap255(int color);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int originalRed, originalGreen, originalBlue;
    float averageColors;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            averageColors = round((originalRed +
                                   originalGreen +
                                   originalBlue) /
                                  3.0);

            image[i][j].rgbtRed = averageColors;
            image[i][j].rgbtGreen = averageColors;
            image[i][j].rgbtBlue = averageColors;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int originalRed, originalGreen, originalBlue;
    int sephiaRed, sephiaGreen, sephiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            sephiaRed = round(.393 * originalRed +
                              .769 * originalGreen +
                              .189 * originalBlue);

            sephiaGreen = round(.349 * originalRed +
                                .686 * originalGreen +
                                .168 * originalBlue);

            sephiaBlue = round(.272 * originalRed +
                               .534 * originalGreen +
                               .131 * originalBlue);

            sephiaRed = cap255(sephiaRed);
            sephiaGreen = cap255(sephiaGreen);
            sephiaBlue = cap255(sephiaBlue);

            image[i][j].rgbtRed = sephiaRed;
            image[i][j].rgbtGreen = sephiaGreen;
            image[i][j].rgbtBlue = sephiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_row[width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_row[j] = image[i][j];
        }
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp_row[width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = temp_row[width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = temp_row[width - 1 - j].rgbtBlue;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_image[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            temp_image[h][w] = image[h][w];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            float sumRed = 0;
            float sumGreen = 0;
            float sumBlue = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    // Check if pixel is outside columns
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    // Otherwise add to sums
                    sumRed += temp_image[i + k][j + l].rgbtRed;
                    sumGreen += temp_image[i + k][j + l].rgbtGreen;
                    sumBlue += temp_image[i + k][j + l].rgbtBlue;
                    count++;
                }
            }

            image[i][j].rgbtRed = (int)round(sumRed / count);
            image[i][j].rgbtGreen = (int)round(sumGreen / count);
            image[i][j].rgbtBlue = (int)round(sumBlue / count);
        }
    }
}

int cap255(int color)
{
    if (color > 255)
    {
        return 255;
    }
    else
    {
        return color;
    }
}
