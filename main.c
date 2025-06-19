#include <stdio.h>
#include "matematica.h"
#include "inimigo.h"
#include "player.h"
#include <windows.h>
#include "mapa.h"

int main(){
    system("chcp 65001 > nul"); // Forçar ter os caracteres de UTF-8
    instanciarSemente();

    // Inimigo* i1;
    // i1 = criarInimigo();
    // printInimigo(i1);

    // Player* p1;
    // p1 = criarPlayer();
    // printPlayer(p1);

    Mapa* dungeon = criaMapa();
    printDungeon(dungeon);






    return 0;
}