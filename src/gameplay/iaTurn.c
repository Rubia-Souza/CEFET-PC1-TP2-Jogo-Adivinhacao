#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../utils/constants.h"
#include "../utils/utils.h"

bool validateGuess(const int guessNumber);
int guessOtherValueBasedOnLast(const int lastValue);

int startIaTurn() {
    bool isGuessRight = false;
    int attempts = 0;
    int guessNumber = createRandomNumber(MIN_ACCEPTED_NUMBER, MAX_ACCEPTED_NUMBER);

    do {
        isGuessRight = validateGuess(guessNumber);
        attempts++;

        if (!isGuessRight) {
            guessNumber = guessOtherValueBasedOnLast(guessNumber);
        }
    } while(!isGuessRight);

    return attempts;
}

bool validateGuess(const int guessNumber) {
    printf("\nO número secreto é %d (s/n)? ", guessNumber);
    fflush(stdin);

    bool isInputValid = false;
    char validation;

    do {
        scanf("%c", &validation);

        isInputValid = validation == 's' || validation == 'n';
        if (!isInputValid) {
            printf("\nPor favor digite [s] para sim ou [n] para não");
        }
    } while (!isInputValid);

    return validation == 's';
}

int guessOtherValueBasedOnLast(const int lastValue) {
    printf("\nO número é maior do que %d (s/n)? ", lastValue);
    fflush(stdin);

    bool isInputValid = false;
    char userAwnser;

    do {
        scanf("%c", &userAwnser);

        isInputValid = userAwnser == 's' || userAwnser == 'n';
        if (!isInputValid) {
            printf("\nPor favor digite [s] para sim ou [n] para não");
        }
    } while (!isInputValid);

    bool isValueBigger = userAwnser == 's';
    int newGuess = 0;
    if (isValueBigger) {
        newGuess = createRandomNumber(lastValue, MAX_ACCEPTED_NUMBER);
    }
    else {
        newGuess = createRandomNumber(MIN_ACCEPTED_NUMBER, lastValue);
    }

    return newGuess;
}
