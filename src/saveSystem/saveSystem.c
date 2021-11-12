#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../utils/constants.h"
#include "saveSystem.h"

void createSaveFile();
void createSaveFolder();

const char SPLIT_CHARACTER = '|';

void saveScore(const int playerScore, const int iaScore) {
    FILE *fileRef = fopen(SCORE_SAVE_FULL_FILE_PATH, "w");

    fprintf(fileRef, "Histórico de potuação: Usuário: %d %c IA: %d\n", playerScore, SPLIT_CHARACTER, iaScore);
    fclose(fileRef);
    
    return;
}

void loadScore(int *playerScore, int *iaScore) {
    char actualCharacter = 'a';
    char fileUserScore[100], fileIaScore[100];
    char *target = fileUserScore;
    int fillIndex = 0;
    bool foundSplitCharacter = false;
    FILE *fileRef = fopen(SCORE_SAVE_FULL_FILE_PATH, "r");

    while(actualCharacter != EOF) {
        actualCharacter = fgetc(fileRef);

        foundSplitCharacter = actualCharacter == SPLIT_CHARACTER;
        if (foundSplitCharacter) {
            target = fileIaScore;
            fillIndex = 0;
        }

        if (isdigit(actualCharacter)) {
            target[fillIndex] = actualCharacter;
            fillIndex++;
        }
    }

    fclose(fileRef);

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

    if (stat(SCORE_SAVE_PATH, &directory) == -1) {
        mkdir(SCORE_SAVE_PATH);
    }

    return;
}

void createSaveFile() {
    FILE *fileRef = fopen(SCORE_SAVE_FULL_FILE_PATH, "a");
    fclose(fileRef);

    return;
}
