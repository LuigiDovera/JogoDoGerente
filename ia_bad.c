//https://github.com/amirbawab/Hungarian-Algorithm/blob/master/Hungarian.java
//http://www.hungarianalgorithm.com/examplehungarianalgorithm.php

//Arquivo deve ser transformado em header
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ia.h"

int main() {
    int **m = alocaMatrizQuadrada(4);
    m[1][1] = 82;
    m[1][2] = 83;
    m[1][3] = 69;
    m[1][4] = 92;
    m[2][1] = 77;
    m[2][2] = 37;
    m[2][3] = 49;
    m[2][4] = 92;
    m[3][1] = 11;
    m[3][2] = 69;
    m[3][3] = 5;
    m[3][4] = 86;
    m[4][1] = 8;
    m[4][2] = 9;
    m[4][3] = 98;
    m[4][4] = 23;
    Jogada jo;
    printf("aaaa");
    jo = jogadaAutomatica(m, 4, 1);
    printf("%d", jo.resultado);
    for(int i=0; i < 4; i++) {
        printf("%d", jo.atribuicoes[i]);
    }
}