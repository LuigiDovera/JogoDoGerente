//https://github.com/amirbawab/Hungarian-Algorithm/blob/master/Hungarian.java
//http://www.hungarianalgorithm.com/examplehungarianalgorithm.php

//Arquivo deve ser transformado em header
#include <locale.h>
#include "dados.h"
#include "ia.h"

#define TRUE 1
#define FALSE 0



int main() {

    setlocale(LC_ALL, "Portuguese");//adicionando acentua��o

    int opcaoMenu, opcaoIA, opcaoCenario;



    while(TRUE){
        system("cls");
        printf("Bem vindo ao Jogo da Atribui��o!\n");
        printf("    1 - JOGAR SOZINHO\n    2 - VERSUS\n    3 - I.A.\n    4 - RECORDE\n    5 - SAIR\n\n");
        scanf("%d", &opcaoMenu);

        if(opcaoMenu==1){
            while(TRUE){
                printf("Escolha uma Fase: 10, 20, 30, 50 ou 100.\n");
                scanf("%d", &opcaoCenario);
                if(opcaoCenario==10 || opcaoCenario==20 || opcaoCenario==30 || opcaoCenario==50 || opcaoCenario==100){
                    system("cls");
                    int ** mm = getCenario(opcaoCenario);
                    printf("F\\T ");
                    for(int i=1;i<=opcaoCenario;i++)
                        printf("%03d ", i);
                    printf("\n");

                    //printando a matriz do cenario
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

                    jo->resultado = 0;
                    for(int i=0; i<opcaoCenario; i++)
                        jo->atribuicoes[i] = -1;

                    for(int i=0; i<opcaoCenario; i++){
                        int BOOL;
                        do{
                            BOOL = FALSE;
                            printf("Atribua uma Tarefa ao Funcion�rio %d: ", i+1);
                            scanf("%d", &(jo->atribuicoes[i]));
                            jo->atribuicoes[i]--;
                            if(jo->atribuicoes[i]<0 || jo->atribuicoes[i]>=opcaoCenario){
                                printf("Essa tarefa n�o existe. Escolha novamente.\n");
                                BOOL = TRUE;
                                continue;
                            }
                            for(int j=0; j<i; j++){
                                if(jo->atribuicoes[j]==jo->atribuicoes[i]){
                                    printf("Voc� j� atribuiu essa Tarefa a outro Funcion�rio. Escolha novamente.\n");
                                    BOOL = TRUE;
                                    break;
                                }
                            }
                        }while(BOOL);
                    }
                    printf("\n");

                    for(int i=0; i<opcaoCenario; i++){
                        jo->resultado += mm[i][jo->atribuicoes[i]];
                    }

                    printf("Sua pontua��o: %d\n", jo->resultado);

                    Score p = getRecorde();

                    if(opcaoCenario==10 && jo->resultado<p.Score10)
                        p.Score10 = jo->resultado;
                    else if(opcaoCenario==20 && jo->resultado<p.Score20)
                        p.Score20 = jo->resultado;
                    else if(opcaoCenario==30 && jo->resultado<p.Score30)
                        p.Score30 = jo->resultado;
                    else if(opcaoCenario==50 && jo->resultado<p.Score50)
                        p.Score50 = jo->resultado;
                    else if(opcaoCenario==100 && jo->resultado<p.Score100)
                        p.Score100 = jo->resultado;

                    setRecorde(p);

                    system("pause");

                    freeIntMatriz(mm, opcaoCenario);
                    free(jo->atribuicoes);
                    free(jo);

                    break;
                }else{
                    printf("Op��o inv�lida. Escolha novamente.\n");
                    system("pause");
                    continue;
                }

            }
        }else if(opcaoMenu==2){
            int BOOL, rIa, rPlayer, **mm;
            Jogada joIa;
            do{
                BOOL = TRUE;
                printf("Escolha o n�vel de precis�o da IA: 1-Alto, 2-M�dio, 3-Baixo\n");
                scanf("%d", &opcaoIA);
                if(opcaoIA==1 || opcaoIA==2 || opcaoIA==3){
                    while(TRUE){
                        printf("Escolha uma Fase: 10, 20, 30 ou 50.\n");
                        scanf("%d", &opcaoCenario);
                        printf("\n");
                        if(opcaoCenario==10 || opcaoCenario==20 || opcaoCenario==30 || opcaoCenario==50 || opcaoCenario==100){
                            mm = getCenario(opcaoCenario);

                            joIa = jogadaAutomatica(mm, opcaoCenario, 1);
                            rIa = joIa.resultado;
                           
                            BOOL = FALSE;

                            freeIntMatriz(mm, opcaoCenario);
                            free(joIa.atribuicoes);

                            break;
                        }else{
                            printf("Op��o inv�lida. Escolha novamente.\n");
                            system("pause");
                            continue;
                        }
                    }
                }else{
                    printf("Op��o inv�lida. Escolha novamente.\n");
                    system("pause");
                    continue;
                }
            }while(BOOL);

            while(TRUE){
                //printf("Escolha uma Fase: 10, 20, 30 ou 50.\n");
                //scanf("%d", &opcaoCenario);
                if(opcaoCenario==10 || opcaoCenario==20 || opcaoCenario==30 || opcaoCenario==50 || opcaoCenario==100){
                    system("cls");
                    mm = getCenario(opcaoCenario);
                    printf("F\\T ");
                    for(int i=1;i<=opcaoCenario;i++)
                        printf("%03d ", i);
                    printf("\n");

                    //printando a matriz do cenario
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

                    jo->resultado = 0;
                    for(int i=0; i<opcaoCenario; i++)
                        jo->atribuicoes[i] = -1;

                    for(int i=0; i<opcaoCenario; i++){
                        int BOOL;
                        do{
                            BOOL = FALSE;
                            printf("Atribua uma Tarefa ao Funcion�rio %d: ", i+1);
                            scanf("%d", &(jo->atribuicoes[i]));
                            jo->atribuicoes[i]--;
                            if(jo->atribuicoes[i]<0 || jo->atribuicoes[i]>=opcaoCenario){
                                printf("Essa tarefa n�o existe. Escolha novamente.\n");
                                BOOL = TRUE;
                                continue;
                            }
                            for(int j=0; j<i; j++){
                                if(jo->atribuicoes[j]==jo->atribuicoes[i]){
                                    printf("Voc� j� atribuiu essa Tarefa a outro Funcion�rio. Escolha novamente.\n");
                                    BOOL = TRUE;
                                    break;
                                }
                            }
                        }while(BOOL);
                    }
                    printf("\n");

                    for(int i=0; i<opcaoCenario; i++){
                        jo->resultado += mm[i][jo->atribuicoes[i]];
                    }
                    rPlayer = jo->resultado;

                    printf("Sua pontua��o: %d\n", rPlayer);
                    printf("Pontuação da IA: %d\n", rIa);

                    if(rIa < rPlayer)
                        printf("Você perdeu\n");
                    else if(rIa > rPlayer)
                        printf("Você venceu\n");
                    else
                        printf("Empate\n");
                    
                    system("pause");

                    freeIntMatriz(mm, opcaoCenario);
                    free(jo->atribuicoes);
                    free(jo);
                    free(joIa.atribuicoes);

                    break;
                }else{
                    printf("Op��o inv�lida. Escolha novamente.\n");
                    system("pause");
                    continue;
                }

            }
        }else if(opcaoMenu==3){
            int BOOL;
            do{
                BOOL = TRUE;
                printf("Escolha o n�vel de precis�o da IA: 1-Alto, 2-M�dio, 3-Baixo\n");
                scanf("%d", &opcaoIA);
                if(opcaoIA==1 || opcaoIA==2 || opcaoIA==3){
                    while(TRUE){
                        printf("Escolha uma Fase: 10, 20, 30 ou 50.\n");
                        scanf("%d", &opcaoCenario);
                        printf("\n");
                        if(opcaoCenario==10 || opcaoCenario==20 || opcaoCenario==30 || opcaoCenario==50){
                            int ** mm = getCenario(opcaoCenario);

                            Jogada jo = jogadaAutomatica(mm, opcaoCenario, 1);
                            printf("Pontua��o da IA: %d\n", jo.resultado);
                            for(int i=0; i < opcaoCenario; i++)
                                printf("F%d-T%d ", i+1,jo.atribuicoes[i]);
                            printf("\n");
                            system("pause");
                            BOOL = FALSE;

                            freeIntMatriz(mm, opcaoCenario);
                            free(jo.atribuicoes);

                            break;
                        }else{
                            printf("Op��o inv�lida. Escolha novamente.\n");
                            system("pause");
                            continue;
                        }
                    }
                }else{
                    printf("Op��o inv�lida. Escolha novamente.\n");
                    system("pause");
                    continue;
                }
            }while(BOOL);

        }else if(opcaoMenu==4){
            Score p = getRecorde();
            printf("Melhor pontua��o no cen�rio 10: %d\n", p.Score10);
            printf("Melhor pontua��o no cen�rio 20: %d\n", p.Score20);
            printf("Melhor pontua��o no cen�rio 30: %d\n", p.Score30);
            printf("Melhor pontua��o no cen�rio 50: %d\n", p.Score50);
            printf("Melhor pontua��o no cen�rio 100: %d\n", p.Score100);
            system("pause");

        }else if(opcaoMenu==5){
            break;
        }else{
            printf("Op��o inv�lida. Escolha novamente.\n");
            system("pause");
            continue;
        }
    }


    return 0;
}
