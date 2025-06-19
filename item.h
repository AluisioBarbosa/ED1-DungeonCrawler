
typedef struct item Item;                   // item tem como atributos ID, char que representa, nome, posicao x e y,
                                            // e ponteiro para uma funcao que vai utiliza-lo
typedef struct listaItem ListaItem;         // linked list duplamente encadeada de itens


Item*               criaItem                        ();
void                destuirItem                     (Item*);

//------------------------------------------- Gets e Setters ---------------------------------------------------------//

void                setItemX                        (Item*, int);
void                setItemY                        (Item*, int);
int                 getItemX                        (Item*);
int                 getItemY                        (Item*);
char                getItemRepresentacao            (Item* item);

//------------------------------------------- Funções usar do item (ponteiro) ---------------------------------------------------------//
void                usarPocao                       (Item*, void*);
void                usarBomba                       (Item*, void*);
void                usarBombaFumaca                 (Item*, void*);

//------------------------------------------- Funções de lista ---------------------------------------------------------//
ListaItem*          criaListaItens                  ();         
void                destruirListaItem               (ListaItem*);
void                inserirItem                     (ListaItem*, Item*);