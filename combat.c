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
#include "item.h"
#include "inventario.h"

void exibirHUD(Inimigo* inimigo, Player* player, Fila* logDeBatalha){
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
    imprimirFila(logDeBatalha);
}

void turnoInimigo(Inimigo* inimigo, Player* player, bool* turno, Fila* logDeBatalha){
    // aqui seria a "arvore IA" de batalha inimiga
    if(getEnemyHP(inimigo) <= 20){
        // se o inimigo tiver <= 20 de vida, ele tenta se curar, tem 15% de curar 18 de vida
        if(gerarNumeroAleatorio(1,100) <= 15){
            healEnemy(inimigo, 18); // Como todo turno ele pode se curar, tem que balancear esse numero de cura
            enfileirar(logDeBatalha, "O inimigo se curou em 18 pontos de HP");
            exibirHUD(inimigo, player, logDeBatalha);
            Sleep(2000);
            trocaTurno(turno);
        }
        else{
            // aqui ele tenta se curar mas nao consegue
            enfileirar(logDeBatalha, "O inimigo tentou se curar, porem nao achou a pocao em sua bolsa a tempo...");
            exibirHUD(inimigo, player, logDeBatalha);
            Sleep(2000);
            trocaTurno(turno);
        }
    }
    else{
        if(getEnemyHP(inimigo) > 40){
            // se tiver mais de 40 de vida, ele bate no jogador
            setPlayerHpDamage(player, getEnemyWeaponDamage(inimigo));
            enfileirar(logDeBatalha, "O inimigo ataca o heroi!");
            exibirHUD(inimigo, player, logDeBatalha);
            Sleep(2000);
            trocaTurno(turno);
        }
        else{
            // se tiver algo entre 16 e 40 de vida, ele aumenta sua propria armadura e bate fraco no jogador
            addEnemyArmor(inimigo, 3);
            setPlayerHpDamage(player, 8);
            enfileirar(logDeBatalha ,"O inimigo aumenta sua propria armadura e acerta fracamente o heroi");
            exibirHUD(inimigo, player, logDeBatalha);
            Sleep(2000);
            trocaTurno(turno);
        }
    }


}


bool combate(Inimigo* inimigo, Player* player, int GAME_STATE, Fila* logDeBatalha){
    // turno false = do jogador
    // turno true = do inimigo
    bool bombaDeFumaca = false;
    bool turno = false;
    while(isEnemyDead(inimigo) == false && getPlayerHP(player) > 0){
        bool acao = false;
        exibirHUD(inimigo, player, logDeBatalha);

        if(turno == true){
            turnoInimigo(inimigo, player, &turno, logDeBatalha);
        }
        else if(turno == false){
            while(acao == false){
                if (GetAsyncKeyState('J') & 0x8000){
                    setEnemyHpDamage(inimigo, getPlayerWeaponDamage(player)); 
                    enfileirar(logDeBatalha, "Voce bateu no inimigo!");
                    acao = true;
                    trocaTurno(&turno);
                    exibirHUD(inimigo, player, logDeBatalha);
                    Sleep(1500);
                }
                else if (GetAsyncKeyState('I') & 0x8000){
                    while(GetAsyncKeyState('I') & 0x8000) {
                        Sleep(10);  // Enquanto nao soltar a tecla, ele nao avança
                    }
                    Item* item = inventarioLoop(getInventario(player), GAME_STATE);
                    if(item != NULL){
                        int ID = getItemID(item);
                        switch(ID){
                            case 1: // pocao de vida
                                usarItem(item, player);
                                enfileirar(logDeBatalha, "Voce usa uma pocao de cura");
                                exibirHUD(inimigo, player, logDeBatalha);
                                Sleep(500);
                                break;
                            case 2:// bomba
                                usarItem(item, inimigo);
                                enfileirar(logDeBatalha, "Voce usa a bomba para explodir um inimigo!");
                                exibirHUD(inimigo, player, logDeBatalha);
                                Sleep(500);
                                break;
                            case 3:// bomba de fumaça
                                usarItem(item, inimigo);
                                bombaDeFumaca = true;
                                system("cls");
                                logInfo("Voce escapou da batalha com uma bomba de fumaca");
                                break;
                        }
                        removerItem(getInventarioLista(getInventario(player)), item);
                        acao = true;
                        trocaTurno(&turno);
                        
                    }
                    if(bombaDeFumaca == false){
                        exibirHUD(inimigo, player, logDeBatalha);
                    }
                    Sleep(300);
                }
            }
        }
        
        acao = false;
    }

    if(isEnemyDead(inimigo) == true){
        if(bombaDeFumaca == true){
            Sleep(2000);
            esvaziarFila(logDeBatalha);
            return true;
        }
        else{
            exibirHUD(inimigo, player, logDeBatalha);
            logInfo("Voce derrotou o inimigo!!!!!");
            esvaziarFila(logDeBatalha);
            Sleep(2000);
            return true;
        }
    } // se o inimigo morrer a função retorna true

    if(isPlayerDead(player)){
        return false;
    } // se o player morrer, a função retorna false


}
void trocaTurno(bool* turno){
    *turno = !(*turno);
}