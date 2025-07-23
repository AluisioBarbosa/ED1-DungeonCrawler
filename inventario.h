#include "item.h"

typedef struct inventario Inventario;

Inventario*         criarInventario             ();                 //Função para criar o inventario
void                destruirInventario          (Inventario*);      //Função para destruir o inventario (usado em casos de GameOver)
void adicionarNoInventario(Inventario* , Item*);
