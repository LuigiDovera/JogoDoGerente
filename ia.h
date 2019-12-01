#define TRUE 1
#define FALSE 0

int _tamanho;

typedef struct
{
    int resultado, *atribuicoes;
}Jogada;

int** alocaMatrizQuadrada(int tamanho) {
    int **ptrM=NULL, i;
    ptrM = (int**)malloc(tamanho * sizeof(int*));
    if(ptrM == NULL) {
        printf("Erro_5");
        return alocaMatrizQuadrada(tamanho);
    }
    for(i=0; i < tamanho; i++) {
        ptrM[i] = (int*)malloc(tamanho * sizeof(int));
        if(ptrM[i] == NULL) {
            printf("Erro_5");
            return alocaMatrizQuadrada(tamanho);
        }
    }
    return ptrM;
}

void copiaMatriz(int**, int**);
void subtraiMinimoLinha(int**);
void subtraiMinimoColuna(int**);
int** cobreZeros(int**, int*);
int direcao(int**, int, int);
void coloreVizinhos(int**, int**, int*, int, int, int);
void criaZerosExtras(int**, int **);
int otimiza(int**, int*, int*, int);

Jogada jogadaAutomatica(int **matrizOriginal, int tamanho, int nivel)
{
    _tamanho = tamanho;
    Jogada jogada = {.resultado = -1, .atribuicoes = NULL};
    int **valores = alocaMatrizQuadrada(_tamanho);
    int aux0=0, aux1;
    int *numLinhas = &aux0;
    int **retas = alocaMatrizQuadrada(_tamanho);
    int linhas[_tamanho], colunasOcupadas[_tamanho];

    jogada.atribuicoes = (int*)malloc(_tamanho * sizeof(int));
    if(jogada.atribuicoes == NULL) {
        printf("Erro_4");
        return jogada;
    }
    copiaMatriz(valores, matrizOriginal);
    printf("aaaa");
    subtraiMinimoLinha(valores);
    subtraiMinimoColuna(valores);
    copiaMatriz(retas, cobreZeros(valores, numLinhas));
    while(*numLinhas < _tamanho) {
        criaZerosExtras(valores, retas);
        copiaMatriz(retas, cobreZeros(valores, numLinhas));
    }
    otimiza(valores, linhas, colunasOcupadas, 0);
    
    jogada.atribuicoes = linhas;
    for(aux1=0; aux1 < _tamanho; aux1++) {
        jogada.resultado += matrizOriginal[aux1][linhas[aux1]];
    }
    free(retas);
    free(valores);
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

void subtraiMinimoLinha(int **matriz)
{
    int menores[_tamanho], i, j;
    for(i=0; i < _tamanho; i++) {
        menores[i] = matriz[i][0];
        for(j=1; j < _tamanho; j++) {
            if(matriz[i][j] < menores[i])
                menores[i] = matriz[i][j];
        }
    }

    for(i=0; i < _tamanho; i++) {
        for(j=0; j < _tamanho; j++) {
            matriz[i][j] -= menores[i];
        }
    }
}

void subtraiMinimoColuna(int **matriz)
{
    int menores[_tamanho], i, j;
    for(j=0; j < _tamanho; j++) {
        menores[j] = matriz[0][j];
        for(i=1; i < _tamanho; i++) {
            if(matriz[i][j] < menores[j])
                menores[j] = matriz[i][j];
        }
    }

    for(j=0; j < _tamanho; j++) {
        for(i=0; i < _tamanho; i++) {
            matriz[i][j] -= menores[j];
        }
    }
}

int** cobreZeros(int **matriz, int *numLinhas)
{
    int **retas= alocaMatrizQuadrada(_tamanho), i, j;

    *numLinhas = 0;
    for(i=0; i < _tamanho; i++) {
        for(j=0; j < _tamanho; j++) {
            if(matriz[i][j] == 0)
                coloreVizinhos(matriz, retas, numLinhas, i, j, direcao(matriz, i, j));
        }
    }
    return retas;
}

int direcao(int **matriz, int linha, int coluna)
{
    int resultado=0, i;
    for(i=0; i < _tamanho; i++) {
        if(matriz[i][coluna] == 0)
            resultado++;
        if(matriz[linha][i] == 0)
            resultado--;
    }
    return resultado;
}

void coloreVizinhos(int **matriz, int **retas, int *numLinhas, int linha, int coluna, int direcao)
{
    int i;

    if(retas[linha][coluna] == 2)
        return;
    if(direcao > 0 && retas[linha][coluna] == 1)
        return;
    if(direcao <= 0 && retas[linha][coluna] == -1)
        return;

    for(i=0; i < _tamanho; i++) {
        if(direcao > 0)
            retas[i][coluna] = retas[i][coluna] == -1 || retas[i][coluna] == 2 ? 2 : 1;
        else
            retas[linha][i] = retas[linha][i] == 1 || retas[linha][i] == 2 ? 2 : -1;
    }
    *numLinhas++;
}

void criaZerosExtras(int** matriz, int **retas)
{
    int minNaoCoberto=0, i, j;

    for(i=0; i < _tamanho; i++) {
        for(j=0; j < _tamanho; j++) {
            if(retas[i][j] == 0 && (matriz[i][j] < minNaoCoberto || minNaoCoberto == 0))
                minNaoCoberto = matriz[i][j];
        }
    }

    for(i=0; i < _tamanho; i++) {
        for(j=0; j < _tamanho; j++) {
            if(retas[i][j] == 0)
                matriz[i][j] -= minNaoCoberto;
            else if(retas[i][j] == 2)
                matriz[i][j] += minNaoCoberto;
        }
    }
}

int otimiza(int **matriz, int *linhas, int *colunasOcupadas, int linha)
{
    int j;

    if(linha == sizeof(linhas)/sizeof(int))
        return TRUE;

    for(j=0; j < _tamanho; j++) {
        if(matriz[linha][j] == 0 && colunasOcupadas[j] == 0) {
            linhas[linha] = j;
            colunasOcupadas[j] = 1;
            if(otimiza(matriz, linhas, colunasOcupadas, linha+1))
                return TRUE;
            colunasOcupadas[j] = 0;
        }
    }
    return FALSE;
}