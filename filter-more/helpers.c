#include "helpers.h"
#include "stdio.h"
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    typedef struct{

        int red[3][3];
        int green[3][3];
        int blue[3][3];
    }Product;

    typedef struct{
        int red;
        int blue;
        int green;
    }Sum;

    int sobelGx[3][3] = {{-1, 0, 1},{-2, 0, 2},{-1, 0, 1}};
    int sobelGy[3][3] = {{-1, -2, -1},{0, 0, 0},{1, 2, 1}};

    RGBTRIPLE temp[width+2][height=2];
    Product Gx[height][width];
    Product Gy[height][width];

    Sum sumGx;
    Sum sumGy;



    //Create a temp image with all black values
    for(int i = 0; i < 1; i++)
    {
        for(int j = 0; j < 1; j++)
        {
            temp[i][j].rgbtBlue = 0;
            temp[i][j].rgbtGreen = 0;
            temp[i][j].rgbtRed = 0;
        }
    }
    //copy image file to temp but leave 1 pixel black pad around the edge.
    for(int i = 1; i < height-2; i++)
    {
        for(int j = 1; j < width-2; j++)
        {
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    for(int i = 1; i < height-2; i++)
    {
        for(int j = 1; j < width-2; j++) //select target pixel
        {
             for(int ki = 0; ki < 3; ki++)
                {
                    for(int kj = 0; kj < 3; kj++)//iterates around the target
                    {
                        int pi = i + ki - 1;
                        int pj = j + kj - 1;

                        for(int n = 0; n < 3; n ++)
                        {
                            for( int m = 0; m < 3; m++) //interates through sobel arrays and assigns resulting product
                            {
                                Gx[pi][pj].blue[n][m] = temp[pi][pj].rgbtBlue * sobelGx[n][m];
                                Gx[pi][pj].green[n][m] = temp[pi][pj].rgbtGreen * sobelGx[n][m];
                                Gx[pi][pj].red[n][m] = temp[pi][pj].rgbtRed * sobelGx[n][m];

                                Gy[pi][pj].blue[n][m] = temp[pi][pj].rgbtBlue * sobelGy[n][m];
                                Gy[pi][pj].green[n][m] = temp[pi][pj].rgbtGreen * sobelGy[n][m];
                                Gy[pi][pj].red[n][m] = temp[pi][pj].rgbtRed * sobelGy[n][m];
                            }
                        }
                        //n,m complete. Gx Gy addition

                    }
                }
        }
    }
    //Write adjusted RGB values to image[][] for output.
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width ; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}

