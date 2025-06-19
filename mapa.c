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

    switch(preSet){
        case 1:{
            char mapaTemp[15][15] = {           {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
                                                {'#','.','.','.','.','I','.','.','.','.','.','.','.','.','#'},
                                                {'#','.','.','I','.','I','.','.','.','.','.','.','.','.','#'},
                                                {'#','.','.','I','.','I','.','.','.','.','.','.','.','.','#'},
                                                {'#','-','-','I','.','I','.','.','.','.','.','.','.','.','#'},
                                                {'#','.','.','.','.','I','.','.','.','.','.','.','.','.','#'},
                                                {'#','.','.','.','.','I','.','.','.','.','.','.','.','.','#'},
                                                {'#','.','.','-','-','I','.','.','.','.','.','.','.','.','#'},
                                                {'#','.','.','.','.','I','.','.','.','.','.','.','.','.','#'},
                                                {'#','.','.','.','.','I','.','.','.','.','.','.','.','.','#'},
                                                {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
                                                {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
                                                {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
                                                {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
                                                {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}};
            memcpy(dungeon->mapa, mapaTemp, sizeof(mapaTemp));
            setarInimigos(dungeon);
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
            if(dungeon->mapa[j][k] == '.'){
                Inimigo* inimigo = criarInimigo();
                dungeon->mapa[j][k] = getRepresentacaoMapa(inimigo);
                inserirInimigo(dungeon->Inimigos, inimigo);
                setado = 1;
            }
        }
    }
}