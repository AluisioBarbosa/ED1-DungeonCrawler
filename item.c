#include "item.h"
#include <stdlib.h>
#include <stdio.h>

struct item{
    char representacao;
    int itemID;
    int posicaoX;
    int posicaoY;
    char nome[64];
    void (*usar)(struct item* self, void* afetado); // Isso aqui é um ponteiro para uma função que vai usar o item
                                                    // Tem como parâmetros o item, e um ponteiro pra quem vai ser afetado (inimigo ou player) 
};

typedef struct celItem{
    Item* item;
    struct celItem* prox;
    struct celItem* ant;
} CelulaItem;

struct listaItem{
    CelulaItem* inicio;
    CelulaItem* fim;
    int tamanho;
};


ListaItem* criaListaItens(){
    ListaItem* l = (ListaItem*)malloc(sizeof(ListaItem));
    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;
    return l;
}

void destruirListaItem(ListaItem* lista) {
    if (lista == NULL){
        return;
    }

    CelulaItem* atual = lista->inicio;

    while (atual != NULL) {
        CelulaItem* prox = atual->prox;
        if(atual->item != NULL){
            free(atual->item);
        }
        
        free(atual);
        atual = prox;
    }
    free(lista);
}
