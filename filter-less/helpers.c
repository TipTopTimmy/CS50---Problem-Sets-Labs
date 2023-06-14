#include "helpers.h"
#include "math.h"
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average = 0;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed = 0;
    float sepiaBlue = 0;
    float sepiaGreen = 0;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            sepiaRed = round(.393*image[i][j].rgbtRed + .769*image[i][j].rgbtGreen + .189*image[i][j].rgbtBlue);
            if(sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            sepiaGreen = round(.349*image[i][j].rgbtRed + .686*image[i][j].rgbtGreen + .168*image[i][j].rgbtBlue);
            if(sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            sepiaBlue = round(.272*image[i][j].rgbtRed + .534*image[i][j].rgbtGreen + .131*image[i][j].rgbtBlue);
            if(sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE swap[height][width];

        for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
        {
            swap[i][j] = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = swap[i][j];

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    float totalBlue = 0;
    float totalGreen = 0;
    float totalRed = 0;
    float counter = 0;
    RGBTRIPLE tempRGB[height][width];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            counter = 0;
            totalBlue = 0;
            totalGreen = 0;
            totalRed = 0;

            //Top Left Corner
            if(i == 0 && j == 0)
            {
                for(int ki = 1; ki < 3; ki++)
                {
                    for(int kj = 1; kj < 3; kj++)
                    {
                        int pi = i + ki - 1;
                        int pj = j + kj - 1;
                        totalBlue = totalBlue + image[pi][pj].rgbtBlue;
                        totalGreen = totalGreen + image[pi][pj].rgbtGreen;
                        totalRed = totalRed + image[pi][pj].rgbtRed;
                        counter++;
                    }
                }
                tempRGB[i][j].rgbtBlue = round(totalBlue/counter);
                tempRGB[i][j].rgbtGreen = round(totalGreen/counter);
                tempRGB[i][j].rgbtRed = round(totalRed/counter);
            }

            //Top Right Corner
            else if (i == 0 && j == width-1)
            {
                for(int ki = 1; ki < 3; ki++)
                {
                    for(int kj = 0; kj < 2; kj++)
                    {
                        int pi = i + ki - 1;
                        int pj = j + kj - 1;

                        totalBlue = totalBlue + image[pi][pj].rgbtBlue;
                        totalGreen = totalGreen + image[pi][pj].rgbtGreen;
                        totalRed = totalRed + image[pi][pj].rgbtRed;
                        counter++;
                    }
                }
                tempRGB[i][j].rgbtBlue = round(totalBlue/counter);
                tempRGB[i][j].rgbtGreen = round(totalGreen/counter);
                tempRGB[i][j].rgbtRed = round(totalRed/counter);
            }

            //Bottom Left Corner
            else if( i == height-1 && j == 0)
            {
                for(int ki = 0; ki < 2; ki++)
                {
                    for(int kj = 1; kj < 3; kj++)
                    {
                        int pi = i + ki - 1;
                        int pj = j + kj - 1;

                        totalBlue = totalBlue + image[pi][pj].rgbtBlue;
                        totalGreen = totalGreen + image[pi][pj].rgbtGreen;
                        totalRed = totalRed + image[pi][pj].rgbtRed;
                        counter++;
                    }
                }
                tempRGB[i][j].rgbtBlue = round(totalBlue/counter);
                tempRGB[i][j].rgbtGreen = round(totalGreen/counter);
                tempRGB[i][j].rgbtRed = round(totalRed/counter);
            }

            //Bottom Right Corner
            else if( i == height-1 && j == width - 1)
            {
                for(int ki = 0; ki < 2; ki++)
                {
                    for(int kj = 0; kj < 2; kj++)
                    {
                        int pi = i + ki - 1;
                        int pj = j + kj - 1;

                        totalBlue = totalBlue + image[pi][pj].rgbtBlue;
                        totalGreen = totalGreen + image[pi][pj].rgbtGreen;
                        totalRed = totalRed + image[pi][pj].rgbtRed;
                        counter++;
                    }
                }
                tempRGB[i][j].rgbtBlue = round(totalBlue/counter);
                tempRGB[i][j].rgbtGreen = round(totalGreen/counter);
                tempRGB[i][j].rgbtRed = round(totalRed/counter);
            }

            //top
            else if ( i == 0)
            {
                for(int ki = 1; ki < 3; ki++)
                {
                    for(int kj = 0; kj < 3; kj++)
                    {
                        int pi = i + ki - 1;
                        int pj = j + kj - 1;

                        totalBlue = totalBlue + image[pi][pj].rgbtBlue;
                        totalGreen = totalGreen + image[pi][pj].rgbtGreen;
                        totalRed = totalRed + image[pi][pj].rgbtRed;
                        counter++;
                    }
                }
                tempRGB[i][j].rgbtBlue = round(totalBlue/counter);
                tempRGB[i][j].rgbtGreen = round(totalGreen/counter);
                tempRGB[i][j].rgbtRed = round(totalRed/counter);
            }

            //bottom
            else if( i == height -1)
             {
                for(int ki = 0; ki < 2; ki++)
                {
                    for(int kj = 0; kj < 3; kj++)
                    {
                        int pi = i + ki - 1;
                        int pj = j + kj - 1;

                        totalBlue = totalBlue + image[pi][pj].rgbtBlue;
                        totalGreen = totalGreen + image[pi][pj].rgbtGreen;
                        totalRed = totalRed + image[pi][pj].rgbtRed;
                        counter++;
                    }
                }
                tempRGB[i][j].rgbtBlue = round(totalBlue/counter);
                tempRGB[i][j].rgbtGreen = round(totalGreen/counter);
                tempRGB[i][j].rgbtRed = round(totalRed/counter);
            }

            //left
            else if( j == 0)
            {
                for(int ki = 0; ki < 3; ki++)
                {
                    for(int kj = 1; kj < 3; kj++)
                    {
                        int pi = i + ki - 1;
                        int pj = j + kj - 1;
                        totalBlue = totalBlue + image[pi][pj].rgbtBlue;
                        totalGreen = totalGreen + image[pi][pj].rgbtGreen;
                        totalRed = totalRed + image[pi][pj].rgbtRed;
                        counter++;
                    }
                }
                tempRGB[i][j].rgbtBlue = round(totalBlue/counter);
                tempRGB[i][j].rgbtGreen = round(totalGreen/counter);
                tempRGB[i][j].rgbtRed = round(totalRed/counter);
            }
            //right
            else if( j == width-1)
             {
                for(int ki = 0; ki < 3; ki++)
                {
                    for(int kj = 0; kj < 2; kj++)
                    {
                        int pi = i + ki - 1;
                        int pj = j + kj - 1;
                        totalBlue = totalBlue + image[pi][pj].rgbtBlue;
                        totalGreen = totalGreen + image[pi][pj].rgbtGreen;
                        totalRed = totalRed + image[pi][pj].rgbtRed;
                        counter++;
                    }
                }
                tempRGB[i][j].rgbtBlue = round(totalBlue/counter);
                tempRGB[i][j].rgbtGreen = round(totalGreen/counter);
                tempRGB[i][j].rgbtRed = round(totalRed/counter);
            }

            //field
            else
            {
                for(int ki = 0; ki < 3; ki++)
                {
                    for(int kj = 0; kj < 3; kj++)
                    {
                        int pi = i + ki - 1;
                        int pj = j + kj - 1;

                        totalBlue = totalBlue + image[pi][pj].rgbtBlue;
                        totalGreen = totalGreen + image[pi][pj].rgbtGreen;
                        totalRed = totalRed + image[pi][pj].rgbtRed;
                        counter++;
                    }
                }
                tempRGB[i][j].rgbtBlue = round(totalBlue/counter);
                tempRGB[i][j].rgbtGreen = round(totalGreen/counter);
                tempRGB[i][j].rgbtRed = round(totalRed/counter);
            }
        }
    }
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tempRGB[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tempRGB[i][j].rgbtGreen;
            image[i][j].rgbtRed = tempRGB[i][j].rgbtRed;
        }
    }
    return;
}

