#include <stdlib.h>
#include <stdio.h>
#include "wavlib.h"

wav_type *cat_audio(wav_type *result, wav_type *input) {

    uint32_t i, size;

    size = result->SubChunk2Size + input->SubChunk2Size;
    result->SamplesArray = realloc(result->SamplesArray,size);
    if (!result->SamplesArray) {
        fprintf(stderr,"Não foi possível realocar na memória\n");
        exit(0);
    }
    for (i=0;i<(input->SubChunk2Size/2);i++) {
        result->SamplesArray[i + (result->SubChunk2Size/2)] = input->SamplesArray[i];
    }
    result->ChunkSize += input->ChunkSize;
    result->SubChunk2Size = size;
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
                result = cat_audio(result,input);
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