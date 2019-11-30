#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    int resultado, *atribuicoes;
}Jogada;

void copiaMatriz(int**, int**);

Jogada jogadaAutomatica(int *matriz, int tamanho, int nivel)
{
    Jogada jogada = {.resultado = -1, .atribuicoes = NULL};
    int valores[tamanho][tamanho];
    int aux0=0;
    int *numLinhas = &aux0;

    jogada.atribuicoes = (int*)malloc(tamanho * sizeof(int));
    if(jogada.atribuicoes == NULL) {
        printf("Erro_4");
        return jogada;
    }
    copiaMatriz(valores, matriz);

    subtraiMinimoLinha();
    subtraiMinimoColuna();
    cobreZeros();
    while(*numLinhas < tamanho) {
        criaZerosExtras();
        cobreZeros();
    }
    otimiza();
    return jogada; 
}

void copiaMatriz(int **destino, int **origem)
{
    int i, j;
    for(i=0; i < sizeof(origem[0])/sizeof(int); i++) {
        for(j=0; j < sizeof(origem[0])/sizeof(int); j++) {
            destino[i][j] = origem[i][j];
        }
    }
}