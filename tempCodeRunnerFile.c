int main() {
    int m[][4]={{82, 83, 69, 92}, {77, 37,49,92}, {11	,69	,5	,86}, {8,	9	,98	,23}};
    Jogada jo;
    jo = jogadaAutomatica(m, 4, 1);
    printf("%d", jo.resultado);
    for(int i=0; i < 4; i++) {
        printf("%d", jo.atribuicoes[i]);
    }
}