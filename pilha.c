#include "pilha.h"
#include "log.h"
#include <stdbool.h>
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
    if(p == NULL){
        logError("Falha na alocação de memoria para a pilha");
        exit(1);
    }
    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

char push(char v, Pilha* pilha){
    Celula* nova = (Celula*)malloc(sizeof(Celula));
    if(nova == NULL){
        logError("Falha na alocação de memoria para celula da pilha");
        exit(1);
    }
    nova->proximo = pilha->topo;
    nova->valor = v;

    pilha->topo = nova;
    pilha->tamanho += 1;

    return 0;
}

char pop(Pilha* pilha) {
 	if (pilha->tamanho < 1){
		return 0;
    }
  	char v = pilha->topo->valor;
  	Celula* cel_topo = pilha->topo;

	pilha->topo = cel_topo->proximo;
  	pilha->tamanho -= 1;
  	free(cel_topo);
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
    return pilha->tamanho;
}

bool isEmpty(Pilha* pilha){
    if(pilha->topo == NULL){
        return true;
    }
    
    return false;
}

void destruirPilha(Pilha* pilha) {
    if (pilha == NULL){
         return;
    }
    while (isEmpty(pilha) == false) {
        pop(pilha);
    }

    free(pilha);
}