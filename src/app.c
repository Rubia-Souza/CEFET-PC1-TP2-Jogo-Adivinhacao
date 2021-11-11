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

        askToThinkANumber();

        iaAttempts = startIaTurn();
        bool userIsStealing = iaAttempts == -1;
        if (userIsStealing) {
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

    printf("\n[JUIZ]: Digite a quantidade de rodadas desejada: ");
    fflush(stdin);
    do {
        scanf("%d", &qtdTunrs);

        isInputInvalid = qtdTunrs <= 0;
        if (isInputInvalid) {
            printf("\n[JUIZ]: Por favor digite um valor válido que seja maior que 0.\n");
        }
    } while(isInputInvalid);

    return qtdTunrs;
}

void askToThinkANumber() {
    printf("\n[JUIZ]: Pense em um número secreto entre 0 e 20. Pensou (s/n)?");
    fflush(stdin);
    
    char userInput;
    bool isInputValid;

    do {
        scanf("%c", &userInput);

        isInputValid = userInput == 's' || userInput == 'n';
        if (!isInputValid) {
            printf("\n[JUIZ]: Por favor digite [s] para sim ou [n] para não");
        }
    } while (!isInputValid);

    return;
}

char evaluateResults(const int iaAttempts, const int userAttempts, const int actualTurn, const int maxTurns) {
    printf("\n[JUIZ]: Computador acertou em %d tentativas e o jogador em %d", iaAttempts, userAttempts);
    bool isDraw = iaAttempts == userAttempts;
    if (isDraw) {
        printf("\n[JUIZ]: Empate na rodada número %d de um total de %d.", actualTurn, maxTurns);
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

    printf("\n[JUIZ]: %s venceu a rodada número %d de um total de %d.", winner, actualTurn, maxTurns);

    char result = playerWon ? USER : IA;
    return result;
}

void printUserScore(const int userScore) {
    printf("\n[IA]: Parabéns, você acertou em %d tentativas. >.<", userScore);
    return;
}

void printScore(const int iaScore, const int userScore) {
    printf("\n[JUIZ]: Placar das rodadas:\nComputador: %d Usuário: %d", iaScore, userScore);
    return;
}

void evaluateFinalResult(const int iaScore, const int userScore) {
    if (iaScore == userScore) {
        printf("\n[JUIZ]: Houve um empate.");
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
        printf("\n[JUIZ]: %s venceu.", winner);
    }

    printf("\n[JUIZ]: Placar final: \n Computador %d Usuário: %d", iaScore, userScore);
    printf("\n[JUIZ]: Historicamente o computador já venceu <insert> rodadas e o usuário <insert> rodas.");
    printf("\n____________________________________________");

    return;
}
