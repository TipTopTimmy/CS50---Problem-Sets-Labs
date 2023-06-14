#include <cs50.h>
#include <stdio.h>
void buildPyramid(int n);

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
    buildPyramid(height);
}

void buildPyramid(int n)
{

    //Check base condition for recursion

    if (n <= 0)
    {
        return ;
    }

    buildPyramid(n-1);

    //Print the appropiate number of leading spaces
    for (int i = n; i > 0; i--)
    {
        printf(" ");
    }
    //Print the appropiate number of hashes for the first half of the pyramid
    for (int j = 0; j < n; j++)
    {
        printf("#");
    }
    //Print the hole
    printf("  ");
    //Print the back half of the pyramid
    for (int j = 0; j < n; j++)
    {
        printf("#");
    }
    printf("\n");


}