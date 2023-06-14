//declare librarys
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

//start of main
int main(void)
{
//Prompt user for string
    string text = get_string("Text: ");

//Count number of letters
    float letters = 0;
    float words = 1;
    float sentences = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        //Count number of letters by checking for their ascii value equivalent
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            letters = letters + 1;
        }

        //Count Number of words by counting spaces
        if (text[i] == 32)
        {
            words = words + 1;
        }

        //Count number of sentences by counting '.', '!', '?'
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            sentences = sentences + 1;
        }
    }


//Use Coleman-Liau formula rounded to nearest integer to determine grade level.
//Determine average number of letters per 100 words, L.
    float L = letters / words * 100;
//Determine the average number of sentences per 100 words, S.
    float S = sentences / words * 100;

//The final determination is as follows:
    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (index > 16)
    {
        printf("Grade 16+\n");
    }

    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int)round(index));
    }

    return 0;
}
