#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "../utils/constants.h"
#include "../utils/mathUtils.h"
#include "../utils/arrayUtils.h"

int startExtremesMode();

int startBinaryDivisionMode();

int startPossiblitysMode();

/*
 * Pergunta ao jogador se o chute do computador esta correto
 */
bool validateGuess(const int guessNumber);

/*
 * Verifica com o usuário se o número pensado é maior que o gerado pela ia
 */
bool checkWithUserIfNumberIsHigher(const int lastValue);

/* MODO: 1
 * Gera um novo valor sempre como o intermediário entre o maior e menor valor definido anteriormente
 */
int guessOtherValueBasedOnBinaryDivision(const int lastValue, int *highestValue, int *lowestValue);

/* MODO: 2
 * Gera um novo valor com base na troca da definição de qual é o maior e o menor número possível
 * definidos de acordo com as tentativas anteriores
 */
int guessOtherValueBasedOnExtremes(const int lastValue, int *highestValue, int *lowestValue);

/* MODO: 3
 * Gera um novo valor com base em um array que possui todos os números válidos ainda não chutados
 * que sobram com base em chutes anteriores
 */
int guessOtherValueBasedOnPossibleValues(const int lastValue, int availableNumbers[POSSIBLE_NUMBERS_ARRAY_SIZE]);

int startIaTurn(const char IAmode) {
    // Seleciona o modo de chute da IA com base no modo selecionado no início do programa
    switch (IAmode) {
        case EXTREMES_MODE: return startExtremesMode();
        
        case BINARY_MODE: return startBinaryDivisionMode();

        case POSSIBILITYS_MODE: return startPossiblitysMode();
    }

    return -1;
}

int startExtremesMode() {
    bool userIsStealing = false, isGuessRight = false;
    int attemps = 0, guessNumber = 0;
    int highestValue = MAX_ACCEPTED_NUMBER, lowestValue = MIN_ACCEPTED_NUMBER;

    guessNumber = createRandomNumber(lowestValue, highestValue);

    do {
        userIsStealing = guessNumber == -1;
        if (userIsStealing) {
            printf("\n[IA]: Que?! Isso não é possível. :o\n[IA]: Você tá robando ¬_¬");
            return -1;
        }

        isGuessRight = validateGuess(guessNumber);
        attemps++;

        if (!isGuessRight) {
            guessNumber = guessOtherValueBasedOnExtremes(guessNumber, &highestValue, &lowestValue);
        }
    } while(!isGuessRight);

    return attemps;
}

int startBinaryDivisionMode() {
    bool userIsStealing = false, isGuessRight = false;
    int attemps = 0, guessNumber = 0;
    int highestValue = MAX_ACCEPTED_NUMBER, lowestValue = MIN_ACCEPTED_NUMBER;

    guessNumber = createRandomNumber(lowestValue, highestValue);

    do {
        userIsStealing = guessNumber == -1;
        if (userIsStealing) {
            printf("\n[IA]: Que?! Isso não é possível. :o\n[IA]: Você tá robando ¬_¬");
            return -1;
        }

        isGuessRight = validateGuess(guessNumber);
        attemps++;

        if (!isGuessRight) {
            guessNumber = guessOtherValueBasedOnBinaryDivision(guessNumber, &highestValue, &lowestValue);
        }
    } while(!isGuessRight);

    return attemps;
}

int startPossiblitysMode() {
    bool isGuessRight = false, userIsStealing = false;
    int attempts = 0;

    // Inicialmente, cria um array que possui os números válidos para serem chutados
    int availableNumbers[POSSIBLE_NUMBERS_ARRAY_SIZE];
    fillArrayWithCount(0, POSSIBLE_NUMBERS_ARRAY_SIZE-1, availableNumbers);
    availableNumbers[POSSIBLE_NUMBERS_ARRAY_SIZE-1] = NULL_NUMBER;

    // Então, é gerado um chute qualquer entre os valores extremos
    int guessNumber = createRandomNumber(MIN_ACCEPTED_NUMBER, MAX_ACCEPTED_NUMBER);

    do {
        // Verifica se o jogador não aceitou nenhum número como resposta e retorna -1 para reiniciar o turno
        userIsStealing = guessNumber == -1;
        if (userIsStealing) {
            printf("\n[IA]: Que?! Isso não é possível. :o\n[IA]: Você tá robando ¬_¬");
            return -1;
        }

        // Verifica se o número gerado pelo pc está certo
        isGuessRight = validateGuess(guessNumber);
        attempts++; // Para cada número chutado, uma nova tentativa é adicionada

        // Enquanto o chute não estiver correto, o pc gera um novo número aleatório com base nos números possíves restantes
        if (!isGuessRight) {
            guessNumber = guessOtherValueBasedOnPossibleValues(guessNumber, availableNumbers);
        }
    } while(!isGuessRight);

    return attempts;
}

bool validateGuess(const int guessNumber) {
    printf("\n[IA]: >:/ Você... pensou no número... :D %d! (s/n)? ", guessNumber);

    bool isInputValid = false;
    char validation;

    do {
        fflush(stdin);
        scanf("%c", &validation);

        isInputValid = validation == 's' || validation == 'n';
        if (!isInputValid) { // Verifica se o input de s ou n do jogador é válido
            printf("\n[JUIZ]: Por favor digite [s] para sim ou [n] para não: ");
        }
    } while (!isInputValid);

    return validation == 's';
}

bool checkWithUserIfNumberIsHigher(const int lastValue) {
    printf("\n[IA]: :S Hummm... o número é maior do que %d (s/n)? ", lastValue);

    bool isInputValid = false;
    char userAwnser;

    // Verifica se o número do chute é menor ou maior que o pensado pelo jogador
    do {
        fflush(stdin);
        scanf("%c", &userAwnser);

        isInputValid = userAwnser == 's' || userAwnser == 'n';
        if (!isInputValid) {
            printf("\n[JUIZ]: Por favor digite [s] para sim ou [n] para não: ");
        }
    } while (!isInputValid);

    return userAwnser == 's';
}

int guessOtherValueBasedOnExtremes(const int lastValue, int *highestValue, int *lowestValue) {
    bool isValueBigger = checkWithUserIfNumberIsHigher(lastValue);

    // Verifica se os valores máximo e mínimo chegaram ao mesmo número. Se sim, o jogador deu respostas inconsistentes
    if (*highestValue == *lowestValue) {
        return -1;
    }

    if (isValueBigger) { // Verifica se o número pensado pelo jogador é maior que o chute anterior.
        *lowestValue = lastValue + 1; // Se o valor anteriror é maior, então o mínimo passa a ser o número acima dele
    }
    else { // Verifica se o número pensado pelo jogador é menor que o chute anterior.
        *highestValue = lastValue - 1; // Se o valor anterior é menor, então o máximo passa a ser o número abaixo dele
    }
    
    return createRandomNumber(*lowestValue, *highestValue); // Então, ele gera um número aleatório qualquer entre os dois
}

int guessOtherValueBasedOnBinaryDivision(const int lastValue, int *highestValue, int *lowestValue) {
    bool isValueBigger = checkWithUserIfNumberIsHigher(lastValue);

    // Verifica se os valores máximo e mínimo chegaram ao mesmo número. Se sim, o jogador deu respostas inconsistentes
    if (*highestValue == *lowestValue) {
        return -1;
    }

    if (isValueBigger) { // Verifica se o número pensado pelo jogador é maior que o chute anterior.
        *lowestValue = lastValue + 1; // Se o valor anteriror é maior, então o mínimo passa a ser o número acima dele
    }
    else { // Verifica se o número pensado pelo jogador é menor que o chute anterior.
        *highestValue = lastValue - 1; // Se o valor anterior é menor, então o máximo passa a ser o número abaixo dele
    }

    return ceil((*highestValue + *lowestValue) / 2); // Então, ele pega a metade entre o máximo e o mínimo arredondado para cima
}

int guessOtherValueBasedOnPossibleValues(const int lastValue, int availableNumbers[POSSIBLE_NUMBERS_ARRAY_SIZE]) {
    int filteredNumbers[POSSIBLE_NUMBERS_ARRAY_SIZE];
    int filteredNumbersSize = POSSIBLE_NUMBERS_ARRAY_SIZE;

    bool isValueBigger = checkWithUserIfNumberIsHigher(lastValue);
    if (isValueBigger) { // Verifica se o número pensado pelo jogador é maior que o chute anterior.
        cutLeftPartArray(availableNumbers, lastValue, &filteredNumbersSize, filteredNumbers); // Se sim, ele remove o chute e todos os números menores que ele (a esquerda do array)
    }
    else { // Verifica se o número pensado pelo jogador é menor que o chute anterior.
        cutRightPartArray(availableNumbers, lastValue, &filteredNumbersSize, filteredNumbers); // Se sim, ele remove o chute e todos os números maiores que ele (a direita do array)
    }

    // Caso todos os números tenham sido removidos do array de possibilidades, o jogador deu dicas que impossibilitam uma respota e o retorno da função será -1 (para reiniciar o turno)
    if (filteredNumbers[0] == NULL_NUMBER) {
        return -1;
    }

    // Caso ainda haja números no array de possibilidades, o pc pega um index aleatório entre 0 e a quantidade de números restantes no array
    int randomNumberIndex = createRandomNumber(0, filteredNumbersSize);
    copyArray(filteredNumbers, POSSIBLE_NUMBERS_ARRAY_SIZE, availableNumbers);

    return availableNumbers[randomNumberIndex]; // Então, ele chuta o número presente no index aleatório gerado
}
