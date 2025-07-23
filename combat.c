#include "combat.h"
#include "player.h"
#include "log.h"
#include "ansi.h"
#include "fila.h"
#include <stdbool.h>
#include "inimigo.h"
#include <windows.h>
#include <stdio.h>
#include "matematica.h"

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

void turnoInimigo(Inimigo* inimigo, Player* player, bool* turno){
    // aqui seria a "arvore IA" de batalha inimiga
    if(getEnemyHP(inimigo) <= 20){
        // se o inimigo tiver <= 20 de vida, ele tenta se curar, tem 15% de curar 18 de vida
        if(gerarNumeroAleatorio(1,100) <= 15){
            healEnemy(inimigo, 18); // Como todo turno ele pode se curar, tem que balancear esse numero de cura
            exibirHUD(inimigo, player);
            logInfo("O inimigo se curou em 18 pontos de HP");
            Sleep(2000);
            trocaTurno(turno);
        }
        else{
            // aqui ele tenta se curar mas nao consegue
            logInfo("O inimigo tentou se curar, porem nao achou a pocao em sua bolsa a tempo...");
            Sleep(2000);
            trocaTurno(turno);
        }
    }
    else{
        if(getEnemyHP(inimigo) > 40){
            // se tiver mais de 40 de vida, ele bate no jogador
            setPlayerHpDamage(player, getEnemyWeaponDamage(inimigo));
            exibirHUD(inimigo, player);
            logInfo("O inimigo ataca o heroi!");
            Sleep(2000);
            trocaTurno(turno);
        }
        else{
            // se tiver algo entre 16 e 40 de vida, ele aumenta sua propria armadura e bate fraco no jogador
            addEnemyArmor(inimigo, 10);
            setPlayerHpDamage(player, 8);
            exibirHUD(inimigo, player);
            logInfo("O inimigo aumenta sua propria armadura e acerta fracamente o heroi");
            Sleep(2000);
            trocaTurno(turno);
        }
    }


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
                    trocaTurno(&turno);
                    exibirHUD(inimigo, player);
                    logInfo("Voce bateu no inimigo!");
                    Sleep(2000);
                }
                else if (GetAsyncKeyState('I') & 0x8000){

                }




            }
        }
        else if(turno == true){
            turnoInimigo(inimigo, player, &turno);
        }
        acao = false;


    }

    if(isEnemyDead(inimigo) == true){
        exibirHUD(inimigo, player);
        logInfo("Voce derrotou o inimigo!!!!!");
        Sleep(2000);
        return true;
    } // se o inimigo morrer a função retorna true

    if(isPlayerDead(player)){
        return false;
    } // se o player morrer, a função retorna false


}
void trocaTurno(bool* turno){
    *turno = !(*turno);
}