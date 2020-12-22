#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "wavlib.h"

int16_t peak_sample (wav_type *input) {

    uint32_t t;
    int16_t peak = input->SamplesArray[0];

    for (t=1;t<(input->SubChunk2Size/2);t++) {
        if (abs(peak) <  abs(input->SamplesArray[t]))
            peak = (input->SamplesArray[t]);
    }
    return peak;
}

void normalize_audio (wav_type *input) {

    uint32_t t;
    int16_t peak;
    float adj_factor;

    
    if ((peak = peak_sample(input)) > 0)
        adj_factor = INT16_MAX / (float)peak;
    else
        adj_factor = INT16_MIN / (float)peak;
    for (t=0;t<(input->SubChunk2Size/2);t++) {
        input->SamplesArray[t] = input->SamplesArray[t] * adj_factor;
    }
    fprintf(stderr,"Fator de Normalização: %.3f\n",adj_factor);
}
    
int main (int argc, char **argv) {

    wav_type *input;
    char opt;
    char *fin = NULL;
    char *fout = NULL;

    while ((opt = getopt (argc, argv, "i:o:")) != -1) {
        switch(opt) {
            case 'i':
                fin = optarg;
                break;
            case 'o':
                fout = optarg;
                break;
        }
    }
    
    input = load_wav(fin,1);
    if (!input)
        return 0;
    normalize_audio(input);
    if (!(write_wav(input,fout)))
        return 0;
    free_wav(input);
    return 1;
}