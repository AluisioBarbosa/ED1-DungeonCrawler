#include "combat.h"
#include "player.h"
#include "log.h"
#include "ansi.h"
#include "fila.h"
#include <stdbool.h>
#include "inimigo.h"
#include <windows.h>
#include <stdio.h>

void exibirHUD(Inimigo* inimigo, Player* player){
    system("cls");
    printf(TEXTO_VERDE"Heroi: "RESET ""  "%s\n", getPlayerName(player));
    printf(TEXTO_VERMELHO"HP: " RESET"" "%d/%d\n", getPlayerHP(player), getPlayerMaxHP(player));
    printf("\n\n\n");
    printf(TEXTO_VERMELHO_CLARO"Inimigo: " RESET"" "%s\n", getEnemyName(inimigo));
    printf(TEXTO_VERMELHO "HP: " RESET"" "%d/%d\n", getEnemyHP(inimigo), getEnemyMaxHP(inimigo));
    printf("\n\n\n\n");
    printf(TEXTO_AMARELO_CLARO"Acoes: \n"RESET"");
    printf(TEXTO_AMARELO"[J] " RESET"" "Atacar\n");
    printf(TEXTO_AMARELO"[I] " RESET"" "Abrir inventario\n");
}


bool combate(Inimigo* inimigo, Player* player){
    // turno false = do jogador
    // turno true = do inimigo
    bool turno = false;
    while(isEnemyDead(inimigo) == false && getPlayerHP(player) > 0){
        bool acao = false;
        exibirHUD(inimigo, player);
        if(turno == false){
            while(acao == false){
                if (GetAsyncKeyState('J') & 0x8000){
                    setEnemyHpDamage(inimigo, getPlayerWeaponDamage(player)); 
                    acao = true;
                }
                else if (GetAsyncKeyState('I') & 0x8000){

                }




            }
        }
        acao = false;
    }

    if(isEnemyDead(inimigo) == true){
        exibirHUD(inimigo, player);
        logInfo("Voce derrotou o inimigo!!!!!");
        Sleep(1000);
        return true;
    } // se o inimigo morrer a função retorna true

    if(getPlayerHP <= 0){
        return false;
    } // se o player morrer, a função retorna false


}
void trocaTurno(bool* turno){
    *turno = !(*turno);
}