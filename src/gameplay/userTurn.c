#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../utils/constants.h"
#include "userTurn.h"

int getUserGuess();
bool verifyUserGuess(const int guessValue, const int generatedNumber);

int startUserTurn(const int ganeratedNumber) {
    printf("\nQual o número secreto gerado pelo computador?");

    int userGuess = 0, attempts = 0;
    bool userGuessedRight = false;

    printf("\nDigite um número entre %d e %d: ", MIN_ACCEPTED_NUMBER, MAX_ACCEPTED_NUMBER);
    fflush(stdin);
    do {
        userGuess = getUserGuess();
        userGuessedRight = verifyUserGuess(userGuess, ganeratedNumber);
        attempts++;
    } while (!userGuessedRight);

    return attempts;
}

int getUserGuess() {
    int userGuess = 0;
    bool isInputInvalid = false;
    fflush(stdin);

    do {
        scanf("%d", &userGuess);

        isInputInvalid = userGuess < 0 || userGuess > 20;
        if (isInputInvalid) {
            printf("\nPor favor digite um valor válido, que esteja entre %d e %d", MIN_ACCEPTED_NUMBER, MAX_ACCEPTED_NUMBER);
        }
    } while(isInputInvalid);

    return userGuess;
}

bool verifyUserGuess(const int guessValue, const int generatedNumber) {
    if (guessValue == generatedNumber) {
        return true;
    }

    char tip[10];
    if (guessValue < generatedNumber) {
        strcpy(tip, "maior");
    }
    else {
        strcpy(tip, "menor");
    }

    printf("\nErrou, o número secreto é %s. Tente novamente: ", tip);

    return false;
}
