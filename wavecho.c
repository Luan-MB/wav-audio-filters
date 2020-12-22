#include <stdlib.h>
#include "wavlib.h"
#include <unistd.h>

void create_echo (wav_type *input, int delay, float level) {

    uint32_t t, gap;
    
    gap = (input->SampleRate * delay)/1000;
    
    for (t=gap;t<(input->SubChunk2Size/2);t++) {
        if ((input->SamplesArray[t] + (level * input->SamplesArray[t - gap])) > INT16_MAX)
            input->SamplesArray[t] = INT16_MAX;
        else if ((input->SamplesArray[t] + (level * input->SamplesArray[t - gap])) < INT16_MIN) 
            input->SamplesArray[t] = INT16_MIN;
        else 
            input->SamplesArray[t] = input->SamplesArray[t] + (level * input->SamplesArray[t - gap]);
    }

}

int main (int argc, char **argv) {

    wav_type *input;
    char opt;
    char *fin = NULL;
    char *fout = NULL;
    int delay = 1000;
    float level= 0.5;

    while ((opt = getopt (argc, argv, "i:o:t:l:")) != -1) {
        switch(opt) {
            case 'i':
                fin = optarg;
                break;
            case 'o':
                fout = optarg;
                break;
            case 't':
                delay = atoi(optarg);
                break;
            case 'l':
                level = atof(optarg);
                break;
        }
    }
    
    input = load_wav(fin,1);
    if (!input)
        return 0;
    create_echo(input,delay,level);
    if (!(write_wav(input,fout)))
        return 0;
    free_wav(input);
    return 1;
}