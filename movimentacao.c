#include "movimentacao.h"
#include "log.h"
#include "mapa.h"
#include "game.h"
#include <windows.h>
#include <stdbool.h>

void movimentarJogador(Mapa* dungeon) {
    Player* p1 = getPlayer(dungeon);
    bool flagMovimento = false;

    int xAnterior = getPlayerX(p1);
    int yAnterior = getPlayerY(p1);
    int xPosterior = xAnterior;
    int yPosterior = yAnterior;

    if (GetAsyncKeyState('W') & 0x8000){
        if (getRepresentacaoPosicaoMapa(dungeon, yPosterior - 1, xPosterior) == '#' ||
            getRepresentacaoPosicaoMapa(dungeon, yPosterior - 1, xPosterior) == 'I' ||
            getRepresentacaoPosicaoMapa(dungeon, yPosterior - 1, xPosterior) == '-') {
            logWarn("Posicao invalida, tente novamente!!!");
            Sleep(200);
        }
        else{
            yPosterior -= 1;
            flagMovimento = true;
        }
    }
    else if (GetAsyncKeyState('S') & 0x8000){
        if (getRepresentacaoPosicaoMapa(dungeon, yPosterior + 1, xPosterior) == '#' ||
            getRepresentacaoPosicaoMapa(dungeon, yPosterior + 1, xPosterior) == 'I' ||
            getRepresentacaoPosicaoMapa(dungeon, yPosterior + 1, xPosterior) == '-') {
            logWarn("Posicao invalida, tente novamente!!!");
            Sleep(200);
        }
        else{
            yPosterior += 1;
            flagMovimento = true;
        }
    }
    else if (GetAsyncKeyState('A') & 0x8000){
        if (getRepresentacaoPosicaoMapa(dungeon, yPosterior, xPosterior - 1) == '#' ||
            getRepresentacaoPosicaoMapa(dungeon, yPosterior, xPosterior - 1) == 'I' ||
            getRepresentacaoPosicaoMapa(dungeon, yPosterior, xPosterior - 1) == '-') {
            logWarn("Posicao invalida, tente novamente!!!");
            Sleep(200);
        }
        else{
            xPosterior -= 1;
            flagMovimento = true;
        }
    }
    else if (GetAsyncKeyState('D') & 0x8000){
        if (getRepresentacaoPosicaoMapa(dungeon, yPosterior, xPosterior + 1) == '#' ||
            getRepresentacaoPosicaoMapa(dungeon, yPosterior, xPosterior + 1) == 'I' ||
            getRepresentacaoPosicaoMapa(dungeon, yPosterior, xPosterior + 1) == '-') {
            logWarn("Posicao invalida, tente novamente!!!");
            Sleep(200);
        }
        else{
            xPosterior += 1;
            flagMovimento = true;
        }
    }
    if(flagMovimento == true){
        logMovimento(yAnterior, xAnterior, yPosterior, xPosterior);
        setPlayerX(p1, xPosterior);
        setPlayerY(p1, yPosterior);
        atualizarMapa(dungeon, xAnterior, xPosterior, yAnterior, yPosterior);
    }
}