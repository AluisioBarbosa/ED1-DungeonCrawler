#include <stdbool.h>

typedef struct trap Trap;                   
typedef struct listaTrap ListaTrap;


Trap*               criaTrap                ();
void                destruirTrap            (Trap*);



//--------------------------------- Gets e setters -----------------------------------------------------------------//


void                setTrapX                (Trap*, int);
void                setTrapY                (Trap*, int);
int                 getTrapX                (Trap*);
int                 getTrapY                (Trap*);
bool                getTrapState            (Trap*);
char                getTrapRepresentacao    (Trap*);
int                 getTrapDamage           (Trap*);
int getTrapQuantidade(ListaTrap*);



//--------------------------------- Funcoes para lista de traps -----------------------------------------------------//

ListaTrap*      criaListaTrap       ();
void            destruirListaTrap   (ListaTrap*);
void            inserirTrap         (ListaTrap*, Trap*);
void esconderTrapsDoMapa(ListaTrap* , char [15][15]);
void atualizarTrapsNoMapa(ListaTrap* , char [15][15], bool );
Trap* buscarTrapXY(ListaTrap* , int , int );
bool checarTrapXY(ListaTrap*, int, int);
bool removerTrap(ListaTrap*, Trap*);

