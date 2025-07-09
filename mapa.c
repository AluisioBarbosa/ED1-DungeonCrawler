#include "mapa.h"
#include "inimigo.h"
#include "player.h"
#include "item.h"
#include "matematica.h"
#include "trap.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


struct mapa{
    char mapa[15][15];
    ListaTrap* traps;
    ListaInimigo* Inimigos;
    ListaItem* itens;
    Player* player;
};


Mapa* criaMapa(){
    int preSet = gerarNumeroAleatorio(1,3);
    Mapa* dungeon = (Mapa*)malloc(sizeof(Mapa));
    if(dungeon == NULL){
        printf("Erro na alocação de memoria na criação do mapa\n");
        exit(1);
    }
    preSet = 1;
    dungeon->Inimigos = criaListaInimigo();
    dungeon->traps = criaListaTrap();
    dungeon->itens = criaListaItens();
    dungeon->player = criarPlayer();

    switch(preSet){
        case 1:{                                //1   2   3   4   5   6   7   8   9   10  11  12  13  14  15
            char mapaTemp[15][15] = {           {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}, // 1
                                                {'#',' ',' ',' ','|',' ',' ',' ',' ',' ','|',' ',' ',' ','#'}, // 2
                                                {'#',' ',' ',' ','+','_','_',' ','|',' ','+','_','_',' ','#'}, // 3
                                                {'#',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','#'}, // 4
                                                {'#','_','_','_','_','_','+','_','+','_','_',' ','_','_','#'}, // 5
                                                {'#',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','#'}, // 6
                                                {'#',' ','|',' ','|',' ','+','_','_',' ','|',' ','_','_','#'}, // 7 
                                                {'#',' ','|',' ','|',' ',' ',' ',' ',' ','|',' ',' ',' ','#'}, // 8
                                                {'#','_','+',' ','|',' ','_','_','+',' ','+','_','_','_','#'}, // 9 
                                                {'#',' ',' ',' ','|',' ',' ',' ','|',' ','|',' ',' ',' ','#'}, //10
                                                {'#','_','+',' ','|',' ','+','_','+','_','+',' ',' ',' ','#'}, //11
                                                {'#',' ','|',' ','|',' ','|',' ',' ',' ','|',' ',' ',' ','#'}, //12
                                                {'#',' ','|',' ','+','_','+',' ','|',' ','|',' ','_','_','#'}, //13
                                                {'#',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','#'}, //14
                                                {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}};//15
            memcpy(dungeon->mapa, mapaTemp, sizeof(mapaTemp));
            setarItens(dungeon);
            setarInimigos(dungeon);
            setarTraps(dungeon);
            dungeon->mapa[getPlayerX(dungeon->player)][getPlayerY(dungeon->player)] = getPlayerRepresentacao(dungeon->player);
            break;
        }
        case 2:



            break;
        case 3:





            break;
    }


    return dungeon;
}


void printDungeon(Mapa* dungeon){
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            printf("%c ", dungeon->mapa[i][j]);
        }
        printf("\n");
    }
}

void setarInimigos(Mapa* dungeon){
    int quantidade = gerarNumeroAleatorio(4, 8);
    for(int i = 0; i < quantidade; i++){
        int setado = 0;
        while(setado == 0){
            int j = gerarNumeroAleatorio(0, 14);
            int k = gerarNumeroAleatorio(0, 14);
            if(dungeon->mapa[j][k] == ' '){
                Inimigo* inimigo = criarInimigo();
                setEnemyX(inimigo, j);
                setEnemyY(inimigo, k);
                dungeon->mapa[j][k] = getInimigoRepresentacao(inimigo);
                inserirInimigo(dungeon->Inimigos, inimigo);
                setado = 1;
            }
        }
    }
}

void setarTraps(Mapa* dungeon){
    int quantidade = gerarNumeroAleatorio(5,7);
    for(int i = 0; i < quantidade; i++){
        int setado = 0;
        while(setado == 0){
            int j = gerarNumeroAleatorio(0,14);
            int k = gerarNumeroAleatorio(0,14);
            if(dungeon->mapa[j][k] == ' '){
                Trap* armadilha = criaTrap();
                dungeon->mapa[j][k] = getTrapRepresentacao(armadilha);
                setTrapX(armadilha, j);
                setTrapY(armadilha, k);
                inserirTrap(dungeon->traps, armadilha);
                setado = 1;
            }
        }
    }
}

void setarItens(Mapa* dungeon){
    int quantidade = gerarNumeroAleatorio(3,5);
    for(int i = 0; i < quantidade; i++){
        int setado = 0;
        while(setado == 0){
            int j = gerarNumeroAleatorio(0, 14);
            int k = gerarNumeroAleatorio(0, 14);
            if(dungeon->mapa[j][k] == ' '){
                Item* item = criaItem();
                dungeon->mapa[j][k] = getItemRepresentacao(item);
                setItemX(item, j);
                setItemY(item, k);
                inserirItem(dungeon->itens, item);
                setado = 1;
            }
        }
    }
}
