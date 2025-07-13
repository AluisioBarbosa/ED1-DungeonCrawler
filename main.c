#include <stdio.h>
#include "matematica.h"
#include "inimigo.h"
#include "player.h"
#include <windows.h>
#include "mapa.h"
#include "log.h"
#include "game.h"
#include <stdlib.h>

int main(){
    instanciarSemente();
    initLog();
    int decisao = 1;

    Jogo* j = NULL;

    while(decisao == 1){
        j = criarJogo();
        
        while(getEndGame(j) != true){
            update(j);
            Sleep(200);
        }


        printf("Quer jogar de novo? digite 1 para sim e 2 para nao\n");
        scanf("%d", &decisao);
    }




    closeLog();
    return 0;
}