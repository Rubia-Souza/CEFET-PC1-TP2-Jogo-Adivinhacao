/*
 * Cria a pasta e o arquivo de save do jogo
 */
void createSave();

/*
 * Salva a pontuação do jogoador e do pc sobrescrevendo os valores anteriores
 */
void saveScore(const int playerScore, const int iaScore);

/*
 * Carrega as pontuações presentes no arquivo
 * Caso o arquivo não exista ou esteja vazio ele mantem os valores inalterados
 */
void loadScore(int *playerScore, int *iaScore);
