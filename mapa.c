#include "mapa.h"
#include "inimigo.h"
#include "player.h"
#include "item.h"
#include "matematica.h"
#include "trap.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ansi.h"
#include "log.h"
#include <windows.h>


struct mapa{
    char mapa[15][15];
    ListaTrap* traps;
    ListaInimigo* Inimigos;
    ListaItem* itens;
    Player* player;
    bool debug;
};


Mapa* criaMapa(){
    int preSet = gerarNumeroAleatorio(1,3);
    Mapa* dungeon = (Mapa*)malloc(sizeof(Mapa));
    if(dungeon == NULL){
        logError("na alocação de memoria na criação do mapa\n");
        exit(1);
    }
    logInfo("Criando dungeon...");
    Sleep(150);
    dungeon->Inimigos = criaListaInimigo();
    logInfo("Criando inimigos...");
    Sleep(200);
    dungeon->traps = criaListaTrap();
    logInfo("Criando traps...");
    Sleep(100);
    dungeon->itens = criaListaItens();
    logInfo("Colocando itens na dungeon...");
    Sleep(500);
    dungeon->player = criarPlayer();
    logInfo("Escolhendo o heroi...");
    Sleep(600);
    dungeon->debug = false;

    switch(preSet){
        case 1:{
            char mapaTemp[15][15] = {           {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
                                                {'#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ','#'},
                                                {'#',' ',' ',' ','#','#','#',' ','#',' ','#','#','#',' ','#'},
                                                {'#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','#'},
                                                {'#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#'},
                                                {'#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#'},
                                                {'#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#','#','#'},
                                                {'#',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ','#'},
                                                {'#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#','#'},
                                                {'#',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#'},
                                                {'#','#','#',' ','#',' ','#','#','#','#','#',' ','#',' ','#'},
                                                {'#',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#'},
                                                {'#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#'},
                                                {'#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','$'},
                                                {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}};
            memcpy(dungeon->mapa, mapaTemp, sizeof(mapaTemp));
            break;
        }
        case 2:{
            char mapaTemp[15][15] ={            {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
                                                {'#',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ','#'},
                                                {'#',' ','#','#','#',' ','#',' ','#','#','#','#','#',' ','#'},
                                                {'#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                                                {'#','#','#',' ','#',' ','#',' ','#',' ','#','#','#','#','#'},
                                                {'#',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#'},
                                                {'#','#','#',' ','#',' ','#','#','#',' ','#','#','#',' ','#'},
                                                {'#',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ',' ',' ','#'},
                                                {'#',' ','#','#','#',' ','#',' ','#',' ','#','#','#','#','#'},
                                                {'#',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ','#'},
                                                {'#','#','#',' ','#',' ','#',' ','#',' ','#','#','#',' ','#'},
                                                {'#',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#'},
                                                {'#',' ','#',' ','#','#','#',' ','#','#','#','#','#',' ','#'},
                                                {'#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','$'},
                                                {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}};
            memcpy(dungeon->mapa, mapaTemp, sizeof(mapaTemp));
            break;
        }
        case 3:{
            char mapaTemp[15][15] = {           {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
                                                {'#',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','#'},
                                                {'#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#'},
                                                {'#',' ',' ',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#'},
                                                {'#',' ','#','#','#',' ','#','#','#','#','#',' ','#',' ','#'},
                                                {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
                                                {'#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#'},
                                                {'#',' ','#',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#'},
                                                {'#',' ','#','#','#',' ','#',' ','#',' ','#',' ','#','#','#'},
                                                {'#',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#'},
                                                {'#','#','#',' ','#','#','#','#','#',' ','#',' ','#',' ','#'},
                                                {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#'},
                                                {'#',' ','#','#','#',' ','#',' ','#','#','#','#','#',' ','#'},
                                                {'#',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ','$'},
                                                {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}};
            memcpy(dungeon->mapa, mapaTemp, sizeof(mapaTemp));
            break;
        }
    }
    setarItens(dungeon);
    setarInimigos(dungeon);
    setarTraps(dungeon);
    dungeon->mapa[getPlayerY(dungeon->player)][getPlayerX(dungeon->player)] = getPlayerRepresentacao(dungeon->player);
    logInfo("Dungeon criada com sucesso.");
    Sleep(450);
    return dungeon;
}


void printDungeon(Mapa* dungeon){
    system("cls");
    if(dungeon->debug == false){
        for(int i = 0; i < 15; i++){
            for(int j = 0; j < 15; j++){
                switch(dungeon->mapa[i][j]){
                    case 'P':
                        printf(TEXTO_VERDE_CLARO "P "RESET "");
                        break;
                    case '#':
                        printf(TEXTO_PRETO_CLARO "# "RESET "");
                        break;
                    default:
                        printf("%c ", dungeon->mapa[i][j]);
                        break;
                }
            }
            printf("\n");
        }
    }
    else{
        for(int i = 0; i < 15; i++){
            for(int j = 0; j < 15; j++){
                switch(dungeon->mapa[i][j]){
                    case '#':
                        printf(TEXTO_PRETO_CLARO "# "RESET "");
                        break;
                    case 'P':
                        printf(TEXTO_VERDE_CLARO "P "RESET "");
                        break;
                    case 'O':
                        printf(TEXTO_AMARELO "O "RESET "");
                        break;
                    case 'H':
                        printf(TEXTO_VERMELHO "H "RESET "");
                        break;
                    case 'E':
                        printf(TEXTO_VERMELHO "E "RESET "");
                        break;
                    case 'Z':
                        printf(TEXTO_VERMELHO "Z "RESET "");
                        break;
                    case 'T':
                        printf(TEXTO_CIANO"T "RESET "");
                        break;
                    default:
                        printf("%c ", dungeon->mapa[i][j]);
                        break;
                }
            }
            printf("\n");
        }
    }
    printf("VIDA DO JOGADOR: %d     QUANTIDADE DE ITENS NA DUNGEON: %d", getPlayerHP(dungeon->player), getQuantidadeItem(dungeon->itens));
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
                setEnemyX(inimigo, k);
                setEnemyY(inimigo, j);
                // dungeon->mapa[j][k] = getInimigoRepresentacao(inimigo); // só tire o comentario caso queira debugar diretamente
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
                // dungeon->mapa[j][k] = getTrapRepresentacao(armadilha); // só tire o comentario caso queira debugar diretamente
                setTrapX(armadilha, k);
                setTrapY(armadilha, j);
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
                // dungeon->mapa[j][k] = getItemRepresentacao(item); // só tire o comentario caso queira debugar diretamente
                setItemX(item, k);
                setItemY(item, j);
                inserirItem(dungeon->itens, item);
                setado = 1;
            }
        }
    }
}

Player* getPlayer(Mapa* dungeon){
    return dungeon->player;
}

void atualizarMapa(Mapa* dungeon, int xAnt, int xPos, int yAnt, int yPos){
    Player* p = dungeon->player;

    dungeon->mapa[yAnt][xAnt] = ' ';
    dungeon->mapa[yPos][xPos] = getPlayerRepresentacao(p);



    printDungeon(dungeon);
}

char getRepresentacaoPosicaoMapa(Mapa* dungeon, int altura, int largura){
    return dungeon->mapa[altura][largura];
}

void destruirMapa(Mapa* dungeon){
    logInfo("DESTRUINDO DUNGEON");
    destruirPlayer(dungeon->player);
    destruirListaTrap(dungeon->traps);
    destruirListaInimigo(dungeon->Inimigos);
    destruirListaItem(dungeon->itens);
    free(dungeon);
}


// teoricamente o debug não é um atributo do mapa e sim do proprio jogo
// se sobrar tempo, colocar o debug e suas atribuições consequentes
// no game.h

bool getDebugState(Mapa* dungeon){
    return dungeon->debug;
}

void setDebugState(Mapa* dungeon, bool state){
    dungeon->debug = state;
}

void setarInimigosDebug(Mapa* dungeon, bool debugState){
    if(debugState == true){
        atualizarInimigosNoMapa(dungeon->Inimigos, dungeon->mapa, dungeon->debug);
        atualizarItemsNoMapa(dungeon->itens, dungeon->mapa, dungeon->debug);
        atualizarTrapsNoMapa(dungeon->traps, dungeon->mapa, dungeon->debug);
        printDungeon(dungeon);
    }
    else{
        esconderInimigosDoMapa(dungeon->Inimigos, dungeon->mapa);
        esconderItemsDoMapa(dungeon->itens, dungeon->mapa);
        esconderTrapsDoMapa(dungeon->traps, dungeon->mapa);
        printDungeon(dungeon);
    }
}



bool checarExisteInimigoPosicaoMapa(Mapa* dungeon){
    if(checarInimigoXY(dungeon->Inimigos, getPlayerX(dungeon->player), getPlayerY(dungeon->player)) == true){
        return true;
    }
    return false;
}

bool checarExisteTrapPosicaoMapa(Mapa* dungeon){
    if(checarTrapXY(dungeon->traps, getPlayerX(dungeon->player), getPlayerY(dungeon->player)) == true){
        return true;
    }
    return false;
}

bool checarExisteItemPosicaoMapa(Mapa* dungeon){
    if(checarItemXY(dungeon->itens, getPlayerX(dungeon->player), getPlayerY(dungeon->player)) == true){
        return true;
    }
    return false;
}

ListaTrap* getListaTrap(Mapa* dungeon){
    return dungeon->traps;
}

ListaItem* getListaItem(Mapa* dungeon){
    return dungeon->itens;
}

ListaInimigo* getListaInimigos(Mapa* dungeon){
    return dungeon->Inimigos;
}