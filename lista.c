#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct cel{
    int valor;
    struct cel* prox;
    struct cel* ant;
} Celula;

struct lista{
    Celula* inicio;
    Celula* fim;
    int tamanho;
};

Lista* criaLista(){
    Lista* l = (Lista *)malloc(sizeof(Lista));
    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;
    return l;
}

void inserirInicio(Lista* lista, int v){
    Celula *nova = malloc(sizeof(Celula));
    nova->valor = v;

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

int removerInicio(Lista* lista){
    Celula* cel = lista->inicio;
    int v = cel->valor;

    lista->inicio = lista->inicio->prox;

    if(lista->inicio == NULL) // lista ficará vazia
        lista->fim = NULL;
    else
        lista->inicio->ant = NULL;
    
    free(cel);
    return v;
}

void imprimeLista(Lista* lista){
    Celula* aux = lista->inicio;

    while(aux != NULL){
        printf("%d -> ", aux->valor);
        aux = aux->prox;
    }
    printf("NULL\n");
}

void inserirFim(Lista* lista, int v) {
    Celula* nova = malloc(sizeof(Celula));
    nova->valor = v;
    nova->prox = NULL;

    if (lista->inicio == NULL) { // lista vazia
        nova->ant = NULL;
        lista->inicio = nova;
        lista->fim = nova;
    }
    else{
        nova->ant = lista->fim;
        lista->fim->prox = nova;
        lista->fim = nova;
    }
    lista->tamanho++;
}

void inserirMeio(Lista* lista, int v, int posicao) {
    if (posicao < 0 || posicao > lista->tamanho){
        return;
    }

    if (posicao == 0) {
        inserirInicio(lista, v);
        return;
    }

    if (posicao == lista->tamanho) {
        inserirFim(lista, v);
        return;
    }

    Celula* nova = malloc(sizeof(Celula));
    nova->valor = v;

    Celula* atual = lista->inicio;
    for (int i = 0; i < posicao; i++)
        atual = atual->prox;

    nova->prox = atual;
    nova->ant = atual->ant;
    atual->ant->prox = nova;
    atual->ant = nova;

    lista->tamanho++;
}

int removerFim(Lista* lista) {
    int v;
    if (lista->inicio == NULL){ 
        return -1;
    }
    Celula* cel = lista->fim;

    lista->fim = cel->ant;
    if (lista->fim == NULL){
        lista->inicio = NULL;
    }
    else{
        lista->fim->prox = NULL;
    }
    v = cel->valor;

    free(cel);
    lista->tamanho--;
    return v;
}

int removerMeio(Lista* lista, int posicao) {
    int v;
    if (posicao < 0 || posicao >= lista->tamanho){ 
        return -1;
    }

    if (posicao == 0) {
        v = removerInicio(lista);
        return v;
    }

    if (posicao == lista->tamanho - 1) {
        v = removerFim(lista);
        return v;
    }

    Celula* atual = lista->inicio;
    for (int i = 0; i < posicao; i++){
        atual = atual->prox;
    }
    atual->ant->prox = atual->prox;
    atual->prox->ant = atual->ant;

    v = atual->valor;
    free(atual);
    lista->tamanho--;
    return v;
}

void destruirLista(Lista* lista) {
    if (lista == NULL){
        return;
    }
    Celula* atual = lista->inicio;
    while (atual != NULL) {
        Celula* prox = atual->prox;
        free(atual);
        atual = prox;
    }

    free(lista);
}

int getTamanhoLista(Lista* lista){
    return lista->tamanho;
}