#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    FILE *in = fopen(argv[1], "rb");
    if (in == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *out = fopen(argv[2], "wb");
    if (out == NULL)
    {
        printf("Could not open file.\n");
        fclose(in);
        return 1;
    }

    float factor = atof(argv[3]);

    uint8_t header[44];
    fread(header, 44, 1, in);
    fwrite(header, 44, 1, out);

    int16_t sample;
    while (fread(&sample, sizeof(int16_t), 1, in))
    {
        sample *= factor;
        fwrite(&sample, sizeof(int16_t), 1, out);
    }

    fclose(in);
    fclose(out);
    return 0;
}
