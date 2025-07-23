#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "log.h"

typedef struct cel{
    int valor;
    struct cel* proximo;
} Celula;

struct fila
{
    Celula* inicio;
    Celula* fim;
    int tamanho;
};


Fila* criarFila(){
    Fila *f = (Fila*)malloc(sizeof(Fila));
    if(f == NULL){
        logError("Erro na hora de alocar memoria para a fila");
        exit(1);
    }
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
    return f;
}

bool isEmpty(Fila *f){
    if(f->fim == NULL){
        return true;
    }
    return false;
}

void imprimirFila(Fila *f){
    Celula *cel = f->inicio;
    while(cel != NULL){
        printf("%i\n", cel->valor);
        cel = cel->proximo;
    }
}

void enfileirar(Fila *f, int valor){
    Celula *cel = (Celula*)malloc(sizeof(Celula));
    if(cel == NULL){
        logError("Erro na alocação de memoria para celula da fila");
        exit(1);
    }
    cel->valor = valor;
    cel->proximo = NULL;

    if(f->fim != NULL){
        f->fim->proximo = cel;
    }
    else{
        f->inicio = cel;
    }

    f->fim = cel;
    f->tamanho++;

}

int desenfileirar(Fila *f){
    if(f->inicio == NULL){
        printf("A fila esta vazia\n");
        return -1;
    }

    Celula *cel = f->inicio;
    int valor = cel->valor;
    f->inicio = f->inicio->proximo;
    if(f->inicio == NULL){
        f->fim = NULL;
    }
    free(cel);
    f->tamanho--;
    return valor;
}

int filaSize(Fila *f){
    int size = f->tamanho;
    return size;
}