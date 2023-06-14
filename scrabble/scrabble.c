#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if( score1 > score2)
    {
        printf("Player 1 Wins!");
    }
    else if (score1 < score2)
    {
        printf("Player 2 Wins!");
    }
    else
        {
            printf("Tie!");
        }


}

int compute_score(string word)
{
    int score = 0;  //keeps the score to be returned
    int wordUp[strlen(word)]; //converts all chars in the word string to their uppercase values
    int diff[strlen(word)]; //stores the value of the wordUp value - 65 to be correlated against POINTS[]
    // TODO: Compute and return score for string

    for( int i=0; i < strlen(word); i++)
    {
        if(ispunct(word[i]))    //Determines if char is punctuation and sets value to be 0 thus making its diff negative in the future.
        {
            word[i] = 0;
        }

        wordUp[i] = toupper(word[i]);   //convert chars to uppercase

        diff[i] = wordUp[i]-65;     //ASCII value of uppercase word - 65 correlates to associated points value in POINTS[]
        if(diff[i]>=0)              //Reject values less than zero because they are punctuation and tally score
        {
            score = score + POINTS[diff[i]];
        }

    }
    return score;
}
