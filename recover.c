/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

/*int main(int argc, char* argv[])
{
    // TODO
}
*/
#include <stdint.h>
#include <stdio.h>

typedef uint8_t  BYTE;

BYTE block[512];

int main ()
{
   FILE *inp;
   FILE *otp;
   //int c;
   //int n = 0;
   int i = 0;

   inp = fopen("card.raw","r");
   if(inp == NULL)
   {
      perror("Error in opening file");
      return(-1);
   }
   //find the first JPEG start & insert it into 'block'
   do
   {
       fread(&block, 512, 1, inp);
       if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && block[3] >= 0xe0 && block[3] <= 0xef)
       {
           printf("%x %x %x %x %x\n", block[0], block[1], block[2], block[3], block[4]);
           break;
       }
   }while (1);
}
