#include "inventario.h"
#include "item.h"
#include <stdio.h>
#include "log.h"
#include <stdlib.h>


struct inventario{
    ListaItem* itens;
};


Inventario* criarInventario(){
    Inventario* inventario = (Inventario*)malloc(sizeof(Inventario));
    if(inventario == NULL){
        logError("Erro na alocação de memoria para o inventario");
        exit(1);
    }
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

void adicionarNoInventario(Inventario* inventario, Item* item){
    inserirItem(inventario->itens, item);
}