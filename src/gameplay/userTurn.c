#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../utils/constants.h"
#include "userTurn.h"

/*
 * Pede para o jogador chutar um número
 */
int getUserGuess();

/*
 * Verifica se o chute do jogador está correto
 */
bool verifyUserGuess(const int guessValue, const int generatedNumber);

int startUserTurn(const int ganeratedNumber) {
    printf("\n[IA]: Qual o meu número secreto? <_<\n[IA]: >.>");

    int userGuess = 0, attempts = 0;
    bool userGuessedRight = false;

    printf("\n[JUIZ]: Digite um número entre %d e %d: ", MIN_ACCEPTED_NUMBER, MAX_ACCEPTED_NUMBER);
    // Enquanto o jogador não acertar o número, a função permanece no loop
    do {
        userGuess = getUserGuess(); // Pede um valor para o usuário
        userGuessedRight = verifyUserGuess(userGuess, ganeratedNumber); // Verifica se está correto
        attempts++; // Cada valor dado é adicionado como uma tentativa
    } while (!userGuessedRight);

    return attempts;
}

int getUserGuess() {
    int userGuess = 0;
    bool isInputInvalid = false;

    do {
        fflush(stdin);
        scanf("%d", &userGuess);

        isInputInvalid = userGuess < MIN_ACCEPTED_NUMBER || userGuess > MAX_ACCEPTED_NUMBER;
        if (isInputInvalid) {// Verifica se o número informado esta na faixa válida do jogo
            printf("\n[JUIZ]: Por favor digite um valor válido, que esteja entre %d e %d: ", MIN_ACCEPTED_NUMBER, MAX_ACCEPTED_NUMBER);
        }
    } while(isInputInvalid);

    return userGuess;
}

bool verifyUserGuess(const int guessValue, const int generatedNumber) {
    // Inicialmente, verifica se o chute está certo
    if (guessValue == generatedNumber) {
        return true; // Se sim já retorna true
    }

    // Se não, verifica se o chute foi acima ou abaixo do valor gerado
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
