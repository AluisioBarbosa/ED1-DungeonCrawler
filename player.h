#include <stdbool.h>
#include "inventario.h"
typedef struct player Player;

void        healPlayer              (Player*, int);   //Função para healar o HP
Player*     criarPlayer             ();               //Função que cria o player com base em pre-sets (HP, dano, armor, etc)
void        destruirPlayer          (Player*);        //Função para destruir o jogador quando o jogo acabar (casos de game over)
bool        isPlayerDead            (Player*);        //Função que checa se o player ta morto

//------------------------------------------- Gets e Setters ---------------------------------------------------------//

void        setPlayerHpDamage       (Player*, int);   //Função para tomar dano no HP
void        setPlayerX              (Player*, int);
void        setPlayerY              (Player*, int);
int         getPlayerX              (Player*);
int         getPlayerY              (Player*);
char        getPlayerRepresentacao  (Player*);
int         getPlayerWeaponDamage   (Player*);        //Função para pegar o dano da arma
int         getPlayerHP             (Player*);        //Função que pega o HP atual do jogador
Inventario* getInventario(Player*);

//------------------------------------------- Funções para debugar ---------------------------------------------------------//

void        printPlayer             (Player*);