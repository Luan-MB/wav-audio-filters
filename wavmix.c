#include <stdlib.h>
#include <stdio.h>
#include "wavlib.h"

wav_type *mix_audio(wav_type *result, wav_type *input) {

    uint32_t i, size;

    if (result->SubChunk2Size < input->SubChunk2Size) {
        result->SamplesArray = realloc(result->SamplesArray,input->SubChunk2Size);
        if (!result->SamplesArray) {
            fprintf(stderr,"Não foi possível realocar na memória\n");
            exit(0);
        }
        result->SubChunk2Size = input->SubChunk2Size;
    }
    size = input->SubChunk2Size;
    for (i=0;i<(size/2);i++) {
        if ((result->SamplesArray[i] + input->SamplesArray[i]) > INT16_MAX)
            result->SamplesArray[i] = INT16_MAX;
        else if ((result->SamplesArray[i] + input->SamplesArray[i]) < INT16_MIN)
            result->SamplesArray[i] = INT16_MIN;
        else
            result->SamplesArray[i] += input->SamplesArray[i];
    }
    return result;
}

int main (int argc, char **argv) {

    char *fout = NULL;
    wav_type *result, *input;
    int arg = 0;
    int i = 1;

    while (i < argc) {
        if ((argv[i][0] == '-') && (argv[i][1] == 'o')) {
            fout = argv[i+1];
            i++;
        } else {
            if (arg == 0) {
                result = load_wav(argv[i],1);
                if (!result)
                    return 0;
                arg++;
            } else {
                input = load_wav(argv[i],1);
                if (!input)
                    return 0;
                result = mix_audio(result,input);
                free_wav(input);
            }
        }
        i++;
    }
    if (!(write_wav(result,fout)))
        return 0;
    free_wav(result);
    return 1; 
}