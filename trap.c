#include "trap.h"


struct trap{
    char representacao;
    int itemID;
    int dano;
    int posicaoX;
    int posicaoY;
};

typedef struct celTrap{
    Trap* trap;
    struct celTrap* prox;
    struct celTrap* ant;
} CelulaTrap;

struct listaTrap{
    CelulaTrap* inicio;
    CelulaTrap* fim;
    int tamanho;
};

