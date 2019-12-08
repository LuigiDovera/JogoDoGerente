//https://github.com/amirbawab/Hungarian-Algorithm/blob/master/Hungarian.java
//http://www.hungarianalgorithm.com/examplehungarianalgorithm.php

//Arquivo deve ser transformado em header
#include <locale.h>
#include "dados.h"
#include "ia.h"


int main() {
    /*int opcaoMenu, opcaoJogador, opcaoCenario;
    setlocale(LC_ALL, "Portuguese");
    printf("Bem vindo ao Jogo da Atribui��o!\n")
    //printf("Quem vai jogar?\n   1 - Eu\n  2 - I.A.\n")
    printf("    1 - JOGAR\n    ")
    scanf("%d", &opcaoMenu);

    while(1){
        if(opcao==1){

        }else if(opcao==2){

        }else{
            printf()
        }
    }

    printf("");
    */
    //adicionando acentua��o
    /*int **m = alocaMatrizQuadrada(4);
    m[0][0] = 82;
    m[0][1] = 83;
    m[0][2] = 69;
    m[0][3] = 92;
    m[1][0] = 77;
    m[1][1] = 37;
    m[1][2] = 49;
    m[1][3] = 92;
    m[2][0] = 11;
    m[2][1] = 69;
    m[2][2] = 5;
    m[2][3] = 86;
    m[3][0] = 8;
    m[3][1] = 9;
    m[3][2] = 98;
    m[3][3] = 23;
    Jogada jo;
    jo = jogadaAutomatica(m, 4, 1);
    printf("%d\n", jo.resultado);
    for(int i=0; i < 4; i++) {
        printf("%d ", jo.atribuicoes[i]);
    }*/

    int ** mm = getCenario(50), i;

    Jogada jo = jogadaAutomatica(mm, 50, 1);
    printf("%d\n", jo.resultado);
    for( i=0; i < 50; i++) {
        printf("%d ", jo.atribuicoes[i]);
    }
}
