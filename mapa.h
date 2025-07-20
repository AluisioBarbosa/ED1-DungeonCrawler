#include "player.h"
typedef struct mapa Mapa;

Mapa*           criaMapa            ();
void            destruirMapa        (Mapa*);
void            printDungeon        (Mapa*);
void            setarInimigos       (Mapa*);
void            setarTraps          (Mapa*);
void            setarItens          (Mapa*);
Player*         getPlayer           (Mapa*);
char            getRepresentacaoPosicaoMapa (Mapa*, int, int);
void atualizarMapa(Mapa* , int, int, int, int);

bool getDebugState(Mapa*);

void setDebugState(Mapa*, bool);