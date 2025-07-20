#include "trap.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "log.h"

struct trap{
    char representacao;
    int trapID;
    int dano;
    int posicaoX;
    int posicaoY;
    bool isActivated;
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


Trap* criaTrap(){
    Trap* armadilha = (Trap*)malloc(sizeof(Trap));
    if(armadilha == NULL){
        logError("na alocação de memoria para criar uma armadilha");
        exit(1);
    }
    armadilha->dano = 15;
    armadilha->representacao = 'T';
    armadilha->isActivated = false;
    return armadilha;
}

void destruirTrap(Trap* armadilha){
    if(armadilha == NULL){
        return;
    }
    free(armadilha);
}



// -------------------------------------------------- Gets e setters ----------------------------------------------------- //

void setTrapX(Trap* armadilha, int posicao){
    armadilha->posicaoX = posicao;
}

void setTrapY(Trap* armadilha, int posicao){
    armadilha->posicaoY = posicao;
}

int getTrapX(Trap* armadilha){
    return armadilha->posicaoX;    
}

int getTrapY(Trap* armadilha){
    return armadilha->posicaoY;
}

bool getTrapState(Trap* armadilha){
    return armadilha->isActivated;
}

char getTrapRepresentacao(Trap* armadilha){
    return armadilha->representacao;
}

int getTrapDamage(Trap* armadilha){
    return armadilha->dano;
}

// ---------------------------------- Funcoes para lista de traps ------------------------------------------------------------//


ListaTrap* criaListaTrap(){
    ListaTrap* l = (ListaTrap*)malloc(sizeof(ListaTrap));
    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;
    return l;
}

void destruirListaTrap(ListaTrap* lista){
    if(lista == NULL){
        return;
    }

    CelulaTrap* atual = lista->inicio;
    while(atual != NULL){
        CelulaTrap* proximo = atual->prox;
        destruirTrap(atual->trap);
        free(atual);
        atual = proximo;
    }
    free(lista);
}

void inserirTrap(ListaTrap* lista, Trap* armadilha){
    CelulaTrap *nova = (CelulaTrap*)malloc(sizeof(CelulaTrap));
    if(nova == NULL){
        logError("na alocação de memoria para inserir trap na lista");
        exit(1);
    }

    nova->trap = armadilha;

    if (lista->inicio == NULL){ // lista vazia
        lista->inicio = nova;
        lista->fim = nova;
        nova->prox = NULL;
        nova->ant = NULL;
    }
    else{
        nova->prox = lista->inicio;
        nova->ant = NULL;
        lista->inicio->ant = nova;
        lista->inicio = nova;
    }
    lista->tamanho++;
}