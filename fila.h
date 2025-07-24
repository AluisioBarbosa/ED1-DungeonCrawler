#include <stdbool.h>

typedef struct fila Fila;

bool        isFilaEmpty             (Fila*);
Fila*       criarFila           ();
void        enfileirar          (Fila*, const char*);
char*       desenfileirar       (Fila*);
int         filaSize            (Fila*);
void        imprimirFila        (Fila*);
Fila*       inverterFila        (Fila *);
void destruirFila(Fila*);
void esvaziarFila(Fila*);
