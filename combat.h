#include <stdbool.h>
#include "player.h"
#include "inimigo.h"
#include "fila.h"

bool combate(Inimigo* , Player*, int, Fila*);
void exibirHUD(Inimigo*, Player*);
void trocaTurno(bool*);
void turnoInimigo(Inimigo*, Player*, bool*, Fila*);