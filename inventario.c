#include "inventario.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>


struct inventario{
    ListaItem* itens;
};


Inventario* criarInventario(){
    Inventario* inventario = (Inventario*)malloc(sizeof(Inventario));
    inventario->itens = criaListaItens();
    return inventario;
}

void destruirInventario(Inventario* inventario){
    if(inventario == NULL){ 
        return;
    }
    if(inventario->itens != NULL){
        destruirListaItem(inventario->itens);
    }

    free(inventario);
}
