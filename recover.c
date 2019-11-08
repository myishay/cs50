#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile \n");
        return 1;
    }

    //remember filenames
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    typedef uint8_t BYTE;
    BYTE buffer[512];
    int JPEG_found = 0;
    int JPEG_det = 0;
    FILE *img = NULL;

    while(fread(&buffer, 512, 1, inptr) != 0)
    {
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
            {
                if (JPEG_found == 1)
                {
                    fclose(img);
                }

                JPEG_found = 1;
                char filename[7];
                sprintf(filename, "%03i.jpg", JPEG_det);
                img = fopen(filename, "w");
                JPEG_det++;
            }

        if (JPEG_found == 1)
        {
            fwrite(buffer, 512, 1, img);
        }
    }

    fclose(img);

    fclose(inptr);

    printf("DONE! \n");

    return 0;
}
