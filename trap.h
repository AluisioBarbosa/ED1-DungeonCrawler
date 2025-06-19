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



//--------------------------------- Funcoes para lista de traps -----------------------------------------------------//

ListaTrap*      criaListaTrap       ();
void            destruirListaTrap   (ListaTrap*);
void            inserirTrap         (ListaTrap*, Trap*);

