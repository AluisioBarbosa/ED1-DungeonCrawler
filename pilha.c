#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct cel{
    char valor;
    struct cel* proximo;
} Celula;

struct pilha
{
    Celula* topo;
    int tamanho;
};

Pilha* criaPilha(){
    Pilha* p = (Pilha *)malloc(sizeof(Pilha));
    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

char push(char v, Pilha* pilha){
    Celula* nova = (Celula*)malloc(sizeof(Celula));
    nova->proximo = pilha->topo;
    nova->valor = v;

    pilha->topo = nova;
    pilha->tamanho += 1;

    return 0;
}

char pop(Pilha* pilha) {
 	if (pilha->tamanho < 1)
		return 0; // vazia

  	char v = pilha->topo->valor;
  	Celula* cel_topo = pilha->topo;

	pilha->topo = cel_topo->proximo;
  	pilha->tamanho -= 1; // um a menos;
  	free(cel_topo); // adeus celula
  	return v;
}


void imprimePilha(Pilha* pilha){
    Celula* nova = pilha->topo;

    while(nova != NULL){
        printf("%d \n", nova->valor);
        nova = nova->proximo;
    }
    
}

int pilhaSize(Pilha* pilha){
    int size = pilha->tamanho;
    return size;
}