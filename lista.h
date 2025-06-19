typedef struct lista Lista;

Lista*  criaLista       ();
void    imprimeLista    (Lista*);

int     removerInicio   (Lista*);
int     removerFim      (Lista*);
int     removerMeio     (Lista*, int);

void    inserirInicio   (Lista*, int);
void    inserirFim      (Lista*, int);
void    inserirMeio     (Lista*, int, int);

void    destruirLista   (Lista*);

int     getTamanhoLista (Lista*);