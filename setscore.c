#include <stdlib.h>
#include <stdio.h>

#include "dados.h"
#include "ia.h"

int main(){

    Score *p = (Score*)malloc(sizeof(Score));
    /*
    p->Score10 = MAX;
    p->Score20 = MAX;
    p->Score30 = MAX;
    p->Score50 = MAX;
    p->Score100 = MAX;
    */


    p->Score10 = 1;
    p->Score20 = 2;
    p->Score30 = 3;
    p->Score50 = 4;
    p->Score100 = 5;


    setRecorde(p);

    p = getRecorde();
    printf("%d ", p->Score10);
    printf("%d ", p->Score20);
    printf("%d ", p->Score30);
    printf("%d ", p->Score50);
    printf("%d ", p->Score100);

    return 0;
}
