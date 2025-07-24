#include "item.h"
#include "matematica.h"
#include "player.h"
#include "inimigo.h"
#include "log.h"
#include "ansi.h"
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
            strcpy(item->descricao, "Pocao de vida: Uma pocao rarissima de origem elfica. Use para curar 40 de HP");
            break;
        case 2:
            strcpy(item->nome, "Bomba");
            item->representacaoMapa = 'O';
            item->usar = usarBomba;
            strcpy(item->descricao, "Bomba: Uma bomba antiga esquecida por mineradores anoes de outrora. Use para inflingir 40 de dano ao inimigo");
            break;
        case 3:
            strcpy(item->nome, "Bomba de fumaca"); // esse item aqui a gente usa pra escapar dos bixos
            item->representacaoMapa = 'O';
            item->usar = usarBombaFumaca; // placeholder
            strcpy(item->descricao, "Bomba de fumaca: Os antigos ninjas usavam dispositivos como esse em suas batalhas. Use-a para escapar de uma batalha");
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
int getItemID(Item* item){
    return item->itemID;
}

char* getItemNome(Item* item){
    return item->nome;
}

int getQuantidadeItem(ListaItem* lista){
    return lista->tamanho;
}

char* getItemDescricao(Item* item){
    return item->descricao;
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
    Sleep(150);
}

void usarItem(Item* item, void* alvo){
    if(item != NULL && item->usar != NULL){
        item->usar(item, alvo);
    }
    else{
        logError("Erro no item, ele e nulo ou a funcao de utiliza-lo e nula");
    }
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

void imprimirArte(int itemID){
    switch(itemID){
        case 1:{
            char arteTemp[16][16] = {
                {' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' '},
                {' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' '},
                {' ', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' '},
                {' ', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', '#', '.', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', '#', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
            };

            for(int i = 0; i < 15; i++){
                for(int j = 0; j < 16; j++){
                    switch(arteTemp[i][j]){
                        case '.':
                            printf(FUNDO_VERMELHO_CLARO" "RESET"");
                            break;
                        case '#':
                            printf(FUNDO_BRANCO " " RESET "");
                            break;
                        default:
                            printf("%c", arteTemp[i][j]);
                            break;
                    }
                }
                printf("\n");
            }
            break;
        }
        case 2:{
            char arteTemp[16][16] = {
                {' ', ' ', ' ', ' ', ' ', '-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', '#', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', '#', '.', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', '#', '.', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' '},
                {' ', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' '},
                {' ', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' '},
                {' ', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', '#', '.', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', '#', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
            };
            for(int i = 0; i < 15; i++){
                for(int j = 0; j < 16; j++){
                    switch(arteTemp[i][j]){
                        case '.':
                            printf(FUNDO_PRETO_CLARO" "RESET"");
                            break;
                        case '#':
                            printf(FUNDO_PRETO_CLARO " " RESET "");
                            break;
                        case '*':
                            printf(FUNDO_BRANCO " " RESET"");
                            break;
                        case '-':
                            printf(FUNDO_AMARELO" " RESET "");
                            break; 
                        default:
                            printf("%c", arteTemp[i][j]);
                            break;
                    }
                }
                printf("\n");
            }
            break;
        }
        case 3:{
            char arteTemp[16][16] = {
                {' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', '#', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', '#', '.', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', '#', '.', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' '},
                {' ', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' '},
                {' ', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' '},
                {' ', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', '#', '.', '.', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', '#', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
            };
            for(int i = 0; i < 15; i++){
                for(int j = 0; j < 16; j++){
                    switch(arteTemp[i][j]){
                        case '.':
                            printf(FUNDO_BRANCO_CLARO" "RESET"");
                            break;
                        case '#':
                            printf(FUNDO_PRETO_CLARO " " RESET "");
                            break;
                        case '*':
                            printf(FUNDO_BRANCO " " RESET"");
                            break;
                        default:
                            printf("%c", arteTemp[i][j]);
                            break;
                    }
                }
                printf("\n");
            }
            break;
        }
    }
}