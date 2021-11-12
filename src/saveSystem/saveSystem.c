#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../utils/constants.h"
#include "saveSystem.h"

void createSaveFile();
void createSaveFolder();

void saveScore(const int playerScore, const int iaScore) {
    FILE *fileRef = fopen(SCORE_SAVE_FULL_FILE_PATH, "w");

    fprintf(fileRef, "Histórico de potuação: Usuário: %d, IA: %d\n", playerScore, iaScore);
    fclose(fileRef);
    
    return;
}

void loadScore(int *playerScore, int *iaScore) {
    FILE *fileRef = fopen(SCORE_SAVE_FULL_FILE_PATH, "r");
    int fileUserScore = 0, fileIaScore = 0;

    fscanf(fileRef, "%d %d", &fileUserScore, &fileIaScore);
    fclose(fileRef);

    *playerScore = fileUserScore;
    *iaScore = fileIaScore;

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
