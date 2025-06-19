#include <stdbool.h>

typedef struct fila Fila;

bool        isEmpty             (Fila*);
Fila*       criarFila           ();
void        enfileirar          (Fila*, int);
int         desenfileirar       (Fila*);
int         filaSize            (Fila*);
void        imprimirFila        (Fila*);
Fila*       inverterFila        (Fila *);
