#include "arrayUtils.h"
#include "constants.h"

void fillArrayWithCount(const int minNumber, const int size, int outArray[]) {
    for (int i = minNumber; i < size; i++) {
        outArray[i] = i;
    }
}

int findElementIndex(const int element, const int referenceArray[]) {
    for (int i = 0; referenceArray[i] != NULL_NUMBER; i++) {
        if (referenceArray[i] == element) {
            return i;
        }
    }

    return -1;
}

void cutLeftPartArray(const int referenceArray[], const int cutNumberStart, int *outSize, int outArray[]) {
    int cutIndex = findElementIndex(cutNumberStart, referenceArray) + 1;
    copyArray(referenceArray, POSSIBLE_NUMBERS_ARRAY_SIZE, outArray);

    int i = 0;
    for (i; referenceArray[cutIndex] != NULL_NUMBER; cutIndex++, i++) {
        outArray[i] = referenceArray[cutIndex];
    }

    *outSize = i - 1;

    for (i; referenceArray[i] != NULL_NUMBER; i++) {
        outArray[i] = NULL_NUMBER;
    }

    return;
}

void cutRightPartArray(const int referenceArray[], const int cutNumberStart, int *outSize, int outArray[]) {
    int cutIndex = findElementIndex(cutNumberStart, referenceArray);
    copyArray(referenceArray, POSSIBLE_NUMBERS_ARRAY_SIZE, outArray);

    for (int i = cutIndex; referenceArray[i] != NULL_NUMBER; i++) {
        outArray[i] = NULL_NUMBER;
    }

    *outSize = cutIndex - 1;

    return;
}

void copyArray(const int referenceArray[], const int size, int outArray[]) {
    for (int i = 0; i < size; i++) {
        outArray[i] = referenceArray[i];
    }

    return;
}
