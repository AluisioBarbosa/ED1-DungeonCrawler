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
    char linha[100];

    logToFile("Começando sessão do jogo");
    while(decisao == 1){
        Jogo* j = criarJogo();
        
        while(getEndGame(j) != true){
            update(j);
            Sleep(200);
        }
        destruirJogo(j);

        printf("Quer jogar de novo? digite 1 para sim e 2 para nao\n");
        while (1) {
            if (fgets(linha, sizeof(linha), stdin) == NULL) {
                decisao = 2; // sai do decisao == 1 e termina o jogo
                break;
            }
            if (sscanf(linha, "%d", &decisao) == 1 && (decisao == 1 || decisao == 2)) {
                break; // só da break no while(1) e começa outro jogo
            }
            printf("Escolha nao encontrada, tente novamente: \n");
        }
    }
    closeLog();
    return 0;
}