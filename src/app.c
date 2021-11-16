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
#include "saveSystem/saveSystem.h"

/*
 * Aluna: Rúbia Alice Moreira de Souza
 * Curso: Engenharia da Computação - CEFET-MG
 */

/*
 * Configura funções para valores padrões no projeto e
 * prepara o arquivo de save
 */
void setUpConfigs();

/*
 * Pergunta ao usuário a quantidade de turnos que serão executados
 */
int getAmountOfTurns();

/*
 * Pergunta ao usuário qual modo de jogo ele deseja que a IA siga
 */
char getGameMode();

/*
 * Pede ao usuário para que pense em um número, preparando para iniciar
 * o turno do computador
 */
void askToThinkANumber();

/*
 * Verifica os resutados de um turno considerando a quantidade de tentativas
 */
char evaluateResults(const int iaAttempts, const int userAttempts, const int actualTurn, const int maxTurns);

/*
 * Imprime a pontuação do usuário no fim do turno em que ele adivinha o número do pc
 */
void printUserScore(const int userScore);

/*
 * Imprime a pontuação final de um turno
 */
void printScore(const int iaScore, const int userScore);

/*
 * Avalia o resultado de todos os turnos e define o possível vencedor
 */
void evaluateFinalResult(const int iaScore, const int userScore);

int main() {
    setUpConfigs();
    printf("====== Jogo da Adivinhação - Rúbia Alice ======");

    int generatedNumber = 0, amountTurns = 0;
    int userScore = 0, iaScore = 0;
    amountTurns = getAmountOfTurns();
    char gameMode = getGameMode();

    for (int i = 1; i <= amountTurns; i++) {
        printf("\n\n<<<< Iniciando o turno %d >>>>", i);
        int userAttempts = 0, iaAttempts = 0;

        // Inicia o turno em que o usuário deverá adivinhar o número
        printf("\n[JUIZ]: Iniciando vez do usuário");
        generatedNumber =  createRandomNumber(MIN_ACCEPTED_NUMBER, MAX_ACCEPTED_NUMBER);
        userAttempts = startUserTurn(generatedNumber);
        printUserScore(userAttempts);

        // Pede ao usuário para pensar em um número e se preparar para o turno do pc
        askToThinkANumber();

        // Inicia o turno em que o computador deverá adivinhar o número
        printf("\n[JUIZ]: Iniciando vez da IA");
        iaAttempts = startIaTurn(gameMode);

        // Verifica se o usuário foi inconsistente com as respostas, levando a nenhum resultado possível
        bool userIsStealing = iaAttempts == -1;
        if (userIsStealing) {
            printf("\n[JUIZ]: Reiniciando turno devido a ação leviana do usuário.");
            iaAttempts = 0;
            userAttempts = 0;
            i--; // Então, o contador de turnos é decrementado para reinicia-lo
        }

        // Avalia os resultados, por meio das tentativas, de um turno
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
    setlocale(LC_ALL, DEFAULT_LOCALE); // Configura a linguagem como portugues
    srand(time(0)); // Faz configuração inicial para criar números aleatórios
    createSave(); // Cria a pasta e o arquivo para salvar as pontuações se ainda não existirem

    return;
}

int getAmountOfTurns() {
    int qtdTunrs = 0;
    bool isInputInvalid = true;

    printf("\n[JUIZ]: Digite a quantidade de rodadas desejada: ");
    do {
        fflush(stdin); // Limpa buffer de entrada para evitar alguma entrada não necessária
        scanf("%d", &qtdTunrs);

        isInputInvalid = qtdTunrs <= 0;
        if (isInputInvalid) { // Valida se a quantidade de turnos informada é válida
            printf("\n[JUIZ]: Por favor digite um valor válido que seja maior que 0: ");
        }
    } while(isInputInvalid);

    return qtdTunrs;
}

char getGameMode() {
    int gameMode;
    bool isInputValid = false;

    printf("\n[1]: Modo IA binária: Seleciona o número intermediário entre o menor e maior já informado");
    printf("\n[2]: Modo IA Extrema: Seleciona um número aleatório entre o menor e maior já informado");
    printf("\n[3]: Modo IA Possibilidades: Seleciona um número aleatório entre um array de possibilidades");
    printf("\n[JUIZ]: Escolha um modo dos modos de jogo: ");

    do {
        fflush(stdin); // Limpa buffer de entrada para evitar alguma entrada não necessária
        scanf("%d", &gameMode);

        isInputValid = gameMode >= 1 && gameMode <= 3;
        if (!isInputValid) { // Valida se o modo de jogo escolhido é válido
            printf("\n[JUIZ]: Digite uma das três opções: 1, 2 ou 3: ");
        }
    } while (!isInputValid);

    // Retorna a constante relacionado ao modo selecionado
    switch (gameMode) {
        case 1: return BINARY_MODE;
        case 2: return EXTREMES_MODE;
        case 3: return POSSIBILITYS_MODE;
    }

    return POSSIBILITYS_MODE;
}

void askToThinkANumber() {
    printf("\n[JUIZ]: Pense em um número secreto entre 0 e 20. Pensou (s/n)? ");
    
    char userInput;
    bool isInputValid = false;

    do {
        fflush(stdin); // Limpa buffer de entrada para evitar alguma entrada não necessária
        scanf("%c", &userInput);

        isInputValid = userInput == 's' || userInput == 'n';
        if (!isInputValid) { // Avalia se a escolha digitada pelo usuário é válida
            printf("\n[JUIZ]: Por favor digite [s] para sim ou [n] para não: ");
        }
        else if (userInput == 'n') { // Continua a questionar o usuário até decidir
            printf("\n[JUIZ]: Já pensou (s/n)? ");
        }
    } while (userInput != 's');

    return;
}

char evaluateResults(const int iaAttempts, const int userAttempts, const int actualTurn, const int maxTurns) {
    printf("\n[JUIZ]: Computador acertou em %d tentativas e o jogador em %d", iaAttempts, userAttempts);
    // Verifica se houve um empate em um turno
    bool isDraw = iaAttempts == userAttempts;
    if (isDraw) {
        printf("\n[JUIZ]: Empate na rodada número %d de um total de %d.", actualTurn, maxTurns);
        return '\000';
    }

    // Avalia qual foi o vencedor do turno
    bool playerWon = userAttempts < iaAttempts;
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
    if (iaScore == userScore) { // Verifica se houve um empate no jogo
        printf("\n[JUIZ]: Houve um empate.");
    }
    else { // Se não, verifica qual foi o vencedor
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

    // Então, ele carrega as informações do arquivo de texto se houver
    // Caso não esteja presente as variáveis permanecem 0
    int userHistoryScore = 0, iaHistoryScore = 0;
    loadScore(&userHistoryScore, &iaHistoryScore);

    // Depois elas são incrementadas conforme a pontuação obtida pelo jogador e pelo pc
    userHistoryScore += userScore;
    iaHistoryScore += iaScore;

    // Por fim, as novas potuações são salvas no arquivo save.txt
    saveScore(userHistoryScore, iaHistoryScore);

    printf("\n[JUIZ]: Placar final: \n Computador %d | Usuário: %d", iaScore, userScore);
    printf("\n[JUIZ]: Historicamente o computador já venceu %d rodadas e o usuário %d rodas.", iaHistoryScore, userHistoryScore);
    printf("\n____________________________________________");

    return;
}
