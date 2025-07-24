#include "trap.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "log.h"

struct trap{
    char representacaoMapa;
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
        logError("Erro na alocação de memoria para criar uma armadilha");
        exit(1);
    }
    armadilha->dano = 15;
    armadilha->representacaoMapa = 'T';
    armadilha->isActivated = false;
    logToFile("Armadilha criada com sucesso");
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
    return armadilha->representacaoMapa;
}

int getTrapDamage(Trap* armadilha){
    return armadilha->dano;
}
int getTrapQuantidade(ListaTrap* lista){
    return lista->tamanho;
}

// ---------------------------------- Funcoes para lista de traps ------------------------------------------------------------//


ListaTrap* criaListaTrap(){
    ListaTrap* l = (ListaTrap*)malloc(sizeof(ListaTrap));
    if(l == NULL){
        logError("Falha na alocação de memoria para a lista de traps");
        exit(1);
    }
    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;
    return l;
}

void destruirListaTrap(ListaTrap* lista){
    if(lista == NULL){
        logWarn("Lista de traps não existe");
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
bool removerTrap(ListaTrap* lista, Trap* alvo){

    if(lista == NULL || lista->inicio == NULL || alvo == NULL){
        logError("Lista de traps não existe // Trap nao existente");
        return false;
    }

    CelulaTrap* atual = lista->inicio;

    while(atual != NULL){
        if(atual->trap == alvo){
            if(atual->ant != NULL){
                atual->ant->prox = atual->prox;
            } 
            else{
                lista->inicio = atual->prox;
            }

            if(atual->prox != NULL){
                atual->prox->ant = atual->ant;
            }
            else{
                lista->fim = atual->ant;
            }

            destruirTrap(atual->trap);
            free(atual);
            lista->tamanho--;
            return true;
        }
        atual = atual->prox;
    }

    return false;
}


Trap* buscarTrapXY(ListaTrap* lista, int x, int y){
    if(lista == NULL){
        logError("Lista de traps não existe"); 
        return NULL;
    }

    CelulaTrap* atual = lista->inicio;
    while(atual != NULL){
        if(atual->trap->posicaoX == x && atual->trap->posicaoY == y){
            return atual->trap;
        }
        atual = atual->prox;
    }
    return NULL;
}

void atualizarTrapsNoMapa(ListaTrap* lista, char mapa[15][15], bool debug){
    if(debug == false || lista == NULL) {
        logError("Lista de traps não existe // debug já esta setado false");
        return;
    }

    CelulaTrap* atual = lista->inicio;

    while(atual != NULL){
        Trap* trap = atual->trap;

        if(trap->isActivated == false){
            int x = trap->posicaoX;
            int y = trap->posicaoY;

            if(mapa[y][x] == ' '){
                mapa[y][x] = trap->representacaoMapa;
            }
        }

        atual = atual->prox;
    }
}
void esconderTrapsDoMapa(ListaTrap* lista, char mapa[15][15]){
    if(lista == NULL) {
        logError("Lista de traps não existe");
        return;
    }

    CelulaTrap* atual = lista->inicio;

    while(atual != NULL){
        Trap* trap = atual->trap;

        if(trap->isActivated == false){
            int x = trap->posicaoX;
            int y = trap->posicaoY;

            mapa[y][x] = ' ';
        }

        atual = atual->prox;
    }
}

// Teoricamente falando, checar se existe alguma trap na posição xy é atribuição do jogo
// se sobrar tempo, colocar isso no game.c em vez de deixar no inimigo.c
bool checarTrapXY(ListaTrap* lista, int x, int y){
    if(lista == NULL){
        logError("Lista de traps não existe");
        return NULL;
    }

    CelulaTrap* atual = lista->inicio;
    while(atual != NULL){
        if(atual->trap->posicaoX == x && atual->trap->posicaoY == y){
            return true;
        }
        atual = atual->prox;
    }
    return NULL;
}