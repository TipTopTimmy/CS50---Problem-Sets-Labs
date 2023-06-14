#include<stdio.h>
#include<cs50.h>

int main(void)
{
    int odd = 0;
    int even = 0;
    int firstDigit = 0;
    int secondDigit = 0;

//Take user input of CC number
    long NUM = get_long("Number: ");

//Determine the length and the first and second digits of the card number by dividing card number by 10 until 0 and tracking the number of iterations.
    long cardNumber = NUM;
    int i = 0;
    int oddSum = 0;
    int evenSum = 0;
    int finalSum = 0;
    int checkSum = 0;
    while (cardNumber > 0)
    {
        i++;
        
        int digit = cardNumber % 10;

        if(i % 2 == 1)
        {
            oddSum = oddSum + digit;
        }
        else if ( i % 2 == 0)
        {
            int modEven = digit * 2;     //modEven created so that the last even value will be stored for later use
            evenSum = modEven / 10 + evenSum;
            evenSum = modEven % 10 + evenSum;
        }
        cardNumber = cardNumber / 10;
        secondDigit = firstDigit;
        firstDigit = digit;
//This finalizes the checksum to determine if the number satifies Luhn's Algorithm
        finalSum = evenSum + oddSum;
        checkSum = finalSum % 10;
    }

//Once the checksum is determined, the first 2 numbers are used to determine credit card type.
    if (checkSum == 0 && firstDigit == 4 && (i == 13 || i == 16))
    {
        printf("VISA\n");
    }
    else if (checkSum == 0 && firstDigit == 3 && (secondDigit == 4 || secondDigit == 7))
    {
        printf("AMEX\n");
    }
    else if (checkSum == 0 && firstDigit == 5 && (secondDigit >= 1 && secondDigit <= 5))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");

    }
}

