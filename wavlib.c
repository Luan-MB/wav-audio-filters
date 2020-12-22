#include <stdlib.h>
#include <stdio.h>
#include "wavlib.h"

// Função que lê cabeçalho do arquivo "fin" ou de STDIN, se data != 0, lê-se também o vetor de amostras
// Retorna o arquivo "fin" alocado em memória
wav_type *load_wav (char *fin, int data) {
    
    wav_type *input;
    FILE *arq;
    uint32_t i;

    // Aloca espaço necessário para ler o cabeçalho de arquivos wav
    input = malloc(sizeof(wav_type));
    if (!input) {
        fprintf(stderr,"Erro ao alocar memória\n");
        return NULL;
    }
    
    // Checa se "fin" é != NULL
    // Se for, abre-se o arquivo "arq" com nome apontado pelo mesmo
    if (fin) {
        arq = fopen(fin,"rb");
        if (!arq) {
            fprintf(stderr,"Erro ao abrir o arquivo: %s\n",fin);
            return NULL;
        }
    
    // Lê os 44 bytes de cabeçalho de "arq"
        fread(input,44,1,arq);

        // Se "data" != 0
        // Aloca-se em "input->SamplesArray" (vetor de amostras), "input->SubChunk2Size" (tamanho amostras em bytes)
        // Lê-se o vetor de amostras
        if (data) {
            input->SamplesArray = malloc(input->SubChunk2Size);
            for(i=0;i<(input->SubChunk2Size/(input->BitsSample/8));i++)
                fread(&input->SamplesArray[i],(input->BitsSample/8),1,arq);
        }
        fclose(arq);
    // Se "fin" == NULL, não é necessário abrir arquivo
    } else {
        // Lê os 44 bytes de cabeçalho de STDIN
        fread(input,44,1,stdin);
        
        // Se "data" != 0
        // Aloca-se em "input->SamplesArray" (vetor de amostras), "input->SubChunk2Size" (tamanho amostras em bytes)
        // Lê-se o vetor de amostras
        if (data) {
            input->SamplesArray = malloc(input->SubChunk2Size);
            for(i=0;i<(input->SubChunk2Size/(input->BitsSample/8));i++)
                fread(&input->SamplesArray[i],(input->BitsSample/8),1,stdin);
        }
    }
    
    // Calcula-se os campos "BytesSample" e "SamplesChannel"
    input->BytesSample = input->BitsSample / 8;
    input->SamplesChannel = input->SubChunk2Size/input->BlockAlign;
    
    // Retorna-se input
    return input;
}

// Função que recebe como entrada uma variável do tipo wav e um char*
// Escreve em "fout" o conteúdo de "input" 
// Retorna 1 se sucesso e 0 em caso de falha
int write_wav (wav_type *input, char *fout) {

    FILE *out;
     
    // Se "fout" != NULL
    // Abre-se o arquivo apontado por "fout"
    if (fout) {
        out = fopen(fout,"wb");
        if (!out) {
            fprintf(stderr,"Erro a criar/abrir o arquivo: %s\n",fout);
            return 0;
        }
        // Escreve-se em "out" o conteúdo de "input"
        fwrite(input,44,1,out);
        fwrite(input->SamplesArray,input->SubChunk2Size,1,out);
        fclose(out);
    
    // Se "fout" == NULL
    // Utiliza-se STDOUT
    } else {
        // Escreve-se em STDOUT o conteúdo de "input"
        fwrite(input,44,1,stdout);
        fwrite(input->SamplesArray,input->SubChunk2Size,1,stdout);
    }
    return 1;
}

// Recebe uma varíavel wav e a desaloca da memória
void free_wav (wav_type *input) {

    free(input->SamplesArray);
    input->SamplesArray = NULL;
    free(input);
    input = NULL;
}
