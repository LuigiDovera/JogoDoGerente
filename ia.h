#define TRUE 1
#define FALSE 0

int _tamanho;
int **_valores;
int _numLinhas;
int **_retas;

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

void copia_valores(int**, int**);
void subtraiMinimoLinha();
void subtraiMinimoColuna();
void cobreZeros();
int direcao(int, int);
void coloreVizinhos(int, int, int);
void criaZerosExtras();
int otimiza(int*, int*, int);

Jogada jogadaAutomatica(int **_valoresOriginal, int tamanho, int nivel)
{
    _tamanho = tamanho;
    Jogada jogada = {.resultado = -1, .atribuicoes = NULL};
    _valores = alocaMatrizQuadrada(_tamanho);
    _numLinhas = 0;
    _retas = alocaMatrizQuadrada(_tamanho);
    int linhas[_tamanho], colunasOcupadas[_tamanho], i;

    jogada.atribuicoes = (int*)malloc(_tamanho * sizeof(int));
    if(jogada.atribuicoes == NULL) {
        printf("Erro_4");
        return jogada;
    }
    copia_valores(_valores, _valoresOriginal);
    subtraiMinimoLinha();
    subtraiMinimoColuna();
    cobreZeros();
    while(_numLinhas < _tamanho) {
        criaZerosExtras();
        cobreZeros();
    }
    otimiza(linhas, colunasOcupadas, 0);
    jogada.atribuicoes = linhas;
    for(i=0; i < _tamanho; i++) {
        //jogada.resultado += _valoresOriginal[i][linhas[i]];
    }
    free(_retas);
    free(_valores);
    return jogada; 
}

void copia_valores(int **destino, int **origem)
{
    int i, j;
    for(i=0; i < sizeof(origem[0])/sizeof(int); i++) {
        for(j=0; j < sizeof(origem[0])/sizeof(int); j++) {
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

    _numLinhas = 0;
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
    _numLinhas++;
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

int otimiza(int *linhas, int *colunasOcupadas, int linha)
{
    int j;

    if(linha == sizeof(linhas)/sizeof(int))
        return TRUE;

    for(j=0; j < _tamanho; j++) {
        if(_valores[linha][j] == 0 && colunasOcupadas[j] == 0) {
            linhas[linha] = j;
            colunasOcupadas[j] = 1;
            if(otimiza(linhas, colunasOcupadas, linha+1))
                return TRUE;
            colunasOcupadas[j] = 0;
        }
    }
    return FALSE;
}