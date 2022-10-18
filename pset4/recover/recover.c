#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)                      // Check for correct no. of arguments
    {
        printf("Usage: ./recover 'filename'\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");      // Opens the file specified in function argument

    if (f == NULL)                      // Check that file can be opened
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }


    unsigned char buffer[512];          // Define temporary 512 byte buffer for reading each block
    int i = 0;
    int j = 0;
    char filename[8];
    FILE *img;

    while (fread(buffer, 512, 1, f) == 1)       // Read 512 byte block from jpeg file
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)  // Check for start of JPEG file
        {
            if (i > 0)
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", i);   // Making a new JPEG
            img = fopen(filename, "w");
            fwrite(buffer, 512, 1, img);    // Write to current JPEG file
            i++;
        }
        else if (i > 0)
        {
            fwrite(buffer, 512, 1, img);
        }

        j++;
    }


}
