#include <stdlib.h>
#include <unistd.h>
#include "wavlib.h"

void vol_change (wav_type *input, float level) {

    uint32_t i;

    for (i=0;i<(input->SubChunk2Size/2);i++) {
        if ((input->SamplesArray[i] * level) > INT16_MAX)
            input->SamplesArray[i] = INT16_MAX;
        else if ((input->SamplesArray[i] * level) < INT16_MIN)
            input->SamplesArray[i] = INT16_MIN;
        else 
            input->SamplesArray[i] = input->SamplesArray[i] * level;
    }
}

int main (int argc, char **argv) {

    wav_type *input;
    char opt;
    char *fin = NULL;
    char *fout = NULL;
    float level= 1;

    while ((opt = getopt (argc, argv, "i:o:l:")) != -1) {
        switch(opt) {
            case 'i':
                fin = optarg;
                break;
            case 'o':
                fout = optarg;
                break;
            case 'l':
                level = atof(optarg);
                break;
        }
    }

    input = load_wav(fin,1);
    if (!input)
        return 0;
    vol_change(input,level);
    if (!(write_wav(input,fout)))
        return 0;
    free_wav(input);
    return 1;
}
