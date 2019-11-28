//Arquivo deve ser transformado em header
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int* minimo(int**, int, int);

int main() 
{


    return 0;
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