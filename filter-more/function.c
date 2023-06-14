void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE totalRGB;
    //RGBTRIPLE avgRGB;
    RGBTRIPLE tempRGB[height][width];



    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            totalRGB = image[i][j];
            //Corner 1
            if((i == 0 && j == 0)
            {
                for(int ki = 1; ki < 3; ki++)
                {
                    for(int kj = 1; kj < 2; kj++)
                    {
                        int pi = i + ki - 1;
                        int pj = j + kj - 1;
                        totalRGB = totalRGB + image[pi][pj];
                    }
                    avgRGB = totalRGB/counter;
                }
            }
            //Corner 2
            else if (i == 0 && j == width-1)
            {
                for(int ki = 1; ki < 3; ki++)
                {
                    for(int kj = width-2; kj < width; kj++)
                    {
                        int pi = i + ki - 1;
                        int pj = j + kj - 1;
                        totalRGB = totalRGB + image[pi][pj];
                    }
                    temp[i][j] = totalRGB/counter;

                }
            }
            //Corner 3
            else if( i = height-1 && j == 0)
            {
                for(int ki = height-2 ; ki < height; ki++)
                {
                    for(int kj = 1; kj < 2; kj++)
                    {
                        int pi = i + ki - 1;
                        int pj = j + kj - 1;
                        totalRGB = totalRGB + image[pi][pj];
                    }
                    temp[i][j] = totalRGB/counter;
                }
            }
            //Corner 4
            else if( i == height-1 && j == width - 1)
            {
                for(int ki = height-2; ki < height; ki++)
                {
                    for(int kj = width-2; kj < width; kj++)
                    {
                        int pi = i + ki - 1;
                        int pj = j + kj - 1;
                        totalRGB = totalRGB + image[pi][pj];
                    }
                    temp[i][j] = totalRGB/counter;
                }
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
                        totalRGB = totalRGB + image[pi][pj];
                    }
                    temp[i][j] = totalRGB/counter;
                }
            }
            //bottom
            else if( i == height -1)
            {
                for(int ki = height-2 ; ki < height; ki++)
                {
                    for(int kj = 0; kj < 3; kj++)
                    {
                        int pi = i + ki - 1;
                        int pj = j + kj - 1;
                        totalRGB = totalRGB + image[pi][pj];
                    }
                    temp[i][j] = totalRGB/counter;
                }
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
                        totalRGB = totalRGB + image[pi][pj];
                    }
                    temp[i][j] = totalRGB/counter;
                }
            }
            //right
            else if( j == width-1)
            {
                for(int ki = 0; ki < 3; ki++)
                {
                    for(int kj = width-2; kj < width; kj++)
                    {
                        int pi = i + ki - 1;
                        int pj = j + kj - 1;
                        totalRGB = totalRGB + image[pi][pj];
                    }
                    temp[i][j] = totalRGB/counter;
                }
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
                        totalRGB = totalRGB + image[pi][pj];
                    }
                    temp[i][j] = totalRGB/counter;
                }
            }
        }
    }
    for(int i = 0; i < height; i++)
    {
        for(int i = 0; i < height; i++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}





           //Corner 1
            if(i == 0 && j == 0)
            {
                counter = 1;
                fprintf(blur_log, "Target: Image[%i][%i]\n", i, j);
                fprintf(blur_log, "Initial Total Blue: %i\n",totalRGB.rgbtBlue);
                 printf("totalBlue: %i\n", totalBlue);
                printf("Target: Image[%i][%i]\n", i, j);
                printf("Initial Total Blue: %i\n",totalBlue);
                for(int ki = 1; ki < 3; ki++)
                {
                    for(int kj = 1; kj < 3; kj++)
                    {
                        int pi = i + ki - 1;
                        int pj = j + kj - 1;
                        fprintf(blur_log, "Neighbor Blue[%i][%i]: %i\n", pi, pj, image[pi][pj].rgbtBlue);
                        printf("totalBlue pre calc: %i\n", totalBlue);
                        printf("totalBlue.rgbt pre calc: %i\n", image[pi][pj].rgbtBlue);
                       // totalRGB.rgbtBlue = totalRGB.rgbtBlue + image[pi][pj].rgbtBlue;
                        totalBlue = totalBlue + image[pi][pj].rgbtBlue;
                        totalGreen = totalGreen + image[pi][pj].rgbtGreen;
                        totalRed = totalRed + image[pi][pj].rgbtRed;
                        printf("totalBlue post calc: %i\n", totalBlue);
                        printf("totalBlue.rgbt post calc: %i\n", image[pi][pj].rgbtBlue);
                        //fprintf(blur_log, "totalRGB.rgbtBlue: %i\n", totalRGB.rgbtBlue);
                        //totalRGB.rgbtGreen = totalRGB.rgbtGreen + image[pi][pj].rgbtGreen;
                        //totalRGB.rgbtRed = totalRGB.rgbtRed + image[pi][pj].rgbtRed;
                        //fprintf(blur_log, "Type: Corner 1\ncoordinate = %i, %i,\n offset = %i, %i\n", i, j, pi, pj);
                        counter++;
                    }
                }
                fprintf(blur_log, "totalRGB.rgbtBlue: %i\n Counter: %f\n", totalRGB.rgbtBlue,counter);
                printf("average blue: %f\n", totalBlue/counter);
                tempRGB[i][j].rgbtBlue = round(totalBlue/counter);
                fprintf(blur_log, "tempRGB[%i][%i].rgbtBlue: %i\n", i, j, tempRGB[i][j].rgbtBlue);
                tempRGB[i][j].rgbtGreen = round(totalGreen/counter);
                tempRGB[i][j].rgbtRed = round(totalRed/counter);
            }

            /*void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int averageBlue = 0;
    int averageGreen = 0;
    int averageRed = 0;

    int totalBlue = 0;
    int totalGreen = 0;
    int totalRed = 0;

    int counter = 1;

    int x[3][3] = {{-1, -1, -1}, {0, 0, 0}, {1, 1, 1}}; //These matrices represent the offsets from target array element of each pixel.
    int y[3][3] = {{-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1}};

    RGBTRIPLE tempImage[height][width];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++) //select target element
        {
            totalBlue = image[i][j].rgbtBlue;
            totalGreen =image[i][j].rgbtGreen;
            totalRed = image[i][j].rgbtRed;

            for(int k = 0; k < 3; k ++ ) //k&n interate through elements surround the target element
            {
                for(int n = 0; n < 3; n++)
                {
                    if (&image[i+x[k][n]][j+y[k][n]] >= &image[0][0] && &image[i+x[k][n]][j+y[k][n]] <= &image[height - 1][width -1])
                    {
                        //Total RGB Values, Update Counter, Average RGB Values. Assign Average Value to image[i][j]
                        counter++;
                        totalBlue = totalBlue + image[i+x[k][n]][j+y[k][n]].rgbtBlue;
                        totalGreen = totalGreen + image[i+x[k][n]][j+y[k][n]].rgbtGreen;
                        totalRed = totalRed + image[i+x[k][n]][j+y[k][n]].rgbtRed;
                    }
                }
            }
                //printf("Counter: %i\n", counter);
                tempImage[i][j].rgbtBlue = totalBlue/counter;
                tempImage[i][j].rgbtGreen = totalGreen/counter;
                tempImage[i][j].rgbtRed = totalRed/counter;
                counter = 1;
        }
    }
//Write adjusted RGB values to image[][] for output.
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width ; j++)
        {
            image[i][j].rgbtBlue = tempImage[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tempImage[i][j].rgbtGreen;
            image[i][j].rgbtRed = tempImage[i][j].rgbtRed;
        }
    }
    return;
}*/
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
            //Corner 1
            if(i == 0 && j == 0)
            {
                counter = 0;
                totalBlue = 0;
                totalGreen = 0;
                totalRed = 0;
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
            //Corner 2
            else if (i == 0 && j == width-1)
            {
                counter = 0;
                totalBlue = 0;
                totalGreen = 0;
                totalRed = 0;
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

            //Corner 3
            else if( i == height-1 && j == 0)
            {
                counter = 0;
                totalBlue = 0;
                totalGreen = 0;
                totalRed = 0;
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

            //Corner 4
            else if( i == height-1 && j == width - 1)
            {
                counter = 0;
                totalBlue = 0;
                totalGreen = 0;
                totalRed = 0;
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
                counter = 0;
                totalBlue = 0;
                totalGreen = 0;
                totalRed = 0;
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
                counter = 0;
                totalBlue = 0;
                totalGreen = 0;
                totalRed = 0;
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
                counter = 0;
                totalBlue = 0;
                totalGreen = 0;
                totalRed = 0;
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
                counter = 0;
                totalBlue = 0;
                totalGreen = 0;
                totalRed = 0;
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
                counter = 0;
                totalBlue = 0;
                totalGreen = 0;
                totalRed = 0;
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

void edges(int height, int width, RGBTRIPLE image[height][width])

//Pad the image with black

if (height == 1 && width == 1)
    {//Do Stuff
    //multiply
    //add
    //sqrt(Gx^2+Gy^2)
    //assign temp[][] value to image[][]
        return;
    }
else
{
    //do stuff starting at height-1, width-1
    //multiply
    //add
    //sqrt(Gx^2+Gy^2)
    //assign temp[][] value to image[][]
    return edges(height - 1, width -1, image[height][width])
}