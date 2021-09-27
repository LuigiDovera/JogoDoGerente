#include <stdio.h>
#include <stdlib.h>

#define MAX 999999999
#define cenario10 "cenario/atribuicao_10.txt"
#define cenario20 "cenario/atribuicao_20.txt"
#define cenario30 "cenario/atribuicao_30.txt"
#define cenario50 "cenario/atribuicao_50.txt"
#define cenario100 "cenario/atribuicao_100.txt"

typedef struct{
	int Score10;
	int Score20;
	int Score30;
	int Score50;
	int Score100;
}Score;

Score  getRecorde(){
    FILE *pLeitura = fopen("score.txt", "r");
	Score p;
    if (pLeitura != NULL){
			fscanf(pLeitura, "%d", &p.Score10);
			fscanf(pLeitura, "%d", &p.Score20);
			fscanf(pLeitura, "%d", &p.Score30);
			fscanf(pLeitura, "%d", &p.Score50);
			fscanf(pLeitura, "%d", &p.Score100);
			fclose(pLeitura);
            return p;
		}else{
			printf("\nERRO\n");
			fclose(pLeitura);
			return;
		}
}

void setRecorde(Score p){
	FILE *pEscrita = fopen("score.txt","w");
	if (pEscrita != NULL){
		fprintf(pEscrita, "%d\n", p.Score10);
		fprintf(pEscrita, "%d\n", p.Score20);
		fprintf(pEscrita, "%d\n", p.Score30);
		fprintf(pEscrita, "%d\n", p.Score50);
		fprintf(pEscrita, "%d\n", p.Score100);
	}else{
		printf("\nERRO\n");
	}
	fclose(pEscrita);
}

int ** getCenario(int cenario){
	int cen;

	int **Matriz = (int**)malloc(cenario*sizeof(int)*2);
	for (int i  = 0; i < cenario; i++ )
		*(Matriz + i) = (int*)malloc(cenario*sizeof(int));

    if (cenario == 10){
        FILE * pLeitura = fopen(cenario10, "r");
        if (pLeitura != NULL){
        fscanf(pLeitura, "%d", &cen);
        for (int i=0;i<10;i++){
            for (int j=0;j<10;j++){
                fscanf(pLeitura, "%d", &Matriz[i][j]);
            }// for i
        }// for j
        fclose(pLeitura);
        }else printf("\nERRO NO PONTEIRO DE ARQUIVO DO CENARIO 10\n");

    }else if (cenario == 20){
        FILE * pLeitura = fopen(cenario20, "r");
        if (pLeitura != NULL){
        fscanf(pLeitura, "%d", &cen);
        for (int i=0;i<20;i++){
            for (int j=0;j<20;j++){
                fscanf(pLeitura, "%d", &Matriz[i][j]);
            }// for i
        }// for j
        fclose(pLeitura);
        }else printf("\nERRO NO PONTEIRO DE ARQUIVO DO CENARIO 20\n");


    }else if (cenario == 30){
        FILE * pLeitura = fopen(cenario30, "r");
        if (pLeitura != NULL){
        fscanf(pLeitura, "%d", &cen);
        for (int i=0;i<30;i++){
            for (int j=0;j<30;j++){
                fscanf(pLeitura, "%d", &Matriz[i][j]);
            }// for i
        }// for j
        fclose(pLeitura);
        }else printf("\nERRO NO PONTEIRO DE ARQUIVO DO CENARIO 30\n");

    }else if (cenario == 50){
        FILE * pLeitura = fopen(cenario50, "r");
        if (pLeitura != NULL){
        fscanf(pLeitura, "%d", &cen);
        for (int i=0;i<50;i++){
            for (int j=0;j<50;j++){
                fscanf(pLeitura, "%d", &Matriz[i][j]);
            }// for i
        }// for j
        fclose(pLeitura);
        }else printf("\nERRO NO PONTEIRO DE ARQUIVO DO CENARIO 50\n");

    }else if(cenario == 100){
        FILE * pLeitura = fopen(cenario100, "r");
        if (pLeitura != NULL){
        fscanf(pLeitura, "%d", &cen);
        for (int i=0;i<100;i++){
            for (int j=0;j<100;j++){
                fscanf(pLeitura, "%d", &Matriz[i][j]);
            }// for i
        }// for j

        fclose(pLeitura);
        }else printf("\nERRO NO PONTEIRO DE ARQUIVO DO CENARIO 100\n");

    }else{
        printf("\nVALOR INFORMADO INVALIDO\n");
    }

    return Matriz;
}

void freeIntMatriz(int **mat, int tam){
    for(int i=0; i<tam; i++)
        free(mat[i]);
    free(mat);
}
