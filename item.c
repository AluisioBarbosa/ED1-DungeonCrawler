#include "item.h"
#include "matematica.h"
#include "player.h"
#include "inimigo.h"
#include <stdlib.h>
#include <string.h>
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

Item* criaItem(){
    int preSet = gerarNumeroAleatorio(1,3);
    Item* item = (Item*)malloc(sizeof(Item));
    if(item == NULL){
        printf("Falha na alocação de memoria na criação do item\n");
        exit(1);
    }

    switch(preSet){
        case 1:
            strcpy(item->nome, "Poção de vida");
            item->representacao = 'O';
            item->usar = usarPocao;
            break;
        case 2:
            strcpy(item->nome, "Bomba");
            item->representacao = 'O';
            item->usar = usarBomba;
            break;
        case 3:
            strcpy(item->nome, "Bomba de fumaca"); // esse item aqui a gente usa pra escapar dos bixos
            item->representacao = 'O';
            item->usar = usarPocao; // placeholder
            break;      
    }
    item->itemID = preSet;
    return item;
}

void destruirItem(Item* item){
    if(item == NULL){
        return;
    }
    free(item);
}

//------------------------------------------- Gets e Setters ---------------------------------------------------------//
void setItemX(Item* item, int posicao){
    item->posicaoX = posicao;
}
void setItemY(Item* item, int posicao){
    item->posicaoY = posicao;
}
int getItemX(Item* item){
    return item->posicaoX;
}
int getItemY(Item* item){
    return item->posicaoY;
}
char getItemRepresentacao(Item* item){
    return item->representacao;
}

//------------------------------------------- Funções usar do item (ponteiro) ---------------------------------------------------------//

void usarPocao(Item* pocao, void* afetado){
    Player* player = (Player*)afetado;
    healPlayer(player, 50);
}

void usarBomba(Item* bomba, void* afetado){
    Inimigo* inimigo = (Inimigo*)afetado;
    setEnemyHpDamage(inimigo, 40);
}

void usarBombaFumaca(Item* bombaF, void* afetado){
    // imeplentação da bomba de fumaça (farei depois);
}

//------------------------------------------- Funções de lista ---------------------------------------------------------//

ListaItem* criaListaItens(){
    ListaItem* l = (ListaItem*)malloc(sizeof(ListaItem));
    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;
    return l;
}

void inserirItem(ListaItem* ListaItem, Item* item){
    CelulaItem *nova = malloc(sizeof(CelulaItem));
    nova->item = item;

    if (ListaItem->inicio == NULL){ // lista vazia
        ListaItem->inicio = nova;
        ListaItem->fim = nova;
        nova->prox = NULL;
        nova->ant = NULL;
    }
    else{
        nova->prox = ListaItem->inicio;
        nova->ant = NULL;
        ListaItem->inicio->ant = nova;
        ListaItem->inicio = nova;
    }
    ListaItem->tamanho++;
}

void destruirListaItem(ListaItem* lista) {
    if (lista == NULL){
        return;
    }

    CelulaItem* atual = lista->inicio;

    while (atual != NULL) {
        CelulaItem* prox = atual->prox;
        destruirItem(atual->item);
        free(atual);
        atual = prox;
    }
    free(lista);
}
