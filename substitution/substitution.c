/* this code should be reviewed and edited to create more functions that isolate actions as the code runs. */
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
//Make sure a key is input at command line.
    if (argc != 2)
    {
        printf("PLEASE PROVIDE A VALID CIPHER KEY AT THE COMMAND LINE\n");
        return 1;
    }
//Create a new string 'key' to work from and determine length.
    string key = argv[1];
    int keyLength = strlen(key);

//Validate the key
    //Must have 26 chars
    if (keyLength < 26)
    {
        printf("INVALID CIPHER KEY. CIPHER KEY MUST BE 26 CHARACTERS\n");
        return 1;
    }

    //must contain only letters
    for (int i = 0; i < keyLength; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            printf("INVALID CIPHER KEY. CIPHER KEY MUST CONTAIN ONLY CHARACTERS\n");
            return 1;
        }
    }

    //must not repeat a letter
    for (int i = 0; i < keyLength; i++)
    {
        for (int j = 0, m = strlen(key); j < m; j++)
        if ( (key[i] == key[j]) && (i != j) )
        {
            printf("INVALID CIPHER KEY. CIPHER KEY CHARACTERS CANNOT REPEAT\n");
            return 1;
        }
    }

    //must accept any combination of uppercase and lowercase letters -- no adjustment necessary 12/28/2020

//Get plaintext
    string plainText = get_string("plaintext: ");

//Encipher plaintext
    //Create an alphabet string
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    //Create a modified key that mirrors alpha -- copy key onto modkey, toupper 0-25, tolower 26-51
    string modKey = strcat(key, key);
    for (int i = 0; i < 52; i++)
    {
        if (i < 26)
        {
            modKey[i] = toupper(modKey[i]);
        }
        else
        {
            modKey[i] = tolower(modKey[i]);
        }
    }
    //printf("Modkey: %s\n", modKey);

    //Use modified key and Alphabet strings to encipher plain text
        //must preserve capitalization -- position within alpha string can determine capitalization
    int position[strlen(plainText)+1];
    for (int i = 0, n = strlen(plainText); i < n; i++)  //This provides the position of the number in alpha
    {
        for (int j = 0, m = strlen(alpha); j < m; j++)
        if (plainText[i] == alpha[j])
        {
            position[i] = j;
            //printf("Character Position: %i\n",position[i]);
            //printf("Character Integer : %i\n", alpha[j]);
        }
    }

    string cipher = plainText;
    for (int  i = 0, n = strlen(plainText); i < n; i++)
    {
        if (plainText[i] == ' ')
        {
            cipher[i] = ' ';
        }
        else if (((int)plainText[i] >= 32 && (int)plainText[i] <= 64)) //Comparisons are made against integer ascii values to ensure punctuation and special characters are preserved in the enciphered result.
        {
            cipher[i] = plainText[i];
        }
        else
        {
            cipher[i] = modKey[position[i]];
        }
    }

//Print ciphertext
    printf("ciphertext: %s\n", cipher);

    return 0;
}