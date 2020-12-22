#include <unistd.h>
#include "wavlib.h"

void reverse_sound (wav_type *input){

    uint32_t i;
    int16_t aux;

    for (i=0;i<(input->SubChunk2Size/4);i=i+2) {
        aux = input->SamplesArray[i];
        input->SamplesArray[i] = input->SamplesArray[(input->SubChunk2Size/2)-(i+2)];
        input->SamplesArray[(input->SubChunk2Size/2)-(i+2)] = aux;

        aux = input->SamplesArray[i+1];
        input->SamplesArray[i+1] = input->SamplesArray[(input->SubChunk2Size/2) - (i+1)];
        input->SamplesArray[(input->SubChunk2Size/2) - (i+1)] = aux;
    }
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
    reverse_sound(input);
    if (!(write_wav(input,fout)))
        return 0;
    free_wav(input);
    return 1;
}