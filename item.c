#include "item.h"
#include "matematica.h"
#include "player.h"
#include "inimigo.h"
#include "log.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>

struct item{
    char representacaoMapa;
    int itemID;
    int posicaoX;
    int posicaoY;
    char nome[64];
    char descricao[1024];
    void (*usar)(struct item* self, void* afetado); // Isso aqui é um ponteiro para uma função que vai usar o item
                                                    // Tem como parâmetros o item, e um ponteiro pra quem vai ser afetado (inimigo ou player) 
};

struct celulaItem{
    Item* item;
    struct celulaItem* prox;
    struct celulaItem* ant;
};

struct listaItem{
    CelulaItem* inicio;
    CelulaItem* fim;
    int tamanho;
};

Item* criaItem(){
    int preSet = gerarNumeroAleatorio(1,3);
    Item* item = (Item*)malloc(sizeof(Item));
    if(item == NULL){
        logError("Erro na alocação de memoria na criação do item");
        exit(1);
    }

    switch(preSet){
        case 1:
            strcpy(item->nome, "Pocao de vida");
            item->representacaoMapa = 'O';
            item->usar = usarPocao;
            strcpy(item->descricao, "Pocao de vida: cura 50 de HP");
            break;
        case 2:
            strcpy(item->nome, "Bomba");
            item->representacaoMapa = 'O';
            item->usar = usarBomba;
            strcpy(item->descricao, "Bomba: inflinge 40 de dano ao inimigo");
            break;
        case 3:
            strcpy(item->nome, "Bomba de fumaca"); // esse item aqui a gente usa pra escapar dos bixos
            item->representacaoMapa = 'O';
            item->usar = usarBombaFumaca; // placeholder
            strcpy(item->descricao, "Bomba de fumaça: use este item para escapar do combate");
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
    return item->representacaoMapa;
}

char* getItemNome(Item* item){
    return item->nome;
}

int getQuantidadeItem(ListaItem* lista){
    return lista->tamanho;
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
    Inimigo* inimigo = (Inimigo*)afetado;
    setEnemyHpDamage(inimigo, 100000000);
    system("cls");
    logInfo("Você escapou do combate");
    Sleep(150);
}

//------------------------------------------- Funções de lista ---------------------------------------------------------//

ListaItem* criaListaItens(){
    ListaItem* l = (ListaItem*)malloc(sizeof(ListaItem));
    if (l == NULL){
        logError("Erro na alocação de memoria da lista de itens");
        exit(1);
    }
    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;
    return l;
}

void inserirItem(ListaItem* ListaItem, Item* item){
    CelulaItem *nova = malloc(sizeof(CelulaItem));
    if (nova == NULL) {
        logError("Erro na alocação de memoria da celula da lista de itens");
        exit(1);
    }
    nova->item = item;
    nova->prox = NULL; // pois será o novo fim

    if (ListaItem->fim == NULL) { // lista vazia
        ListaItem->inicio = nova;
        ListaItem->fim = nova;
        nova->ant = NULL;
    } else {
        nova->ant = ListaItem->fim;
        ListaItem->fim->prox = nova;
        ListaItem->fim = nova;
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

bool removerItem(ListaItem* lista, Item* alvo){

    if(lista == NULL || lista->inicio == NULL || alvo == NULL){
        logError("Lista de Items nao existe // Item nao existente");
        return false;
    }

    CelulaItem* atual = lista->inicio;

    while(atual != NULL){
        if(atual->item == alvo){
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

            destruirItem(atual->item);
            free(atual);
            lista->tamanho--;
            return true;
        }
        atual = atual->prox;
    }

    return false;
}


Item* buscarItemXY(ListaItem* lista, int x, int y){
    if(lista == NULL){
        logError("Lista de itens não existe"); 
        return NULL;
    }

    CelulaItem* atual = lista->inicio;
    while(atual != NULL){
        if(atual->item->posicaoX == x && atual->item->posicaoY == y){
            return atual->item;
        }
        atual = atual->prox;
    }
    return NULL;
}

void atualizarItemsNoMapa(ListaItem* lista, char mapa[15][15], bool debug){
    if(debug == false || lista == NULL) {
        logError("Lista de itens não existe // Debug já é falso");
        return;
    }

    CelulaItem* atual = lista->inicio;

    while(atual != NULL){
        Item* Item = atual->item;

            int x = Item->posicaoX;
            int y = Item->posicaoY;
            if(mapa[y][x] == ' '){
                mapa[y][x] = Item->representacaoMapa;
            }

        atual = atual->prox;
    }
}
void esconderItemsDoMapa(ListaItem* lista, char mapa[15][15]){
    if(lista == NULL) {
        logError("Lista de itens não existe");
        return;
    }

    CelulaItem* atual = lista->inicio;

    while(atual != NULL){
        Item* Item = atual->item;

        int x = Item->posicaoX;
        int y = Item->posicaoY;
        mapa[y][x] = ' ';

        atual = atual->prox;
    }
}

// Teoricamente falando, checar se existe algum item na posição xy é atribuição do jogo
// se sobrar tempo, colocar isso no game.c em vez de deixar no inimigo.c
bool checarItemXY(ListaItem* lista, int x, int y){
    if(lista == NULL){
        logError("Lista de itens não existe");
        return NULL;
    }

    CelulaItem* atual = lista->inicio;
    while(atual != NULL){
        if(atual->item->posicaoX == x && atual->item->posicaoY == y){
            return true;
        }
        atual = atual->prox;
    }
    return NULL;
}

Item* copiarItem(Item* original) {
    if (original == NULL){
        logError("Item não existe");
        return NULL;
    }

    Item* novo = (Item*)malloc(sizeof(Item));
    if (novo == NULL) {
        logError("Falha ao alocar memória para copia do item.");
        exit(1);
    }

    novo->representacaoMapa = original->representacaoMapa;
    novo->itemID = original->itemID;
    novo->posicaoX = original->posicaoX;
    novo->posicaoY = original->posicaoY;

    strncpy(novo->nome, original->nome, sizeof(novo->nome));
    strncpy(novo->descricao, original->descricao, sizeof(novo->descricao));

    novo->usar = original->usar;

    return novo;
}

Item* buscarItemPorIndice(ListaItem* lista, int indice) {
    if (lista == NULL) {
        logError("Lista de itens não existe");
        return NULL;
    }

    if (indice < 0 || indice >= lista->tamanho) {
        logError("Índice fora dos limites da lista de itens");
        return NULL;
    }

    CelulaItem* atual = lista->inicio;
    int contador = 0;

    while (atual != NULL && contador < indice) {
        atual = atual->prox;
        contador++;
    }

    if (atual != NULL) {
        return atual->item;
    } else {
        return NULL;
    }
}