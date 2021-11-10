#include "utils.h"

int createRandomNumber(const int baseValue, const int maxValue) {
    return (rand() % (maxValue - baseValue + 1)) + baseValue;
}
