#include <stdlib.h>
#include <stdio.h>

#include <time.h>

#include "dados.h"
#include "ia.h"

int main(){

    Score p;

    p.Score10 = MAX;
    p.Score20 = MAX;
    p.Score30 = MAX;
    p.Score50 = MAX;
    p.Score100 = MAX;



    setRecorde(p);
   
/*
    clock_t c = clock();
    system("pause");
    int msec = (clock() - c)*1000/CLOCKS_PER_SEC;

    printf("tempo %d", msec/1000);  
     */  

    return 0;
}
