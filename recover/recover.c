#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include<string.h>

int main(int argc, char *argv[])
{
    const int BLOCK_SIZE = 512;
    typedef uint8_t BYTE;
    BYTE buffer[BLOCK_SIZE];
    int counter = 0;
    char *filename = "XXX.jpg";
    FILE *image = NULL;
    char *newJPEG = malloc(strlen(filename) + 1);
    if (newJPEG == NULL)
    {
        return 11;
    }

    if (argc != 2)
    {
        printf("Invalid Command. Try \" your_file.raw\" instead.\n");
        return 1;
    }
    FILE *card = fopen(argv[1], "r");

    while (fread(&buffer, BLOCK_SIZE, 1, card) == 1)
    {
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (counter == 0)
            {
                //write file
                sprintf(newJPEG, "%03i.jpg", counter);
                image = fopen(newJPEG, "w");
                fwrite(&buffer, BLOCK_SIZE, 1, image);
                counter++;
            }

            else
            {
                //close previous file and start a new one
                fclose(image);
                sprintf(newJPEG, "%03i.jpg", counter);
                image = fopen(newJPEG, "w"); 
                fwrite(&buffer, BLOCK_SIZE, 1, image);
                counter++;
            }
        }
        else if (counter != 0)
        {
            //continue writing another block to current file.
            fwrite(&buffer, BLOCK_SIZE, 1, image);
        }
    }
    fclose(image);
    fclose(card);
    free(newJPEG);
    return 0;
}

