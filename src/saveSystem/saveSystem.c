#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../utils/constants.h"
#include "saveSystem.h"

/*
 * Cria o arquivo que salva as pontuações do jogo
 */
void createSaveFile();

/*
 * Cria a pasta para armazenar arquivos de save do jogo
 */
void createSaveFolder();

// Define o caracter que será usado para identificar a separação da pontuação do jogador com o do pc
const char SPLIT_CHARACTER = '|';

void saveScore(const int playerScore, const int iaScore) {
    // Abre o arquivo em modo W para já re-escrever os valores atualizando-os
    FILE *fileRef = fopen(SCORE_SAVE_FULL_FILE_PATH, "w");

    // Escreve os valores no arquivo de save separados pelo SPLIT_CHARACTER
    fprintf(fileRef, "Histórico de potuação: Usuário: %d %c IA: %d\n", playerScore, SPLIT_CHARACTER, iaScore);
    fclose(fileRef);
    
    return;
}

void loadScore(int *playerScore, int *iaScore) {
    char actualCharacter = 'a';
    char fileUserScore[100], fileIaScore[100];
    char *target = fileUserScore; // Define um ponteiro para poder preencher, tanto a pontuação do jogador quanto da ia em uma única interação sobre o arquivo
    int fillIndex = 0;
    bool foundSplitCharacter = false;
    FILE *fileRef = fopen(SCORE_SAVE_FULL_FILE_PATH, "r");

    while(actualCharacter != EOF) { // Percorre o arquivo até o fim
        actualCharacter = fgetc(fileRef);

        // Para cada caracter, ela verifica se é um separador
        foundSplitCharacter = actualCharacter == SPLIT_CHARACTER;
        if (foundSplitCharacter) { // Caso seja, ela finalizou a leitura de dados da primeira pontuação (jogador) e passa para a próxima (pc)
            target = fileIaScore;
            fillIndex = 0;
        }

        // Para cada caracter, verfica se ele é um número
        if (isdigit(actualCharacter)) { // Caso seja, o array atual é preenchido com aquele número
            target[fillIndex] = actualCharacter;
            fillIndex++;
        }
    }

    fclose(fileRef);

    // Por fim, os números registrados nos arrays são convertidos de string para int
    *playerScore = atoi(fileUserScore);
    *iaScore = atoi(fileIaScore);

    return;
}

void createSave(){
    createSaveFolder();
    createSaveFile();
}

void createSaveFolder() {
    struct stat directory = {0};

    // Verifica se já existe o diretório de save do jogo
    if (stat(SCORE_SAVE_PATH, &directory) == -1) { // Se não, ele é criado
        mkdir(SCORE_SAVE_PATH);
    }

    return;
}

void createSaveFile() {
    // Tenta abrir o arquivo em modo a, pois caso já exista ele é apenas aberto. Por outro lado, caso não exista, ele é criado
    FILE *fileRef = fopen(SCORE_SAVE_FULL_FILE_PATH, "a");
    fclose(fileRef);

    return;
}
