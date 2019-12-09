#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX INT_MAX

int _tamanho;
int _contaCaminho;
int caminhoLinha0;
int caminhoColuna0;
int **_valores = NULL;
int **_marcas = NULL;
int **_caminho = NULL;
int *_marcaLinha = NULL;
int *_marcaColuna = NULL;

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
            if(marcaNaLinha((*linha)) == 1) { //checar true false
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

void passoSeis()
{
    int aux = MAX, i, j;
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

void achaZero(int *linha, int *coluna)
{
    int l=0, c, feito = FALSE;

    *linha = -1;
    *coluna = -1;

    while(feito == FALSE) {
        c = 0;
        for(;;) {
            if(_valores[l][c] == 0 && _marcaLinha[l] && _marcaColuna[c] == 0) {
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