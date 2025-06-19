#include <stdbool.h>

typedef struct player Player;

int         getPlayerHP           (Player*);        //Função que pega o HP atual do jogador
void        healPlayer            (Player*, int);   //Função para healar o HP
void        setPlayerHpDamage     (Player*, int);   //Função para tomar dano no HP
int         getPlayerWeaponDamage (Player*);        //Função para pegar o dano da arma
Player*     criarPlayer           ();               //Função que cria o player com base em pre-sets (HP, dano, armor, etc)
void        destruirPlayer        (Player*);        //Função para destruir o jogador quando o jogo acabar (casos de game over)
bool        isPlayerDead          (Player*);        //Função que checa se o player ta morto


// Funções para debugar

void        printPlayer           (Player*);