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
                                   originalBlue) / 3.0);

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

    float averageRed, averageGreen, averageBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                averageRed = (temp_image[i][j].rgbtRed +
                              temp_image[i][j + 1].rgbtRed +
                              temp_image[i + 1][j + 1].rgbtRed +
                              temp_image[i + 1][j].rgbtRed) / 4.0;

                averageGreen = (temp_image[i][j].rgbtGreen +
                                temp_image[i][j + 1].rgbtGreen +
                                temp_image[i + 1][j + 1].rgbtGreen +
                                temp_image[i + 1][j].rgbtGreen) / 4.0;

                averageBlue = (temp_image[i][j].rgbtBlue +
                               temp_image[i][j + 1].rgbtBlue +
                               temp_image[i + 1][j + 1].rgbtBlue +
                               temp_image[i + 1][j].rgbtBlue) / 4.0;
            }
            else if (i == height - 1 && j == 0)
            {
                averageRed = (temp_image[i][j].rgbtRed +
                              temp_image[i - 1][j].rgbtRed +
                              temp_image[i - 1][j + 1].rgbtRed +
                              temp_image[i][j + 1].rgbtRed) / 4.0;

                averageGreen = (temp_image[i][j].rgbtGreen +
                                temp_image[i - 1][j].rgbtGreen +
                                temp_image[i - 1][j + 1].rgbtGreen +
                                temp_image[i][j + 1].rgbtGreen) / 4.0;

                averageBlue = (temp_image[i][j].rgbtBlue +
                               temp_image[i - 1][j].rgbtBlue +
                               temp_image[i - 1][j + 1].rgbtBlue +
                               temp_image[i][j + 1].rgbtBlue) / 4.0;

            }
            else if (i == 0 && j == width - 1)
            {
                averageRed = (temp_image[i][j].rgbtRed +
                              temp_image[i][j - 1].rgbtRed +
                              temp_image[i + 1][j - 1].rgbtRed +
                              temp_image[i + 1][j].rgbtRed) / 4.0;

                averageGreen = (temp_image[i][j].rgbtGreen +
                                temp_image[i][j - 1].rgbtGreen +
                                temp_image[i + 1][j - 1].rgbtGreen +
                                temp_image[i + 1][j].rgbtGreen) / 4.0;

                averageBlue = (temp_image[i][j].rgbtBlue +
                               temp_image[i][j - 1].rgbtBlue +
                               temp_image[i + 1][j - 1].rgbtBlue +
                               temp_image[i + 1][j].rgbtBlue) / 4.0;
            }
            else if (i == height - 1 && j == width - 1)
            {
                averageRed = (temp_image[i][j].rgbtRed +
                              temp_image[i - 1][j].rgbtRed +
                              temp_image[i - 1][j - 1].rgbtRed +
                              temp_image[i][j - 1].rgbtRed) / 4.0;

                averageGreen = (temp_image[i][j].rgbtGreen +
                                temp_image[i - 1][j].rgbtGreen +
                                temp_image[i - 1][j - 1].rgbtGreen +
                                temp_image[i][j - 1].rgbtGreen) / 4.0;

                averageBlue = (temp_image[i][j].rgbtBlue +
                               temp_image[i - 1][j].rgbtBlue +
                               temp_image[i - 1][j - 1].rgbtBlue +
                               temp_image[i][j - 1].rgbtBlue) / 4.0;
            }
            else if (j == width - 1)
            {
                averageRed = (temp_image[i][j].rgbtRed +
                              temp_image[i + 1][j].rgbtRed +
                              temp_image[i + 1][j - 1].rgbtRed +
                              temp_image[i][j - 1].rgbtRed +
                              temp_image[i - 1][j - 1].rgbtRed +
                              temp_image[i - 1][j].rgbtRed) / 6.0;

                averageGreen = (temp_image[i][j].rgbtGreen +
                                temp_image[i + 1][j].rgbtGreen +
                                temp_image[i + 1][j - 1].rgbtGreen +
                                temp_image[i][j - 1].rgbtGreen +
                                temp_image[i - 1][j - 1].rgbtGreen +
                                temp_image[i - 1][j].rgbtGreen) / 6.0;

                averageBlue = (temp_image[i][j].rgbtBlue +
                               temp_image[i + 1][j].rgbtBlue +
                               temp_image[i + 1][j - 1].rgbtBlue +
                               temp_image[i][j - 1].rgbtBlue +
                               temp_image[i - 1][j - 1].rgbtBlue +
                               temp_image[i - 1][j].rgbtBlue) / 6.0;
            }
            else if (j == 0)
            {
                averageRed = (temp_image[i][j].rgbtRed +
                              temp_image[i - 1][j].rgbtRed +
                              temp_image[i - 1][j + 1].rgbtRed +
                              temp_image[i][j + 1].rgbtRed +
                              temp_image[i + 1][j + 1].rgbtRed +
                              temp_image[i + 1][j].rgbtRed) / 6.0;

                averageGreen = (temp_image[i][j].rgbtGreen +
                                temp_image[i - 1][j].rgbtGreen +
                                temp_image[i - 1][j + 1].rgbtGreen +
                                temp_image[i][j + 1].rgbtGreen +
                                temp_image[i + 1][j + 1].rgbtGreen +
                                temp_image[i + 1][j].rgbtGreen) / 6.0;

                averageBlue = (temp_image[i][j].rgbtBlue +
                               temp_image[i - 1][j].rgbtBlue +
                               temp_image[i - 1][j + 1].rgbtBlue +
                               temp_image[i][j + 1].rgbtBlue +
                               temp_image[i + 1][j + 1].rgbtBlue +
                               temp_image[i + 1][j].rgbtBlue) / 6.0;
            }
            else if (i == height - 1)
            {
                averageRed = (temp_image[i][j].rgbtRed +
                              temp_image[i][j - 1].rgbtRed +
                              temp_image[i - 1][j - 1].rgbtRed +
                              temp_image[i - 1][j].rgbtRed +
                              temp_image[i - 1][j + 1].rgbtRed +
                              temp_image[i][j + 1].rgbtRed) / 6.0;

                averageGreen = (temp_image[i][j].rgbtGreen +
                                temp_image[i][j - 1].rgbtGreen +
                                temp_image[i - 1][j - 1].rgbtGreen +
                                temp_image[i - 1][j].rgbtGreen +
                                temp_image[i - 1][j + 1].rgbtGreen +
                                temp_image[i][j + 1].rgbtGreen) / 6.0;

                averageBlue = (temp_image[i][j].rgbtBlue +
                               temp_image[i][j - 1].rgbtBlue +
                               temp_image[i - 1][j - 1].rgbtBlue +
                               temp_image[i - 1][j].rgbtBlue +
                               temp_image[i - 1][j + 1].rgbtBlue +
                               temp_image[i][j + 1].rgbtBlue) / 6.0;
            }
            else if (i == 0)
            {
                averageRed = (temp_image[i][j].rgbtRed +
                              temp_image[i][j + 1].rgbtRed +
                              temp_image[i + 1][j + 1].rgbtRed +
                              temp_image[i + 1][j].rgbtRed +
                              temp_image[i + 1][j - 1].rgbtRed +
                              temp_image[i][j - 1].rgbtRed) / 6.0;

                averageGreen = (temp_image[i][j].rgbtGreen +
                                temp_image[i][j + 1].rgbtGreen +
                                temp_image[i + 1][j + 1].rgbtGreen +
                                temp_image[i + 1][j].rgbtGreen +
                                temp_image[i + 1][j - 1].rgbtGreen +
                                temp_image[i][j - 1].rgbtGreen) / 6.0;

                averageBlue = (temp_image[i][j].rgbtBlue +
                               temp_image[i][j + 1].rgbtBlue +
                               temp_image[i + 1][j + 1].rgbtBlue +
                               temp_image[i + 1][j].rgbtBlue +
                               temp_image[i + 1][j - 1].rgbtBlue +
                               temp_image[i][j - 1].rgbtBlue) / 6.0;
            }
            else
            {
                averageRed = (temp_image[i - 1][j - 1].rgbtRed +
                              temp_image[i - 1][j].rgbtRed +
                              temp_image[i - 1][j + 1].rgbtRed +
                              temp_image[i][j - 1].rgbtRed +
                              temp_image[i][j].rgbtRed +
                              temp_image[i][j + 1].rgbtRed +
                              temp_image[i + 1][j - 1].rgbtRed +
                              temp_image[i + 1][j].rgbtRed +
                              temp_image[i + 1][j + 1].rgbtRed) / 9.0;

                averageGreen = (temp_image[i - 1][j - 1].rgbtGreen +
                                temp_image[i - 1][j].rgbtGreen +
                                temp_image[i - 1][j + 1].rgbtGreen +
                                temp_image[i][j - 1].rgbtGreen +
                                temp_image[i][j].rgbtGreen +
                                temp_image[i][j + 1].rgbtGreen +
                                temp_image[i + 1][j - 1].rgbtGreen +
                                temp_image[i + 1][j].rgbtGreen +
                                temp_image[i + 1][j + 1].rgbtGreen) / 9.0;

                averageBlue = (temp_image[i - 1][j - 1].rgbtBlue +
                               temp_image[i - 1][j].rgbtBlue +
                               temp_image[i - 1][j + 1].rgbtBlue +
                               temp_image[i][j - 1].rgbtBlue +
                               temp_image[i][j].rgbtBlue +
                               temp_image[i][j + 1].rgbtBlue +
                               temp_image[i + 1][j - 1].rgbtBlue +
                               temp_image[i + 1][j].rgbtBlue +
                               temp_image[i + 1][j + 1].rgbtBlue) / 9.0;
            }

            image[i][j].rgbtRed = (int)round(averageRed);
            image[i][j].rgbtGreen = (int)round(averageGreen);
            image[i][j].rgbtBlue = (int)round(averageBlue);
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
