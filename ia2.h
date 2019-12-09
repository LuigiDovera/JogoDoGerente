#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAXI 99999

typedef struct
{
    int resultado, *atribuicoes;
}Jogada;

Jogada jogada = {.resultado = -1, .atribuicoes = NULL};
int _tamanho;
int _contaCaminho = 0;
int caminhoLinha0;
int caminhoColuna0;
int **_matrizOriginal = NULL;
int **_valores = NULL;
int **_marcas = NULL;
int **_caminho = NULL;
int *_marcaLinha = NULL;
int *_marcaColuna = NULL;

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

void copiaMatriz(int **destino, int **origem)
{
    int i, j;
    for(i=0; i < _tamanho; i++) {
        for(j=0; j < _tamanho; j++) {
            destino[i][j] = origem[i][j];
        }
    }
}

void passoUm();
void passoDois();
void passoTres();
void passoQuatro();
void passoCinco();
void passoSeis();
void concluido();
void geraErro(int);

Jogada jogadaAutomatica(int **matrizOriginal, int tamanho, int nivel)
{
    int i, j;

    _tamanho = tamanho;
    _matrizOriginal = alocaMatrizQuadrada(_tamanho);
    _valores = alocaMatrizQuadrada(_tamanho);
    _marcas = alocaMatrizQuadrada(_tamanho);
    //_caminho = alocaMatrizQuadrada(_tamanho);
    _marcaLinha = alocaVetor(_tamanho);
    _marcaColuna = alocaVetor(_tamanho);
    jogada.atribuicoes = alocaVetor(_tamanho);

    _caminho = (int**)malloc(2*_tamanho*sizeof(int*)+1);
    for(i=0; i < ((2*_tamanho)+1); i++);
        _caminho[i] = (int*)malloc(_tamanho*sizeof(int));
    
    copiaMatriz(_matrizOriginal, matrizOriginal);
    copiaMatriz(_valores, matrizOriginal);
    for(i=0; i < _tamanho; i++) {
        _marcaLinha[i] = 0;
        _marcaColuna[i] = 0;
        for(j=0; j < _tamanho; j++) {
            _marcas[i][j] = 0;
        }
    }
    passoUm();
    geraErro(nivel);
    return jogada;
}

void passoUm()
{
    int menorNaLinha, i, j;

    for(i=0; i < _tamanho; i++) {
        menorNaLinha = _valores[i][0];
        for(j=0; j < _tamanho; j++) {
            if(_valores[i][j] < menorNaLinha)
                menorNaLinha = _valores[i][j]; 
        }
        for(j=0; j < _tamanho; j++) {
            _valores[i][j] -= menorNaLinha;
        }  
    }
    passoDois();
}

void passoDois()
{
    int i, j;

    for(i=0; i < _tamanho; i++) {
        for(j=0; j < _tamanho; j++) {
            if(_valores[i][j] == 0 && _marcaLinha[i] == 0 && _marcaColuna[j] == 0) {
                _marcas[i][j] = 1;
                _marcaLinha[i] = 1;
                _marcaColuna[j] = 1;
            }    
        }   
    }
    for(i=0; i < _tamanho; i++) {
        _marcaLinha[i] = 0;
        _marcaColuna[i] = 0;
    }
    passoTres();
}

void passoTres()
{
    int contaColuna, i, j;

    for(i=0; i < _tamanho; i++) {
        for(j=0; j < _tamanho; j++) {
            if(_marcas[i][j] == 1)
                _marcaColuna[j] = 1;
        }
    }
    contaColuna = 0;
    for(j=0; j < _tamanho; j++) {
        if(_marcaColuna[j] == 1)
            contaColuna++;
    }
    if(contaColuna >= _tamanho) {
        concluido();
    } else {
        passoQuatro();
    }
}

void achaZero(int *linha, int *coluna)
{
    int l=0, c, feito = FALSE;

    *linha = -1;
    *coluna = -1;

    while(feito == FALSE) {
        c = 0;
        for(;;) {
            if(_valores[l][c] == 0 && _marcaLinha[l] == 0 && _marcaColuna[c] == 0) {
                *linha = l;
                *coluna = c;
                feito = TRUE;
            }
            c++;
            if(c >= _tamanho || feito == TRUE)
                break;
        }
        l++;
        if(l >= _tamanho)
            feito = TRUE;
    }
}

int marcaNaLinha(int linha)
{
    int resposta=FALSE, j;

    for(j=0; j < _tamanho; j++) {
        if(_marcas[linha][j] == 1)
            resposta = TRUE;
    return resposta;
    }
}

void achaMarcaNaLinha(int linha, int *coluna)
{
    int j;

    *coluna = -1;
    for(j=0; j < _tamanho; j++)
        if(_marcas[linha][j] == 1)
            *coluna = j;
}

void passoQuatro()
{
    int aux1=-1, aux2=-1, feito = FALSE;
    int *linha=&aux1, *coluna=&aux2;

    while(feito == FALSE) {
        achaZero(linha, coluna);
        if(*linha == -1) {
            feito = TRUE;
            passoSeis();
        } else {
            _marcas[(*linha)][(*coluna)] = 2;
            if(marcaNaLinha((*linha)) == TRUE) { //checar true false
                achaMarcaNaLinha((*linha), coluna);
                _marcaLinha[(*linha)] = 1;
                _marcaColuna[(*coluna)] = 0;
            } else {
                feito = TRUE;
                passoCinco();
                caminhoLinha0 = *linha;
                caminhoColuna0 = *coluna;
            }
        }
    }
}

void achaMarcaNaColuna(int coluna, int *linha)
{
    int i;

    *linha = -1;
    for(i=0; i < _tamanho; i++)
        if(_marcas[i][coluna] == 1)
            *linha = i;
}

void achaEspecialNaLinha(int linha, int *coluna)
{
    int j;

    for(j=0; j < _tamanho; j++) {
        if(_marcas[linha][j] == 2)
            *coluna = j;
    }
}

void melhoraCaminho()
{
    int i;

    for(i=0; i < _contaCaminho; i++) {
        if(_marcas[_caminho[i][0]][_caminho[i][1]] == 1)
            _marcas[_caminho[i][0]][_caminho[i][1]] = 0;
        else
            _marcas[_caminho[i][0]][_caminho[i][1]] = 1;
    }
}

void limpaMarcas()
{
    int i;

    for(i=0; i < _tamanho; i++) {
        _marcaLinha[i] = 0;
        _marcaColuna[i] = 0;
    }
}

void limpaEspeciais()
{
    int i, j;

    for(i=0; i < _tamanho; i++) {
        for(j=0; j < _tamanho; j++) {
            if(_marcas[i][j] == 2)
                _marcas[i][j] = 0;
        }
    }
}

void passoCinco()
{
    int aux1=-1, aux2=-1, feito = FALSE;
    int *linha=&aux1, *coluna=&aux2;

    _contaCaminho = 1;
    _caminho[_contaCaminho-1][0] = caminhoLinha0;
    _caminho[_contaCaminho-1][1] = caminhoColuna0;

    while(feito == FALSE) {
        achaMarcaNaColuna(_caminho[_contaCaminho-1][1], linha);
        if(*linha > -1) {
            _contaCaminho++;
            _caminho[_contaCaminho-1][0] = *linha;
            _caminho[_contaCaminho-1][1] = _caminho[_contaCaminho-2][1];
        } else {
            feito = TRUE;
        }
        if(feito == FALSE) {
            achaEspecialNaLinha( _caminho[_contaCaminho-1][0], coluna);
            _contaCaminho++;
            _caminho[_contaCaminho-1][0] = _caminho[_contaCaminho-2][0];
            _caminho[_contaCaminho-1][1] = *coluna;
        }
    }
    melhoraCaminho();
    limpaMarcas();
    limpaEspeciais();
    passoTres();
}

void achaMenor(int *menor)
{
    int i, j;

    for(i=0; i < _tamanho; i++) {
        for(j=0; j < _tamanho; j++) {
            if(_marcaLinha[i] == 0 && _marcaColuna[j] == 0)
                if(*menor > _valores[i][j])
                    *menor = _valores[i][j];
        }
    }
}

void passoSeis()
{
    int aux = MAXI, i, j;
    int *menor = &aux;

    achaMenor(menor);
    for(i=0; i < _tamanho; i++) {
        for(j=0; j < _tamanho; j++) {
            if(_marcaLinha[i] == 1)
                _valores[i][j] += *menor;
            if(_marcaColuna[j] == 0)
                _valores[i][j] -= *menor;
        }
    }
    passoQuatro();
}

void concluido()
{
    int i, j;
    jogada.resultado++;
    for(i=0; i < _tamanho; i++) {
        for(j=0; j < _tamanho; j++) {
            if(_marcas[i][j] == 1) {
                jogada.atribuicoes[i] = j;
                jogada.resultado += _matrizOriginal[i][j];
            }
        }
    }
}

void geraErro(int nivel)
{
    srand(time(NULL));
    int chance = rand() % 100;
    int troca[] = {0, 0}, aux;
    while(troca[0] == troca[1]) {
        troca[0] = rand() % (_tamanho-1);
        troca[1] = rand() % (_tamanho-1);
    }

    if(nivel == 3) {
        if(chance > 95) {
            aux = jogada.atribuicoes[troca[0]];
            jogada.atribuicoes[troca[0]] = jogada.atribuicoes[troca[1]];
            jogada.atribuicoes[troca[1]] = aux;
        }
    } else if(nivel == 2) {
        if(chance > 75) {
            aux = jogada.atribuicoes[troca[0]];
            jogada.atribuicoes[troca[0]] = jogada.atribuicoes[troca[1]];
            jogada.atribuicoes[troca[1]] = aux;
        }
    } else if(nivel == 1){
        if(chance % 2 == 0) {
            aux = jogada.atribuicoes[troca[0]];
            jogada.atribuicoes[troca[0]] = jogada.atribuicoes[troca[1]];
            jogada.atribuicoes[troca[1]] = aux;
        }
    } else {
        printf("Erro_8");
    }
}