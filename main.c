//https://github.com/amirbawab/Hungarian-Algorithm/blob/master/Hungarian.java
//http://www.hungarianalgorithm.com/examplehungarianalgorithm.php

//Arquivo deve ser transformado em header
#include <locale.h>
#include "dados.h"
#include "ia.h"


int main() {

    setlocale(LC_ALL, "Portuguese");//adicionando acentuação

    int opcaoMenu, opcaoJogador, opcaoCenario;



    while(1){
        system("cls");
        printf("Bem vindo ao Jogo da Atribuição!\n");
        //printf("Quem vai jogar?\n   1 - Eu\n  2 - I.A.\n");
        printf("    1 - JOGAR\n    2 - I.A.\n    3 - SAIR\n\n");
        scanf("%d", &opcaoMenu);

        if(opcaoMenu==1){
            while(1){
                printf("Escolha uma Fase: 10, 20, 30 ou 50.\n");
                scanf("%d", &opcaoCenario);
                if(opcaoCenario==10 || opcaoCenario==20 || opcaoCenario==30 || opcaoCenario==50){
                    system("cls");
                    int ** mm = getCenario(opcaoCenario);
                    printf("F\\T ");
                    for(int i=1;i<=opcaoCenario;i++)
                        printf("%03d ", i);
                    printf("\n");
                    for(int i=0; i<opcaoCenario; i++){
                        printf("%03d ", i+1);

                        for(int j=0; j<opcaoCenario; j++){
                            printf("%03d ", mm[i][j]);
                        }
                        printf("\n");

                    }
                    printf("\n");

                    Jogada *jo = (Jogada*)malloc(sizeof(Jogada));
                    jo->atribuicoes = (int*)malloc(sizeof(int)*opcaoCenario);

                    system("pause");
                    free(mm);
                    break;
                }else{
                    printf("Opção inválida. Escolha novamente.\n");
                    system("pause");
                    continue;
                }

            }
        }else if(opcaoMenu==2){

        }else if(opcaoMenu==3){
            break;
        }else{
            printf("Opção inválida. Escolha novamente.\n");
            system("pause");
            continue;
        }
    }



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
    /*
    int cennnn = 10;
    int ** mm = getCenario(cennnn);

    Jogada jo = jogadaAutomatica(mm, cennnn, 1);
    printf("%d\n", jo.resultado);
    for(int i=0; i < cennnn; i++) {
        printf("%d ", jo.atribuicoes[i]);
    for(int i=0; i < cennnn; i++)
        free(mm[i]);
    free(mm);
    }
    */
}
