#include "player.h"
#include "inimigo.h"
#include <stdbool.h>
#include "trap.h"
#include "item.h"

typedef struct mapa Mapa;

Mapa*           criaMapa                            ();
void            destruirMapa                        (Mapa*);
void            printDungeon                        (Mapa*);
void            setarInimigos                       (Mapa*);
void            setarTraps                          (Mapa*);
void            setarItens                          (Mapa*);
Player*         getPlayer                           (Mapa*);
char            getRepresentacaoPosicaoMapa         (Mapa*, int, int);
void            atualizarMapa                       (Mapa* , int, int, int, int);

//--------------------------------------- FUNÇÕES DE DEBUG ------------------------------------//
bool            getDebugState                       (Mapa*);
void            setDebugState                       (Mapa*, bool);
void            setarInimigosDebug                  (Mapa*, bool );
bool            checarExisteInimigoPosicaoMapa      (Mapa*);
bool            checarExisteTrapPosicaoMapa         (Mapa*);
bool            checarExisteItemPosicaoMapa         (Mapa*);

//-------------------------------------- FUNÇÕES PARA PEGAR AS LISTA DE ENTIDADES DA DUNGEON ----------------------------------------//

ListaTrap*      getListaTrap                        (Mapa*);
ListaItem*      getListaItem                        (Mapa*);
ListaInimigo*   getListaInimigos                    (Mapa*);