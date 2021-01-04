#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }
    FILE *card = fopen(argv[1], "r");
    unsigned char *buffer = malloc(512);
    if (buffer == NULL)
    {
        return 1;
    }
    char *filename = malloc(3 * sizeof(int));
    int photoCount = 0;

    while (fread(buffer, sizeof(unsigned char), 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (photoCount == 1)
            {
                sprintf(filename, "%03i.jpg", photoCount);
                FILE *imageFile = fopen(filename, "w");
                fwrite(buffer, 1, 512, imageFile);
                fclose(imageFile);
            }
            else
            {
                sprintf(filename, "%03i.jpg", photoCount);
                FILE *imageFile = fopen(filename, "w");
                fwrite(buffer, 1, 512, imageFile);
                fclose(imageFile);
            }
            photoCount++;
        }
        else if (photoCount != 0)
        {
            FILE *imageFile = fopen(filename, "a");
            fwrite(buffer, 1, 512, imageFile);
            fclose(imageFile);
        }

    }
    free(buffer);
    printf("contagem = %i\n", photoCount);
}
