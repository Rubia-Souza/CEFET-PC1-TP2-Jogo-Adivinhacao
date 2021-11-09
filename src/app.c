#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

#include "utils/utils.h"
#include "utils/constants.h"
#include "gameplay/userTurn.h"
#include "gameplay/iaTurn.h"

int main() {
    setUpConfigs();

    int generatedNumber = 0, amountTurns = 0;
    int userScore = 0, iaScore = 0;
    amountTurns = getAmountOfTurns();

    for (int i = 1; i <= amountTurns; i++) {
        int userAttempts = 0, iaAttempts = 0;

        generatedNumber =  createRandomNumber(MIN_ACCEPTED_NUMBER, MAX_ACCEPTED_NUMBER);
        userAttempts = startUserTurn(generatedNumber);
        iaAttempts = startIaTurn();

        char winner = evaluateResults(iaAttempts, userAttempts, i, amountTurns);
        if (winner == USER) {
            userScore++;
        }
        else {
            iaScore++;
        }

        printScore(iaScore, userScore);
    }

    evaluateFinalResult(iaScore, userScore);

    return 0;
}

void setUpConfigs() {
    setlocale(LC_ALL, DEFAULT_LOCALE);

    return;
}

int getAmountOfTurns() {
    int qtdTunrs = 0;
    bool isInputValid = false;

    printf("Digite a quantidade de rodadas desejada: ");
    do {
        scanf("%d", &qtdTunrs);

        isInputValid = qtdTunrs <= 0;
        if (!isInputValid) {
            printf("\nPor favor digite um valor válido que seja maior que 0.\n");
        }
    } while(!isInputValid);

    return qtdTunrs;
}

char evaluateResults(const int iaAttempts, const int userAttempts, const int actualTurn, const int maxTurns) {
    printf("\nComputador acertou em %d tentativas e o jogador em %d", iaAttempts, userAttempts);
    bool isDraw = iaAttempts == userAttempts;
    if (isDraw) {
        printf("\nEmpate na rodada número %d de um total de %d.", actualTurn, maxTurns);
        return;
    }

    bool playerWon = iaAttempts < userAttempts;
    char winner[10] = playerWon ? "Usuário" : "Computador";
    printf("\n%s venceu a rodada número %d de um total de %d.", winner, actualTurn, maxTurns);

    char result = playerWon ? USER : IA;
    return result;
}

void printScore(const int iaScore, const int userScore) {
    printf("\nPlacar das rodadas:\nComputador:  %d Usuário: %d", iaScore, userScore);
    return;
}

void evaluateFinalResult(const int iaScore, const int userScore) {
    if (iaScore == userScore) {
        printf("\nHouve um empate.");
    }
    else {
        char winner[10] = iaScore < userScore ? "Usuário" : "Computador";
        printf("\n%s venceu.", winner);
    }

    printf("\nPlacar final: \n Computador %d Usuário: %d", iaScore, userScore);
    printf("\nHistoricamente o computador já venceu <insert> rodadas e o usuário <insert> rodas.");
    printf("\n____________________________________________");

    return;
}
