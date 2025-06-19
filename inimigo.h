#include <stdbool.h>

typedef struct inimigo Inimigo;
typedef struct listaInimigo ListaInimigo; 

int         getEnemyHP                  (Inimigo*);        //Função que pega o HP atual do inimigo
void        setEnemyHpDamage            (Inimigo*, int);   //Função para tomar dano no HP
int         getEnemyWeaponDamage        (Inimigo*);        //Função para pegar o dano da arma
Inimigo*    criarInimigo                ();                //Função que cria o inimigo com base em pre-sets (HP, dano, armor, etc)
void        destruirInimigo             (Inimigo*);        //Função para destruir o inimigo quando ele morrer
bool        isEnemyDead                 (Inimigo*);        //Função que checa se o inimigo esta morto
char        getRepresentacaoMapa        (Inimigo*);


ListaInimigo* criaListaInimigo();
void inserirInimigo(ListaInimigo*, Inimigo*);


// Funções para debugar

void        printInimigo        (Inimigo*);         //Função para printar os atributos do inimigo