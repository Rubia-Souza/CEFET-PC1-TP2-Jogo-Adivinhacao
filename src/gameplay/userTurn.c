#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils/constants.h"
#include "userTurn.h"

void startUserTurn(int ganeratedNumber) {
    printf("Qual o número secreto gerado pelo computador?\n");

    int userGuess = 0, attempts = 0;
    bool userGuessedRight = false;

    printf("Digite um número entre %d e %d: ", MIN_ACCEPTED_NUMBER, MAX_ACCEPTED_NUMBER);
    do {
        userGuess = getUserGuess();
        userGuessedRight = verifyUserGuess(userGuess, ganeratedNumber);
        attempts++;
    } while (!userGuessedRight);

    printf("\nParabéns, você acertou em %d tentativas.", attempts);
    return;
}

int getUserGuess() {
    int userGuess = 0;
    bool isInputInvalid = false;

    do {
        scanf("%d", &userGuess);

        isInputInvalid = userGuess < 0 || userGuess > 20;
        if (isInputInvalid) {
            printf("\nPor favor digite um valor válido, que esteja entre %d e %d", MIN_ACCEPTED_NUMBER, MAX_ACCEPTED_NUMBER);
        }
    } while(isInputInvalid);

    return userGuess;
}

bool verifyUserGuess(int guessValue, int generatedNumber) {
    if (guessValue == generatedNumber) {
        return true;
    }

    char tip[5] = guessValue < generatedNumber ? "maior" : "menor";
    printf("Errou, o número secreto é %s. Tente novamente: ", tip);

    return false;
}
