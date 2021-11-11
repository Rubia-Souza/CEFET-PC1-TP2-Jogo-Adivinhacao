#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../utils/constants.h"
#include "../utils/mathUtils.h"
#include "../utils/arrayUtils.h"

bool validateGuess(const int guessNumber);
int guessOtherValueBasedOnLast(const int lastValue, int availableNumbers[POSSIBLE_NUMBERS_ARRAY_SIZE]);

int startIaTurn() {
    bool isGuessRight = false, userIsStealing = false;
    int attempts = 0;

    int availableNumbers[POSSIBLE_NUMBERS_ARRAY_SIZE];
    fillArrayWithCount(0, POSSIBLE_NUMBERS_ARRAY_SIZE-1, availableNumbers);
    availableNumbers[POSSIBLE_NUMBERS_ARRAY_SIZE-1] = NULL_NUMBER;

    int guessNumber = createRandomNumber(MIN_ACCEPTED_NUMBER, MAX_ACCEPTED_NUMBER);

    do {
        userIsStealing = guessNumber == -1;
        if (userIsStealing) {
            printf("\n[IA]: Que?! Isso não é possível. :o\n Você tá robando ¬_¬");
            return -1;
        }

        isGuessRight = validateGuess(guessNumber);
        attempts++;

        if (!isGuessRight) {
            guessNumber = guessOtherValueBasedOnLast(guessNumber, availableNumbers);
        }
    } while(!isGuessRight);

    return attempts;
}

bool validateGuess(const int guessNumber) {
    printf("\n[IA]: >:/ Você... penso no número... :D %d! (s/n)? ", guessNumber);
    fflush(stdin);

    bool isInputValid = false;
    char validation;

    do {
        scanf("%c", &validation);

        isInputValid = validation == 's' || validation == 'n';
        if (!isInputValid) {
            printf("\n[JUIZ]: Por favor digite [s] para sim ou [n] para não");
        }
    } while (!isInputValid);

    return validation == 's';
}

int guessOtherValueBasedOnLast(const int lastValue, int availableNumbers[POSSIBLE_NUMBERS_ARRAY_SIZE]) {
    printf("\n[IA]: :S Hummm... o número é maior do que %d (s/n)? ", lastValue);
    fflush(stdin);

    bool isInputValid = false;
    char userAwnser;

    do {
        scanf("%c", &userAwnser);

        isInputValid = userAwnser == 's' || userAwnser == 'n';
        if (!isInputValid) {
            printf("\n[JUIZ]: Por favor digite [s] para sim ou [n] para não");
        }
    } while (!isInputValid);

    int filteredNumbers[POSSIBLE_NUMBERS_ARRAY_SIZE];
    int filteredNumbersSize = POSSIBLE_NUMBERS_ARRAY_SIZE;

    bool isValueBigger = userAwnser == 's';
    if (isValueBigger) {
        cutLeftPartArray(availableNumbers, lastValue, &filteredNumbersSize, filteredNumbers);
    }
    else {
        cutRightPartArray(availableNumbers, lastValue, &filteredNumbersSize, filteredNumbers);
    }

    if (filteredNumbers[0] == NULL_NUMBER) {
        return -1;
    }

    int randomNumberIndex = createRandomNumber(0, filteredNumbersSize);
    copyArray(filteredNumbers, POSSIBLE_NUMBERS_ARRAY_SIZE, availableNumbers);

    return availableNumbers[randomNumberIndex];
}
