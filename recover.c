#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "rb");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[512];
    FILE *img = NULL;
    int count = 0;
    char name[8];

    while (fread(buffer, 512, 1, card) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
            {
                fclose(img);
            }

            sprintf(name, "%03i.jpg", count);
            img = fopen(name, "wb");
            count++;
        }

        if (img != NULL)
        {
            fwrite(buffer, 512, 1, img);
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);

    return 0;
}
