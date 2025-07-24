#include <stdbool.h>

typedef struct inimigo Inimigo;
typedef struct listaInimigo ListaInimigo; 


Inimigo*            criarInimigo                    ();                //Função que cria o inimigo com base em pre-sets (HP, dano, armor, etc)
void                destruirInimigo                 (Inimigo*);        //Função para destruir o inimigo quando ele morrer
bool                isEnemyDead                     (Inimigo*);        //Função que checa se o inimigo esta morto
void                healEnemy                       (Inimigo*, int);
void                addEnemyArmor                   (Inimigo*, int);

// ------------------------------------- Gets e setters ---------------------------------------------------------------//

void                setEnemyHpDamage                (Inimigo*, int);   //Função para tomar dano no HP
void                setEnemyX                       (Inimigo*, int);
void                setEnemyY                       (Inimigo*, int);
int                 getEnemyX                       (Inimigo*);
int                 getEnemyY                       (Inimigo*);
char                getInimigoRepresentacao         (Inimigo*);
int                 getEnemyWeaponDamage            (Inimigo*);        //Função para pegar o dano da arma
int                 getEnemyHP                      (Inimigo*);        //Função que pega o HP atual do inimigo
char*               getEnemyName                    (Inimigo*);
int                 getEnemyMaxHP                   (Inimigo*);

// ------------------------------------- Funções de lista ---------------------------------------------------------------//
ListaInimigo*       criaListaInimigo                ();
void                inserirInimigo                  (ListaInimigo*, Inimigo*);
void                destruirListaInimigo            (ListaInimigo*);
int                 getInimigoQuantidade            (ListaInimigo*);
bool                removerInimigo                  (ListaInimigo*, Inimigo*);
Inimigo*            buscarInimigoXY                 (ListaInimigo*, int, int);
bool                checarInimigoXY                 (ListaInimigo*, int, int);
void                atualizarInimigosNoMapa         (ListaInimigo*, char[15][15], bool);
void                esconderInimigosDoMapa          (ListaInimigo*, char [15][15]);


// ------------------------------------- Funções para debugar ---------------------------------------------------------------//

void                printInimigo                    (Inimigo*);         //Função para printar os atributos do inimigo