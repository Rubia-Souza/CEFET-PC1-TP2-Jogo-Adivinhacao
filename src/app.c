#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <time.h>
#include <string.h>

#include "utils/mathUtils.h"
#include "utils/constants.h"
#include "gameplay/userTurn.h"
#include "gameplay/iaTurn.h"

void setUpConfigs();
int getAmountOfTurns();
char evaluateResults(const int iaAttempts, const int userAttempts, const int actualTurn, const int maxTurns);
void printUserScore(const int userScore);
void printScore(const int iaScore, const int userScore);
void evaluateFinalResult(const int iaScore, const int userScore);

int main() {
    setUpConfigs();
    printf("====== Jogo da Adivinhação - Rúbia Alice ======");

    int generatedNumber = 0, amountTurns = 0;
    int userScore = 0, iaScore = 0;
    amountTurns = getAmountOfTurns();

    for (int i = 1; i <= amountTurns; i++) {
        int userAttempts = 0, iaAttempts = 0;

        generatedNumber =  createRandomNumber(MIN_ACCEPTED_NUMBER, MAX_ACCEPTED_NUMBER);
        userAttempts = startUserTurn(generatedNumber);
        printUserScore(userAttempts);

        iaAttempts = startIaTurn();
        if (iaAttempts == -1) {
            printf("\n[JUIZ]: Reiniciando turno devido a ação leviana do usuário.");
            iaAttempts = 0;
            userAttempts = 0;
            i--;
        }

        char winner = evaluateResults(iaAttempts, userAttempts, i, amountTurns);
        if (winner == USER) {
            userScore++;
        }
        else if (winner == IA) {
            iaScore++;
        }

        printScore(iaScore, userScore);
    }

    evaluateFinalResult(iaScore, userScore);

    return 0;
}

void setUpConfigs() {
    setlocale(LC_ALL, DEFAULT_LOCALE);
    srand(time(0));

    return;
}

int getAmountOfTurns() {
    int qtdTunrs = 0;
    bool isInputInvalid = true;

    printf("\nDigite a quantidade de rodadas desejada: ");
    fflush(stdin);
    do {
        scanf("%d", &qtdTunrs);

        isInputInvalid = qtdTunrs <= 0;
        if (isInputInvalid) {
            printf("\nPor favor digite um valor válido que seja maior que 0.\n");
        }
    } while(isInputInvalid);

    return qtdTunrs;
}

char evaluateResults(const int iaAttempts, const int userAttempts, const int actualTurn, const int maxTurns) {
    printf("\nComputador acertou em %d tentativas e o jogador em %d", iaAttempts, userAttempts);
    bool isDraw = iaAttempts == userAttempts || iaAttempts == -1;
    if (isDraw) {
        printf("\nEmpate na rodada número %d de um total de %d.", actualTurn, maxTurns);
        return '\000';
    }

    bool playerWon = iaAttempts < userAttempts;
    char winner[15];
    if (playerWon) {
        strcpy(winner, "Usuário");
    }
    else {
        strcpy(winner, "Computador");
    }

    printf("\n%s venceu a rodada número %d de um total de %d.", winner, actualTurn, maxTurns);

    char result = playerWon ? USER : IA;
    return result;
}

void printUserScore(const int userScore) {
    printf("\nParabéns, você acertou em %d tentativas.", userScore);
    return;
}

void printScore(const int iaScore, const int userScore) {
    printf("\nPlacar das rodadas:\nComputador: %d Usuário: %d", iaScore, userScore);
    return;
}

void evaluateFinalResult(const int iaScore, const int userScore) {
    if (iaScore == userScore) {
        printf("\nHouve um empate.");
    }
    else {
        char winner[15];
        bool playerWon = iaScore < userScore;
        if (playerWon) {
            strcpy(winner, "Usuário");
        }
        else {
            strcpy(winner, "Computador");
        }
        printf("\n%s venceu.", winner);
    }

    printf("\nPlacar final: \n Computador %d Usuário: %d", iaScore, userScore);
    printf("\nHistoricamente o computador já venceu <insert> rodadas e o usuário <insert> rodas.");
    printf("\n____________________________________________");

    return;
}
