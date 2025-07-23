#include <stdbool.h>
#include "mapa.h"

typedef struct jogo Jogo;


Jogo* criarJogo();
void update(Jogo*);
bool getEndGame(Jogo*);
void destruirJogo(Jogo*);
void changeDebugState(Jogo*);
Mapa* getGameDungeon(Jogo*);