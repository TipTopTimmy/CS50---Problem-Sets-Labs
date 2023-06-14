#include <cs50.h>
#include <stdio.h>

int calcYears(int startPop, int endPop);

int main(void)
{
    // TODO: Prompt for start size
    int startSize = 0;
    while (startSize < 9 ){
        startSize = get_int("Starting Population: ");
    }

    // TODO: Prompt for end size
    int endSize = 0;
    while ( endSize < startSize){
        endSize = get_int("\nEnding Population: ");
    }
    // TODO: Calculate number of years until we reach threshold
    int numYears = calcYears(startSize, endSize);
    // TODO: Print number of years
    printf("\nYears: %i\n", numYears);
}

int calcYears(int startPop, int endPop)
{
    int years = 0;
    int newPop = startPop;
    if (startPop < endPop){
        do{
            newPop = newPop + newPop/3 - newPop/4;


            years++;
        }while( newPop < endPop);
    }
    return years;
}