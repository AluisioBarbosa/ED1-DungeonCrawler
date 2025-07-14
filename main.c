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


    while(decisao == 1){
        Jogo* j = criarJogo();
        
        while(getEndGame(j) != true){
            update(j);
            Sleep(200);
        }


        while(getchar() != '\n');
        printf("Quer jogar de novo? digite 1 para sim e 2 para nao\n");
        scanf("%d", &decisao);

        while(decisao != 1 && decisao != 2){
            printf("Escolha nao encontrada, tente novamente: \n");
            scanf("%d", &decisao);
        }
    }




    closeLog();
    return 0;
}