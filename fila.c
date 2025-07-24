#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ansi.h"
#include "fila.h"
#include "log.h"

#define TAM_MAX_FILA 5

typedef struct cel {
    char valor[128];
    struct cel* proximo;
} Celula;

struct fila {
    Celula* inicio;
    Celula* fim;
    int tamanho;
};

Fila* criarFila() {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    if (f == NULL) {
        logError("Erro na hora de alocar memória para a fila");
        exit(1);
    }
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
    return f;
}

bool isFilaEmpty(Fila* f) {
    if(f->inicio == NULL){
        return true;
    }
    return false;
}

void imprimirFila(Fila* f) {
    Celula* cel = f->inicio;
    printf(TEXTO_CIANO"\n[LOG DE BATALHA]\n"RESET"");
    while (cel != NULL) {
        printf("%s\n", cel->valor);
        cel = cel->proximo;
    }
}

void removerPrimeiro(Fila* f) {
    if (f->inicio == NULL){
        return;
    }

    Celula* cel = f->inicio;
    f->inicio = f->inicio->proximo;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    free(cel);
    f->tamanho--;
}

void enfileirar(Fila* f, const char* texto) {
    if (f->tamanho >= TAM_MAX_FILA) {
        removerPrimeiro(f); // remove o primeiro da fila
    }

    Celula* cel = (Celula*)malloc(sizeof(Celula));
    if (cel == NULL) {
        logError("Erro na alocação de memória para célula da fila");
        exit(1);
    }

    const char* hora = horaAtualFormatada();
    snprintf(cel->valor, sizeof(cel->valor), "%s %s", hora, texto);

    cel->proximo = NULL;

    if (f->fim != NULL) {
        f->fim->proximo = cel;
    } else {
        f->inicio = cel;
    }

    f->fim = cel;
    f->tamanho++;
}

char* desenfileirar(Fila* f) {
    if (f->inicio == NULL) {
        logWarn("A fila está vazia");
        return NULL;
    }

    Celula* cel = f->inicio;
    char* valor = (char*)malloc(strlen(cel->valor) + 1);
    if (valor == NULL) {
        logError("Erro ao alocar memória para retorno de desenfileirar");
        exit(1);
    }

    strcpy(valor, cel->valor);
    f->inicio = f->inicio->proximo;

    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    free(cel);
    f->tamanho--;
    return valor;
}

int filaSize(Fila* f) {
    return f->tamanho;
}
void destruirFila(Fila* f) {
    if (f == NULL){
        return;
    }

    while (f->inicio != NULL) {
        removerPrimeiro(f);
    }

    free(f);
}

void esvaziarFila(Fila* f) {
    while (f != NULL && f->inicio != NULL) {
        removerPrimeiro(f);
    }
}