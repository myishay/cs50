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
           printf("%x %x %x\n", block[0], block[1], block[2]);
           break;
       }
   }while (1);
   //
   char s[10]; //  it was [7]. I need to check if thast matters
   //for (int i = 0; i < 50; i++)
   do
   {
       sprintf(s, "%03i.jpg", i);
       //printf("%s\n", s);
       otp = fopen(s, "w");
       fwrite(&block, 512, 1, otp);
       i++;
       do
       {
           if (fread(&block, 512, 1, inp) != 1)
           {
               fclose(inp);
               fclose(otp);
               return 0;
           }
           if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && block[3] >= 0xe0 && block[3] <= 0xef)
           {
               fclose(otp);
               break;
           }
           fwrite(&block, 512, 1, otp);
       } while (1);

       //EEEEEOOOOOOOFFFFFF
   } while(1);










  /* fseek(fp, 1024, SEEK_CUR);

for (int i = 0; i < 50; i++)
   {



       fread(&block, 512, 1, fp);
       fwrite(&block, 512, 1, opt);
       do
       {
           fread(&block, 512, 1, fp);
           if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && block[3] >= 0xe0 && block[3] <= 0xef)
           {
               fclose(fp);
               fclose(opt);
               break;
           }
           fwrite(&block, 512, 1, opt);

       }while(1);
   }


   if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && block[3] >= 0xe0 && block[3] <= 0xef)
   {
       printf("found a new JPEG file\n");
       //fseek(fp, -512, SEEK_CUR);


   }
   */

}
