#ifndef __WAVLIB__
#define __WAVLIB__

#include <inttypes.h>

// Define a estrutura de um arquivo wav

typedef struct {

	char ChunkID[4];
	uint32_t ChunkSize;
	char Format[4];
	char SubChunk1ID[4];
	uint32_t SubChunk1Size;
	uint16_t AudioFormat;
	uint16_t NumberChannels;
	uint32_t SampleRate;
	uint32_t ByteRate;
	uint16_t BlockAlign;
	uint16_t BitsSample;
	char SubChunk2ID[4];
	uint32_t SubChunk2Size;
    uint16_t BytesSample;
    uint32_t SamplesChannel;
    int16_t *SamplesArray;
} wav_type;

// Função que lê cabeçalho do arquivo "fin" ou de STDIN, se data != 0, lê-se também o vetor de amostras
// Retorna o arquivo "fin" alocado em memória
wav_type *load_wav(char *fin, int data);

// Função que escreve "input" em "fout" ou em STDOUT
int write_wav (wav_type *input, char *fout);

// Função que desaloca da memória "input"
void free_wav (wav_type *input);

#endif