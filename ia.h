#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

int _tamanho;
int **_valores = NULL;
int _numRetas;
int **_retas = NULL;
int *_linhas = NULL;
int *_colunasOcupadas = NULL;

typedef struct{
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
            printf("Erro_6");
            return alocaMatrizQuadrada(tamanho);
        }
    }
    return ptrM;
}

int* alocaVetor(int tamanho) {
    int *ptrV=NULL, i;
    ptrV = (int*)malloc(tamanho * sizeof(int));
    if(ptrV == NULL) {
        printf("Erro_7");
        return alocaVetor(tamanho);
    }
    return ptrV;
}

void copiaMatriz(int**, int**);
void subtraiMinimoLinha();
void subtraiMinimoColuna();
void cobreZeros();
int direcao(int, int);
void coloreVizinhos(int, int, int);
void criaZerosExtras();
int otimiza(int);
void geraErro(int);

Jogada jogadaAutomatica(int **matrizOriginal, int tamanho, int nivel)
{
    int i;

    _tamanho = tamanho;
    Jogada jogada = {.resultado = -1, .atribuicoes = NULL};
    jogada.atribuicoes = (int*)malloc(_tamanho * sizeof(int));
    if(jogada.atribuicoes == NULL) {
        printf("Erro_4");
        return jogada;
    }
    _valores = alocaMatrizQuadrada(_tamanho);
    _numRetas = 0;
    _linhas = alocaVetor(_tamanho);
    _colunasOcupadas = alocaVetor(_tamanho);
    for(i=0; i < _tamanho; i++) {
        _colunasOcupadas[i] = 0;
    }

    copiaMatriz(_valores, matrizOriginal);
    subtraiMinimoLinha();
    subtraiMinimoColuna();
    cobreZeros();
    while(_numRetas < _tamanho) {
        criaZerosExtras();
        cobreZeros();
    }
    otimiza(0);

    geraErro(nivel);

    jogada.atribuicoes = _linhas;
    for(i=0; i < _tamanho; i++) {
        jogada.resultado += matrizOriginal[i][_linhas[i]];
    }
    jogada.resultado++;

    for(i=0; i < _tamanho; i++) {
        free(_retas[i]);
        free(_valores[i]);
    }
    free(_retas);
    free(_valores);
    free(_colunasOcupadas);
    return jogada;
}

void copiaMatriz(int **destino, int **origem)
{
    int i, j;
    for(i=0; i < _tamanho; i++) {
        for(j=0; j < _tamanho; j++) {
            destino[i][j] = origem[i][j];
        }
    }
}

void subtraiMinimoLinha()
{
    int menores[_tamanho], i, j;
    for(i=0; i < _tamanho; i++) {
        menores[i] = _valores[i][0];
        for(j=1; j < _tamanho; j++) {
            if(_valores[i][j] < menores[i])
                menores[i] = _valores[i][j];
        }
    }

    for(i=0; i < _tamanho; i++) {
        for(j=0; j < _tamanho; j++) {
            _valores[i][j] -= menores[i];
        }
    }
}

void subtraiMinimoColuna()
{
    int menores[_tamanho], i, j;
    for(j=0; j < _tamanho; j++) {
        menores[j] = _valores[0][j];
        for(i=1; i < _tamanho; i++) {
            if(_valores[i][j] < menores[j])
                menores[j] = _valores[i][j];
        }
    }

    for(j=0; j < _tamanho; j++) {
        for(i=0; i < _tamanho; i++) {
            _valores[i][j] -= menores[j];
        }
    }
}

void cobreZeros()
{
    int i, j;

    _numRetas = 0;
    if(_retas != NULL) {
        free(_retas);
        _retas = NULL;
    }
    _retas = alocaMatrizQuadrada(_tamanho);
    for(i=0; i < _tamanho; i++) {
        for(j=0; j < _tamanho; j++) {
            if(_valores[i][j] == 0)
                coloreVizinhos(i, j, direcao(i, j));
        }
    }
}

int direcao(int linha, int coluna)
{
    int resultado=0, i;
    for(i=0; i < _tamanho; i++) {
        if(_valores[i][coluna] == 0)
            resultado++;
        if(_valores[linha][i] == 0)
            resultado--;
    }
    return resultado;
}

void coloreVizinhos(int linha, int coluna, int direcao)
{
    int i;

    if(_retas[linha][coluna] == 2)
        return;
    if(direcao > 0 && _retas[linha][coluna] == 1)
        return;
    if(direcao <= 0 && _retas[linha][coluna] == -1)
        return;

    for(i=0; i < _tamanho; i++) {
        if(direcao > 0)
            _retas[i][coluna] = _retas[i][coluna] == -1 || _retas[i][coluna] == 2 ? 2 : 1;
        else
            _retas[linha][i] = _retas[linha][i] == 1 || _retas[linha][i] == 2 ? 2 : -1;
    }
    _numRetas++;
}

void criaZerosExtras()
{
    int minNaoCoberto=0, i, j;

    for(i=0; i < _tamanho; i++) {
        for(j=0; j < _tamanho; j++) {
            if(_retas[i][j] == 0 && (_valores[i][j] < minNaoCoberto || minNaoCoberto == 0))
                minNaoCoberto = _valores[i][j];
        }
    }

    for(i=0; i < _tamanho; i++) {
        for(j=0; j < _tamanho; j++) {
            if(_retas[i][j] == 0)
                _valores[i][j] -= minNaoCoberto;
            else if(_retas[i][j] == 2)
                _valores[i][j] += minNaoCoberto;
        }
    }
}

int otimiza(int linha)
{
    int j;

    if(linha == _tamanho)
        return TRUE;

    for(j=0; j < _tamanho; j++) {
        if(_valores[linha][j] == 0 && _colunasOcupadas[j] == 0) {
            _linhas[linha] = j;
            _colunasOcupadas[j] = 1;
            if(otimiza(linha+1))
                return TRUE;
            _colunasOcupadas[j] = 0;
        }
    }
    return FALSE;
}

void geraErro(int nivel)
{   if(nivel == 0)
        return;
    
    int check1=FALSE, check2=TRUE, c=_tamanho-1, atv, i;
    for(i=0; i < _tamanho; i++) {
        if(_linhas[i]==0)
            if(_linhas[i+1] != 0) {
                break;
            } else {
                check1 = TRUE;
                break;
            }
    }
    srand(time(NULL));
    if(check1 == FALSE) {
        while(_linhas[c] == 0) {
            atv = rand() % _tamanho;
            for(i=0; i < _tamanho; i++) {
                if(atv == _linhas[i]) {
                    check2=FALSE;
                    break;
                }
            }
            if(check2 == TRUE) {
                _linhas[c--] = atv;
            }
            check2 = TRUE;
        }
    } else {
        while(_linhas[c] == 0 && _linhas[c-1] == 0) {
            atv = rand() % _tamanho;
            for(i=0; i < _tamanho; i++) {
                if(atv == _linhas[i]) {
                    check2=FALSE;
                    break;
                }
            }
            if(check2 == TRUE) {
                _linhas[c--] = atv;
            }
            check2 = TRUE;
        }
    }

    srand(time(NULL));
    int chance = rand() % 100;

    //printf("%d\n", chance);

    int troca[] = {0, 0}, aux;
    while(troca[0] == troca[1]) {
        troca[0] = rand() % (_tamanho-1);
        troca[1] = rand() % (_tamanho-1);
    }

    if(nivel == 3) {
        if(chance > 95) {
            aux = _linhas[troca[0]];
            _linhas[troca[0]] = _linhas[troca[1]];
            _linhas[troca[1]] = aux;
        }
    } else if(nivel == 2) {
        if(chance > 75) {
            aux = _linhas[troca[0]];
            _linhas[troca[0]] = _linhas[troca[1]];
            _linhas[troca[1]] = aux;
        }
    } else if(nivel == 1){
        if(chance % 2 == 0) {
            aux = _linhas[troca[0]];
            _linhas[troca[0]] = _linhas[troca[1]];
            _linhas[troca[1]] = aux;
        }
    } else {
        printf("Erro_8");
    }
}
