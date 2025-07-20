#include "inimigo.h"
#include "matematica.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"

struct inimigo{
    int inimigoID;
    char representacaoMapa;
    char* nome;
    int HP;
    int weaponDamage;
    int armor;
    bool isDead;
    int posicaoX;
    int posicaoY;
};


typedef struct celInimigo{
    Inimigo* inimigo;
    struct celInimigo* prox;
    struct celInimigo* ant;
} CelulaInimigo;

struct listaInimigo{
    CelulaInimigo* inicio;
    CelulaInimigo* fim;
    int tamanho;
};

Inimigo* criarInimigo(){
    int preSet = gerarNumeroAleatorio(1,3);
    Inimigo* inimigo = (Inimigo*)malloc(sizeof(Inimigo));
    if(inimigo == NULL){
        logError("na alocação de memoria na criação do inimigo");
        exit(1);
    }

    switch(preSet){
        case 1:
            inimigo->representacaoMapa = 'Z';
            inimigo->nome = (char*)malloc(6 * sizeof(char)); // aloca espaço pra 6 letras
            strcpy(inimigo->nome, "Zumbi");
            inimigo->HP = 70;
            inimigo->weaponDamage = 7;
            inimigo->armor = 5;
            break;
        case 2:
            inimigo->representacaoMapa = 'E';
            inimigo->nome = (char*)malloc(10 * sizeof(char)); // aloca espaço pra 10 letras
            strcpy(inimigo->nome, "Esqueleto");
            inimigo->HP = 50;
            inimigo->weaponDamage = 10;
            inimigo->armor = 9;
            break;
        case 3:
            inimigo->representacaoMapa = 'H';
            inimigo->nome = (char*)malloc(7 * sizeof(char)); // aloca espaço pra 7 letras
            strcpy(inimigo->nome, "Humano");
            inimigo->HP = 90;
            inimigo->weaponDamage = 5;
            inimigo->armor = 15;
            break;      
    }
    inimigo->inimigoID = preSet;
    inimigo->isDead = false;
    return inimigo;
}

void destruirInimigo(Inimigo* inimigo){
    if(inimigo == NULL){ // Não tem nada a destruir pq ja ta setado nulo
        return;
    }
    if(inimigo->nome != NULL){
        free(inimigo->nome);
    }
    free(inimigo);
}

bool isEnemyDead(Inimigo* inimigo){
    return inimigo->isDead;
}
// ----------------------------------------------- Gets e Setters -----------------------------------------------------------//


void setEnemyHpDamage(Inimigo* inimigo, int damage){
    inimigo->HP -= calculaDano(damage, inimigo->armor);
    if(inimigo->HP <= 0){
        inimigo->HP = 0;
        inimigo->isDead = true;
    }
}

void setEnemyX(Inimigo* inimigo, int posicao){
    inimigo->posicaoX = posicao;
}
void setEnemyY(Inimigo* inimigo, int posicao){
    inimigo->posicaoY = posicao;
}
int getEnemyX(Inimigo* inimigo){
    return inimigo->posicaoX;
}
int getEnemyY(Inimigo* inimigo){
    return inimigo->posicaoY;
}
int getEnemyHP(Inimigo* inimigo){
    return inimigo->HP;
}
int getEnemyWeaponDamage(Inimigo* inimigo){
    return inimigo->weaponDamage;
}
char getInimigoRepresentacao(Inimigo* inimigo){
    return inimigo->representacaoMapa;
}


// ----------------------------------------------- Funções de lista -----------------------------------------------------------//

ListaInimigo* criaListaInimigo(){
    ListaInimigo* l = (ListaInimigo*)malloc(sizeof(ListaInimigo));
    if(l == NULL){
        logError("na alocação de memoria na criação do inimigo");
        exit(1);
    }
    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;
    return l;
}


void inserirInimigo(ListaInimigo* listaInimigo, Inimigo* inimigo){
    CelulaInimigo *nova = malloc(sizeof(CelulaInimigo));
    nova->inimigo = inimigo;

    if (listaInimigo->inicio == NULL){ // lista vazia
        listaInimigo->inicio = nova;
        listaInimigo->fim = nova;
        nova->prox = NULL;
        nova->ant = NULL;
    }
    else{
        nova->prox = listaInimigo->inicio;
        nova->ant = NULL;
        listaInimigo->inicio->ant = nova;
        listaInimigo->inicio = nova;
    }
    listaInimigo->tamanho++;
}

void destruirListaInimigo(ListaInimigo* lista){
    if(lista == NULL){
        return;
    }

    CelulaInimigo* atual = lista->inicio;
    while(atual != NULL){
        CelulaInimigo* proximo = atual->prox;
        destruirInimigo(atual->inimigo);
        free(atual);
        atual = proximo;
    }
    free(lista);
}






// ----------------------------------------------- Funções para debugar -----------------------------------------------------------//

void printInimigo(Inimigo* inimigo){
    printf("ID do inimigo: %d\n", inimigo->inimigoID);
    printf("Representacao do inimigo: %c\n", inimigo->representacaoMapa);
    printf("Nome do inimigo: %s\n", inimigo->nome);
    printf("HP do inimigo: %d\n", inimigo->HP);
    printf("Dano do inimigo: %d\n", inimigo->weaponDamage);
    printf("Armadura do inimigo: %d\n\n", inimigo->armor);
}