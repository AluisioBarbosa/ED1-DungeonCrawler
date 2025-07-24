#include "inventario.h"
#include "item.h"
#include <stdio.h>
#include "ansi.h"
#include "log.h"
#include <stdlib.h>
#include <windows.h>


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
        logToFile("Destruindo inventario");
        destruirListaItem(inventario->itens);
    }

    free(inventario);
}

void adicionarNoInventario(Inventario* inventario, Item* item){
    logToFile("Inserindo item no inventario");
    inserirItem(inventario->itens, item);
}

int tamanhoInventario(Inventario* inventario){
    return getQuantidadeItem(inventario->itens);
}

void inventarioHUD(Inventario* inventario, int posicaoAtual){
    system("cls");
    printf("------------------------------------<%d/%d>------------------------------------\n", posicaoAtual + 1 ,tamanhoInventario(inventario));
    printf("%s\n", getItemNome(buscarItemPorIndice(inventario->itens, posicaoAtual)));
    imprimirArte(getItemID(buscarItemPorIndice(inventario->itens, posicaoAtual)));
    printf("%s\n", getItemDescricao((buscarItemPorIndice(inventario->itens, posicaoAtual))));
    printf("\n\n");
    printf(TEXTO_AMARELO"[A] "RESET"" "ou " TEXTO_AMARELO"[D] "RESET"" "para percorrer o inventario\n");
    printf(TEXTO_AMARELO"[P] "RESET"" "para utilizar o item\n");
    printf(TEXTO_AMARELO"[O] "RESET"" "para destruir o item\n");
    printf(TEXTO_AMARELO"[I] "RESET"" "para sair do inventario\n");
}

Item* inventarioLoop(Inventario* inventario, int GAME_STATE){
    int posicaoAtual = 0;
    if(inventario->itens == NULL || inventario == NULL || tamanhoInventario(inventario) <= 0 ){
        logWarn("Nao ha itens no seu inventario");
        Sleep(1000);
        return NULL;
    }
    inventarioHUD(inventario, posicaoAtual);

    while(tamanhoInventario(inventario) > 0){
        if(inventario->itens == NULL || inventario == NULL || tamanhoInventario(inventario) <= 0 ){ // é necessario checar novamente pois ao utilizar a posicao do inventario pode ficar negativa
            logWarn("Nao ha itens no seu inventario");
            Sleep(1000);
            return NULL;
        }

        if (GetAsyncKeyState('A') & 0x8000){
            if(posicaoAtual == 0){
                posicaoAtual = 0;
                logWarn("Nao e possivel acessar posicoes negativas do inventario");
            }
            else{
                posicaoAtual--;
                inventarioHUD(inventario, posicaoAtual);
            }
            Sleep(200);
        }
        else if(GetAsyncKeyState('D') & 0x8000){
            if(posicaoAtual >= tamanhoInventario(inventario) - 1){
                posicaoAtual = tamanhoInventario(inventario) - 1;
                logWarn("Nao e possivel acessar posicoes acima do tamanho do inventario");
            }
            else{
                posicaoAtual++;
                inventarioHUD(inventario, posicaoAtual);
            }
            Sleep(200);
        }
        else if (GetAsyncKeyState('O') & 0x8000){
            removerItem(inventario->itens, buscarItemPorIndice(inventario->itens, posicaoAtual));
            if (posicaoAtual >= tamanhoInventario(inventario)) { // isso aqui é pra caso remover e ficar out of bonds, ele arruma
                if (posicaoAtual > 0){ 
                    posicaoAtual--;
                }
                else{
                    posicaoAtual = 0;
                }
            }
            if (tamanhoInventario(inventario) > 0) {
                inventarioHUD(inventario, posicaoAtual);
            } 
            else{
                logWarn("Inventario vazio apos remocao");
                return NULL;
            }
            inventarioHUD(inventario, posicaoAtual);
            Sleep(200);
        }
        else if(GetAsyncKeyState('P') & 0x8000){
            if(GAME_STATE == 2){ // se tiver no combate da pra usar todos os itens
                return buscarItemPorIndice(inventario->itens, posicaoAtual);
            }
            if(GAME_STATE == 3 && getItemID(buscarItemPorIndice(inventario->itens, posicaoAtual)) == 1){ // no mapa mundo só da pra usar a poçao
                return buscarItemPorIndice(inventario->itens, posicaoAtual);
            }
            else{
                logWarn("So e possivel utilizar a pocao fora de batalha!!!");
            }

            Sleep(200);
        }
        else if(GetAsyncKeyState('I') & 0x8000){
            logInfo("Saindo do inventario");
            return NULL;
        }
    }

    return NULL; // Só pra garantir que se der alguma coisa errada dentro da função ele retorne alguma coisa coerente
}

ListaItem* getInventarioLista(Inventario* inventario){
    return inventario->itens;
}