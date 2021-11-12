#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "mathUtils.h"

/*
 * Implementa a função para gerar números aletários dentro de um faixa
 */
int createRandomNumber(const int baseValue, const int maxValue) {
    return (rand() % (maxValue - baseValue + 1)) + baseValue;
}
