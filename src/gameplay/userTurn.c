#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../utils/constants.h"
#include "userTurn.h"

int getUserGuess();
bool verifyUserGuess(const int guessValue, const int generatedNumber);

int startUserTurn(const int ganeratedNumber) {
    printf("\n[IA]: Qual o meu número secreto? <_<\n[IA]: >.>");

    int userGuess = 0, attempts = 0;
    bool userGuessedRight = false;

    printf("\n[JUIZ]: Digite um número entre %d e %d: ", MIN_ACCEPTED_NUMBER, MAX_ACCEPTED_NUMBER);
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
            printf("\n[JUIZ]: Por favor digite um valor válido, que esteja entre %d e %d", MIN_ACCEPTED_NUMBER, MAX_ACCEPTED_NUMBER);
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

    printf("\n[IA]: >:3 AAAA, Errou! O número secreto é %s. Tente de novo: ", tip);

    return false;
}
