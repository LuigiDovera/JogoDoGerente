//https://github.com/amirbawab/Hungarian-Algorithm/blob/master/Hungarian.java
//http://www.hungarianalgorithm.com/examplehungarianalgorithm.php

//Arquivo deve ser transformado em header
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int _tamanho, _numeroLinhas;

typedef struct
{
    int resultado, *atribuicoes;
}Jogada;

Jogada jogadaAutomatica(int **matrizOriginal, int tamanho, int nivel) 
{
    Jogada jogada = {.resultado = -1, .atribuicoes = NULL};
    jogada.atribuicoes = (int*)malloc(tamanho * sizeof(int));
    if(jogada.atribuicoes == NULL) {
        printf("Erro_4");
        return jogada;
    }

    int tabela[tamanho][tamanho];
    memcpy(tabela, matrizOriginal, tamanho*tamanho*sizeof(int));
}

int* minimo(int **matriz, int tamanho, int modo)
{
    int i, j, *menor=NULL;

    menor = (int*)malloc(tamanho*sizeof(int));
    if(menor == NULL) {
        printf("Erro_1\n");
        return menor;
    }
    for(i=0; i < tamanho; i++) menor[i] = -1;
    switch (modo)
    {
    //Menor da linha
    case 1:
        for(i=0; i < tamanho; i++) {
            for (j=0; j < tamanho; j++) {
                if(menor[i] > matriz[i][j]) menor[i] = matriz[i][j];
            }
        }
        break;
    //Menor da coluna
    case 2:
        for(i=0; i < tamanho; i++) {
            for (j=0; j < tamanho; j++) {
                if(menor[i] > matriz[j][i]) menor[i] = matriz[j][i];
            }
        }
        break;
    
    default:
        printf("Erro_2\n");
        menor = NULL;
        return menor;
        break;
    }
    for(i=0; i < tamanho; i++) {
        if(menor[i] == -1) { 
            printf("Erro_3\n");
            menor=NULL;
            return menor;
        }
    }
    return menor;
}