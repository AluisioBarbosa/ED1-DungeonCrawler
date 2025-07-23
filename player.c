#include "player.h"
#include "inventario.h"
#include "matematica.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "log.h"

struct player{
    char representacaoMapa;
    char nome[32];
    int playerID;
    int HP;
    int maxHP;
    int weaponDamage;
    int armor;
    Inventario* inventario;
    bool isDead;
    int posicaoX;
    int posicaoY;
};


Player* criarPlayer(){
    Player *player = (Player*)malloc(sizeof(Player));
    if(player == NULL){
        logError("Erro na alocação de memoria do personagem");
        exit(1);
    }

    int preSet = gerarNumeroAleatorio(1, 5);

    switch(preSet){

        case 1:
            strcpy(player->nome, "Seu Carlinhos");
            player->HP = 110;
            player->weaponDamage = 15;
            player->armor = 10;
            break;
        case 2:
            strcpy(player->nome, "Jorge");
            player->HP = 80;
            player->weaponDamage = 25;
            player->armor = 30;
            break;
        case 3:
            strcpy(player->nome, "Tiao");
            player->HP = 150;
            player->weaponDamage = 10;
            player->armor = 5;
            break;
        case 4:
            strcpy(player->nome, "Tim Maia");
            player->HP = 100;
            player->weaponDamage = 20;
            player->armor = 15;
            break;
        case 5:
            strcpy(player->nome, "Jodisvaldo");
            player->HP = 120;
            player->weaponDamage = 10;
            player->armor = 10;
            break;
    }
    player->playerID = preSet;
    player->inventario = criarInventario();
    player->isDead = false;
    player->maxHP = player->HP;
    player->representacaoMapa = 'P';
    player->posicaoX = 1;
    player->posicaoY = 1;
    return player;
}

void destruirPlayer(Player* player){ // essa função só sera utilizada para a função de GameOver ou de jogar de novo
    if(player == NULL){
        return;
    }

    if (player->inventario != NULL){
        destruirInventario(player->inventario);
    }

    free(player);
    logToFile("Player destruido com sucesso");
}

void healPlayer(Player* player, int cura){
    player->HP += cura;
    if(player->HP > player->maxHP){
        player->HP = player->maxHP;
    }
}

bool isPlayerDead(Player* player){
    return player->isDead;
}

//------------------------------------------- Gets e Setters ---------------------------------------------------------//
void setPlayerX(Player* player, int posicao){
    player->posicaoX = posicao;
}
void setPlayerY(Player* player, int posicao){
    player->posicaoY = posicao;
}
void setPlayerHpDamage(Player* player, int damage){
    player->HP -= calculaDano(damage, player->armor); // aqui faz o HP do player menos o dano do inimigo pós mitigação da armadura

    if(player->HP <= 0){
        player->HP = 0; // Só pra evitar eventuais baguncinhas que HP negativo pode causar
        player->isDead = true;
    }
}

int getPlayerWeaponDamage(Player* player){
    return player->weaponDamage;
}
int getPlayerX(Player* player){
    return player->posicaoX;
}
int getPlayerY(Player* player){
    return player->posicaoY;
}
char getPlayerRepresentacao(Player* player){
    return player->representacaoMapa;
}
int getPlayerHP(Player* player){
    return player->HP;
}
int getPlayerMaxHP(Player* player){
    return player->maxHP;
}

Inventario* getInventario(Player* player){
    return player->inventario;
}

char* getPlayerName(Player* player){
    return player->nome;
}

//------------------------------------------- Funções de debug ---------------------------------------------------------//

void printPlayer(Player* player){
    printf("ID do player: %d\n", player->playerID);
    printf("HP do player: %d\n", player->HP);
    printf("Dano do player: %d\n", player->weaponDamage);
    printf("Armadura do player: %d\n\n", player->armor);
}


