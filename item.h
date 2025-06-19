
typedef struct item Item;                   // item tem como atributos ID, char que representa, nome, posicao x e y,
                                            // e ponteiro para uma funcao que vai utiliza-lo
typedef struct listaItem ListaItem;         // linked list duplamente encadeada de itens


ListaItem*   criaListaItens     ();         
void         destruirListaItem (ListaItem*);
