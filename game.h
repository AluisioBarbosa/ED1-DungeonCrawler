#include <stdbool.h>

typedef struct jogo Jogo;


Jogo* criarJogo();
void update(Jogo*);
bool getEndGame(Jogo*);
void destruirJogo(Jogo*);