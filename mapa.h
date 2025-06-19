typedef struct mapa Mapa;

Mapa*           criaMapa            ();
void            destruirMapa        (Mapa*);
void            printDungeon        (Mapa*);
void            setarInimigos       (Mapa*);
void            setarTraps          (Mapa*);
void            setarItens          (Mapa*);