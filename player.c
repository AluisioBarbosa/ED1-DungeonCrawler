#include "player.h"
#include "inventario.h"
#include "matematica.h"
#include "lista.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct player{
    char representacaoMapa;
    int playerID;
    int HP;
    int weaponDamage;
    int armor;
    Inventario* inventario;
    bool isDead;
    int posicaoX;
    int posicaoY;
};

int getPlayerHP(Player* player){
    return player->HP;
}

void healPlayer(Player* player, int cura){
    player->HP += cura;
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

Player* criarPlayer(){
    Player *player = (Player*)malloc(sizeof(Player));
    if(player == NULL){
        printf("Erro na alocação de memoria para o jogador");
        exit(1);
    }

    int preSet = gerarNumeroAleatorio(1, 5);

    switch(preSet){

        case 1:
            player->HP = 110;
            player->weaponDamage = 15;
            player->armor = 10;
            break;
        case 2:
            player->HP = 80;
            player->weaponDamage = 25;
            player->armor = 30;
            break;
        case 3:
            player->HP = 150;
            player->weaponDamage = 10;
            player->armor = 5;
            break;
        case 4:
            player->HP = 100;
            player->weaponDamage = 20;
            player->armor = 15;
            break;
        case 5:
            player->HP = 120;
            player->weaponDamage = 10;
            player->armor = 10;
            break;
    }
    player->playerID = preSet;
    player->inventario = criarInventario();
    player->isDead = false;
    player->representacaoMapa = 'P';
    
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
}

bool isPlayerDead(Player* player){
    return player->isDead;
}


void printPlayer(Player* player){
    printf("ID do player: %d\n", player->playerID);
    printf("HP do player: %d\n", player->HP);
    printf("Dano do player: %d\n", player->weaponDamage);
    printf("Armadura do player: %d\n\n", player->armor);
}