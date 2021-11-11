#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "mathUtils.h"

int createRandomNumber(const int baseValue, const int maxValue) {
    return (rand() % (maxValue - baseValue + 1)) + baseValue;
}
