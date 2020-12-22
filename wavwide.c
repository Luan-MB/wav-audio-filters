#include <stdlib.h>
#include "wavlib.h"
#include <unistd.h>

void wide_sample (wav_type *input, float fator) {

    uint32_t i;
    int16_t diff;

    for (i=0;i<(input->SubChunk2Size/2);i=i+2) {
            diff = input->SamplesArray[i+1] - input->SamplesArray[i];
            if ((input->SamplesArray[i] - (fator * diff)) < INT16_MIN)
                input->SamplesArray[i] = INT16_MIN;
            else if ((input->SamplesArray[i] - (fator * diff)) > INT16_MAX)
                input->SamplesArray[i] = INT16_MAX;
            else
                input->SamplesArray[i] = input->SamplesArray[i] - (fator * diff);
            
            if ((input->SamplesArray[i+1] + (fator * diff)) > INT16_MAX)
                input->SamplesArray[i+1] = INT16_MAX;
            else if ((input->SamplesArray[i+1] + (fator * diff)) < INT16_MIN)
                input->SamplesArray[i+1] = INT16_MIN;
            else
               input->SamplesArray[i+1] = input->SamplesArray[i+1] + (fator * diff); 
    }
}

int main (int argc, char **argv) {

    wav_type *input;
    char opt;
    char *fin = NULL;
    char *fout = NULL;
    float level = 1;

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
    wide_sample(input,level);
    if (!(write_wav(input,fout)))
        return 0;
    free_wav(input);
    return 1;
}