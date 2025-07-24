#include <windows.h>
#include "mapa.h"
#include <stdio.h>
#include "player.h"
#include <stdbool.h>
#include "game.h"
#include "combat.h"
#include "log.h"
#include "player.h"
#include "trap.h"
#include "movimentacao.h"
#include "inventario.h"
#include "pilha.h"
#include "fila.h"

typedef enum{
    WORLD_MAP = 1,
    COMBAT = 2,
    INVENTORY = 3
}States;

int GAME_STATE;

struct jogo{
    Mapa* dungeon;
    bool fimDeJogo;
    Pilha* movimentos;
    Fila* logDeBatalha;
};

Jogo* criarJogo(){
    Jogo* jogo = (Jogo*)malloc(sizeof(Jogo));
    if(jogo == NULL){
        logError("ERRO NA HORA DE CRIAR O JOGO");
        exit(1);
    }
    jogo->fimDeJogo = false;
    jogo->dungeon = criaMapa();
    jogo->movimentos = criaPilha();
    jogo->logDeBatalha = criarFila();
    GAME_STATE = WORLD_MAP; // tem que setar o game state para o mapa da dungeon no inicio
    printDungeon(jogo->dungeon);
    return jogo;
}

void update(Jogo* jogo){
    Player* p1 = getPlayer(jogo->dungeon);

    if (GetAsyncKeyState('F') & 0x8000){
        if(getDebugState(jogo->dungeon) == false){
            setDebugState(jogo->dungeon, true);
        }
        else{
            setDebugState(jogo->dungeon, false);
        }
        setarInimigosDebug(jogo->dungeon, getDebugState(jogo->dungeon));
    }
    

    if(checarExisteInimigoPosicaoMapa(jogo->dungeon) == true){
        Inimigo* inimigo = buscarInimigoXY(getListaInimigos(jogo->dungeon), getPlayerX(p1), getPlayerY(p1));
        GAME_STATE = COMBAT;
    }
    else if(checarExisteTrapPosicaoMapa(jogo->dungeon) == true){
        Trap* armadilha = buscarTrapXY(getListaTrap(jogo->dungeon), getPlayerX(p1), getPlayerY(p1));
        setPlayerHpDamage(p1, getTrapDamage(armadilha));
        logInfo("Voce pisou numa armadilha!!");
        removerTrap(getListaTrap(jogo->dungeon), armadilha);
        armadilha = NULL;
        Sleep(1000);
        printDungeon(jogo->dungeon);
    }
    else if(checarExisteItemPosicaoMapa(jogo->dungeon) == true){
        Item* item = buscarItemXY(getListaItem(jogo->dungeon), getPlayerX(p1), getPlayerY(p1));
        adicionarNoInventario(getInventario(p1), copiarItem(item));
        system("cls");
        char mensagem[64];
        snprintf(mensagem, sizeof(mensagem), "Voce pegou um item: %s", getItemNome(item));
        logInfo(mensagem);
        removerItem(getListaItem(jogo->dungeon), item);
        item = NULL;
        Sleep(1000);
        printDungeon(jogo->dungeon);
    }
    else if(GetAsyncKeyState('I') & 0x8000){
        while(GetAsyncKeyState('I') & 0x8000) {
            Sleep(10); // enquanto nao soltar a tecla nao avança
        }

        GAME_STATE = INVENTORY;
    }

    if(getPlayerX(getPlayer(jogo->dungeon)) == 14 && getPlayerY(getPlayer(jogo->dungeon)) == 13){ // termina o jogo se chegar na saida
        system("cls");
        logInfo("Voce terminou o jogo!!");
        jogo->fimDeJogo = true;
    }
    else if(isPlayerDead(p1)){ // termina o jogo se o HP for <= 0
        system("cls");
        logInfo("Voce morreu.");
        logInfo("GAME OVER!");
        jogo->fimDeJogo = true;
    }
    
    else if(GAME_STATE == WORLD_MAP){
        movimentarJogador(jogo->dungeon, jogo->movimentos);
    }
    else if(GAME_STATE == COMBAT){
        Inimigo* inimigo = buscarInimigoXY(getListaInimigos(jogo->dungeon), getPlayerX(p1), getPlayerY(p1));
        if(combate(inimigo, p1, GAME_STATE, jogo->logDeBatalha) == true){
            removerInimigo(getListaInimigos(jogo->dungeon), inimigo);
            inimigo = NULL;
            GAME_STATE = WORLD_MAP;
            printDungeon(jogo->dungeon);
        }
    }
    else if(GAME_STATE == INVENTORY){
        Item* item = inventarioLoop(getInventario(p1), GAME_STATE);
        if(item != NULL){
            usarItem(item, p1);
            removerItem(getInventarioLista(getInventario(p1)), item);
        }
        GAME_STATE = WORLD_MAP;
        printDungeon(jogo->dungeon);
        item = NULL;
    }

    
}


bool getEndGame(Jogo* jogo){
    return jogo->fimDeJogo;
}

void destruirJogo(Jogo* jogo){
    destruirMapa(jogo->dungeon);
    destruirPilha(jogo->movimentos);
    destruirFila(jogo->logDeBatalha);
    free(jogo);
}


void changeDebugState(Jogo* jogo){
    if(getDebugState(jogo->dungeon) == false){
        setDebugState(jogo->dungeon, true);
    }
    else{
        setDebugState(jogo->dungeon, false);
    }
}

Mapa* getGameDungeon(Jogo* jogo){
    return jogo->dungeon;
}


