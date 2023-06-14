#include <cs50.h>
#include <stdio.h>

int buildPyramid(int blocks, int counter);

int main(void)
{
    // TODO: Prompt user for height with input validation 1-8 blocks tall
    int height = 0;
    int counter = 1;
    do
    {
        height = get_int("How many blocks tall? ");
    }
    while( height <= 0 || height > 8);
    // TODO: Build pyramid
    buildPyramid(height, counter);
}

int buildPyramid(int blocks, int counter)
{
    int i = 0;
    //Check base condition for recursion

    if (counter > blocks)
    {
        return 0;
    }
    //Print the appropiate number of leading spaces
    for (i = 0; i < blocks - counter; i++)
    {
        printf(" ");
    }
    //Print the appropiate number of hashes for the first half of the pyramid
    for (int j = 0; j < counter; j++)
    {
        printf("#");
    }
    //Print the hole
    printf("  ");
    //Print the back helf of the pyramid
    for (int j = 0; j < counter; j++)
    {
        printf("#");
    }
    printf("\n");
    counter++;

    return buildPyramid(blocks, counter);
}