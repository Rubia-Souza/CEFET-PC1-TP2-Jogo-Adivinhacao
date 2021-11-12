/*
 * Preenche um array com números incrementados de 1 a 1 a partir do mínimo
 */
void fillArrayWithCount(const int minNumber, const int size, int outArray[]);

/*
 * Encontra o index do primeiro elemento passado no array
 * Caso ele não esteja presente, a função retorna -1
 */
int findElementIndex(const int element, const int referenceArray[]);

/*
 * Apaga os valores do lado esquerdo do array a partir de um elemento
 * Ela move os valores a direita da parte a ser removida para o inicio
 * Então, apaga todo o resto, mantendo apenas os números após o index do cutNumberStart
 * Obs.: Apagar um número é defini-lo como NULL_NUMBER
 */
void cutLeftPartArray(const int referenceArray[], const int cutNumberStart, int *outSize, int outArray[]);

/*
 * Apaga todos os valores a direita do index cutNumberStart, mantendo apenas os da esquerda
 * Obs.: Apagar um número é defini-lo como NULL_NUMBER
 */
void cutRightPartArray(const int referenceArray[], const int cutNumberStart, int *outSize, int outArray[]);

/*
 * Copia todos os valores do array de referencia para o array alvo
 */
void copyArray(const int referenceArray[], const int size, int targetArray[]);
