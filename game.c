#include <windows.h>
#include "mapa.h"
#include "player.h"
#include <stdbool.h>
#include "game.h"
#include "log.h"
#include "player.h"

struct jogo{
    Mapa* dungeon;
    bool fimDeJogo;
};

Jogo* criarJogo(){
    Jogo* jogo = (Jogo*)malloc(sizeof(Jogo));
    if(jogo == NULL){
        logError("NA HORA DE CRIAR O JOGO");
        exit(1);
    }
    jogo->fimDeJogo = false;
    jogo->dungeon = criaMapa();
    printDungeon(jogo->dungeon);
    return jogo;
}



void update(Jogo* jogo){
    Player* p1 = getPlayer(jogo->dungeon);
    bool flagMovimento = false;

    int xAnterior = getPlayerX(p1);
    int yAnterior = getPlayerY(p1);
    int xPosterior = xAnterior;
    int yPosterior = yAnterior;

    if (GetAsyncKeyState('W') & 0x8000){
        yPosterior -= 1; // sobe - linha diminui
        flagMovimento = true;
    }
    else if(GetAsyncKeyState('S') & 0x8000){
        yPosterior += 1; // desce - linha aumenta
        flagMovimento = true;
    }
    else if(GetAsyncKeyState('A') & 0x8000){
        xPosterior -= 1; // esquerda - coluna diminui
        flagMovimento = true;
    }
    else if(GetAsyncKeyState('D') & 0x8000){
        xPosterior += 1; // direita - coluna aumenta
        flagMovimento = true;
    }

    if(flagMovimento == true){
        setPlayerX(p1, xPosterior);
        setPlayerY(p1, yPosterior);
        atualizarMapa(jogo->dungeon, xAnterior, xPosterior, yAnterior, yPosterior);
        flagMovimento = false;
    }
}


bool getEndGame(Jogo* jogo){
    return jogo->fimDeJogo;
}