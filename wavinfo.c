#include <stdio.h>
#include <unistd.h>
#include "wavlib.h"

int main (int argc, char **argv) {

wav_type *input;
  char opt;
  char *fin = NULL;
  int i;


  while ((opt = getopt (argc, argv, "i:o:")) != -1) {
        switch(opt) {
            case 'i':
                fin = optarg;
                break;
    }
  }
  
  input = load_wav(fin,0);
  if (!input) 
    return 0;
	printf("RIFF tag:            ");
  for (i=0;i<4;i++)
	  printf("%c",input->ChunkID[i]);
	printf("\n");
	printf("RIFF size:           %d\n",input->ChunkSize);
  printf("Wave tag:            ");
  for (i=0;i<4;i++)
		printf("%c",input->Format[i]);
  printf("\n");
  printf("Format tag:          ");
  for (i=0;i<4;i++)
	  printf("%c",input->SubChunk1ID[i]);
  printf("\n");
  printf("Format size:         %d\n",input->SubChunk1Size);
  printf("Audio format:        %d\n",input->AudioFormat);
  printf("Format channels:     %d\n",input->NumberChannels);
  printf("Sample rate:         %d\n",input->SampleRate);
  printf("Byte rate:           %d\n",input->ByteRate);
  printf("Block align:         %d\n",input->BlockAlign);
  printf("Bits/sample:         %d\n",input->BitsSample);
	printf("Data tag:            ");
  for (i=0;i<4;i++)
	  printf("%c",input->SubChunk2ID[i]);
  printf("\n");
  printf("Data size:           %d\n",input->SubChunk2Size);
  printf("Bytes/sample:        %d\n",input->BytesSample);
  printf("Samples/channel:     %d\n",input->SamplesChannel);
  free_wav(input);
  return 1;
}
