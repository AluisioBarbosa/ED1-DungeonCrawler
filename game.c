#include <windows.h>
#include "mapa.h"
#include <stdio.h>
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

    if(getPlayerX(getPlayer(jogo->dungeon)) == 14 && getPlayerY(getPlayer(jogo->dungeon)) == 13){
        system("cls");
        printf("Voce terminou o jogo!\n");
        jogo->fimDeJogo = true;
    }
    else{
        bool flagMovimento = false;

        int xAnterior = getPlayerX(p1);
        int yAnterior = getPlayerY(p1);
        int xPosterior = xAnterior;
        int yPosterior = yAnterior;

        if (GetAsyncKeyState('W') & 0x8000){
            if(getRepresentacaoPosicaoMapa(jogo->dungeon, yPosterior - 1, xPosterior) == '#' ||
            getRepresentacaoPosicaoMapa(jogo->dungeon, yPosterior - 1, xPosterior) == 'I' ||
            getRepresentacaoPosicaoMapa(jogo->dungeon, yPosterior - 1, xPosterior) == '-'){
                logError("Posicao invalida, tente novamente!!!");
                printDungeon(jogo->dungeon);
            }
            else{
                yPosterior -= 1; // sobe - linha diminui
                flagMovimento = true;
            }
        }
        else if(GetAsyncKeyState('S') & 0x8000){
            if(getRepresentacaoPosicaoMapa(jogo->dungeon, yPosterior + 1, xPosterior) == '#' ||
            getRepresentacaoPosicaoMapa(jogo->dungeon, yPosterior + 1, xPosterior) == 'I' ||
            getRepresentacaoPosicaoMapa(jogo->dungeon, yPosterior + 1, xPosterior) == '-'){
                logError("Posicao invalida, tente novamente!!!");
            }
            else{
                yPosterior += 1; // desce - linha aumenta
                flagMovimento = true;
            }
        }
        else if(GetAsyncKeyState('A') & 0x8000){
            if(getRepresentacaoPosicaoMapa(jogo->dungeon, yPosterior, xPosterior - 1) == '#' ||
            getRepresentacaoPosicaoMapa(jogo->dungeon, yPosterior, xPosterior - 1) == 'I' ||
            getRepresentacaoPosicaoMapa(jogo->dungeon, yPosterior, xPosterior - 1) == '-'){
                logError("Posicao invalida, tente novamente!!!");
            }
            else{
                xPosterior -= 1; // esquerda - coluna diminui
                flagMovimento = true;
            }
        }
        else if(GetAsyncKeyState('D') & 0x8000){
            if(getRepresentacaoPosicaoMapa(jogo->dungeon, yPosterior, xPosterior + 1) == '#' ||
            getRepresentacaoPosicaoMapa(jogo->dungeon, yPosterior, xPosterior + 1) == 'I' ||
            getRepresentacaoPosicaoMapa(jogo->dungeon, yPosterior, xPosterior + 1) == '-'){
                logError("Posicao invalida, tente novamente!!!");
            }
            else{
                xPosterior += 1; // direita - coluna aumenta
                flagMovimento = true;
            }
        }

        if(flagMovimento == true){
            logMovimento(yAnterior, xAnterior, yPosterior, xPosterior);
            setPlayerX(p1, xPosterior);
            setPlayerY(p1, yPosterior);
            atualizarMapa(jogo->dungeon, xAnterior, xPosterior, yAnterior, yPosterior);
            flagMovimento = false;
        }
    }
}


bool getEndGame(Jogo* jogo){
    return jogo->fimDeJogo;
}

void destruirJogo(Jogo* jogo){
    destruirMapa(jogo->dungeon);
    free(jogo);
}