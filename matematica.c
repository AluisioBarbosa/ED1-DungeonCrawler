#include "matematica.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>


void instanciarSemente(){
    srand(time(NULL));
}

int gerarNumeroAleatorio(int minimo, int maximo){
    int numeroAleatorio;

    numeroAleatorio = (rand() % (maximo - minimo + 1)) + minimo; // gera um numero aleatorio entre o minimo e o maximo
    return numeroAleatorio;
}

int calculaDano(int dano, int armadura){
    int danoRecebido;
    danoRecebido = dano - (int)round(armadura * 0.4); // O dano recebido sera o dano do inimigo menos o arredondamento da armadura do player * 0.4

    return danoRecebido;
}