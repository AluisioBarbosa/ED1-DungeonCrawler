#include <stdbool.h>
typedef struct pilha Pilha;

Pilha*      criaPilha           ();
char        push                (char, Pilha*);
char        pop                 (Pilha*);
void        imprimePilha        (Pilha*);
int         pilhaSize           (Pilha*);
bool        isEmpty             (Pilha*);
void        destruirPilha       (Pilha*);