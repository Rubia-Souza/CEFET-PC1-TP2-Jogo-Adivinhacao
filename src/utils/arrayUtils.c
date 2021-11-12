#include "arrayUtils.h"
#include "constants.h"

void fillArrayWithCount(const int minNumber, const int size, int outArray[]) {
    for (int i = minNumber; i < size; i++) {
        outArray[i] = i;
    }
}

int findElementIndex(const int element, const int referenceArray[]) {
    for (int i = 0; referenceArray[i] != NULL_NUMBER; i++) { // Procura no array até encontrar a ultima posição que terá o NULL_NUMBER obrigatoriamente
        if (referenceArray[i] == element) {
            return i;
        }
    }

    return -1;
}

void cutLeftPartArray(const int referenceArray[], const int cutNumberStart, int *outSize, int outArray[]) {
    int cutIndex = findElementIndex(cutNumberStart, referenceArray) + 1;
    // Copia o array para evitar alguma consequência não desejada na referência
    copyArray(referenceArray, POSSIBLE_NUMBERS_ARRAY_SIZE, outArray);

    // Inicialmente, move os valores após o cutIndex para o começo do array (i)
    int i = 0;
    for (i; referenceArray[cutIndex] != NULL_NUMBER; cutIndex++, i++) {
        outArray[i] = referenceArray[cutIndex];
    }

    // Atauliza o valor do tamanho do array, desconsiderando o lado removido
    *outSize = i - 1;

    // Por fim, preenche o resto do array com NULL_NUMBER
    for (i; referenceArray[i] != NULL_NUMBER; i++) {
        outArray[i] = NULL_NUMBER;
    }

    return;
}

void cutRightPartArray(const int referenceArray[], const int cutNumberStart, int *outSize, int outArray[]) {
    int cutIndex = findElementIndex(cutNumberStart, referenceArray);
    // Copia o array para evitar alguma consequência não esperada na referência
    copyArray(referenceArray, POSSIBLE_NUMBERS_ARRAY_SIZE, outArray);

    // A partir do cutIndex, a função apaga todos números a direita dele
    for (int i = cutIndex; referenceArray[i] != NULL_NUMBER; i++) {
        outArray[i] = NULL_NUMBER;
    }

    // Por fim, atualiza o tamanho do array
    *outSize = cutIndex - 1;

    return;
}

void copyArray(const int referenceArray[], const int size, int outArray[]) {
    for (int i = 0; i < size; i++) {
        outArray[i] = referenceArray[i];
    }

    return;
}
