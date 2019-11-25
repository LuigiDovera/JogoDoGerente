#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arrlen(char *arr){
  return sizeof(arr)/sizeof(arr[0]);
}

int main(void) {
  FILE *pf = fopen("cenario/atribuicao_10.txt","r");
  int tam = 301;
  char string[tam]; //string de tamanho arbitrário para alocação de cada linha do arquivo
  /*for(char c=getc(pf);c!=EOF;pf++){
    printf("%c", c);
  }
  while(fgets(string, 1000, pf) != NULL)
    printf("%s", string);
  */
  fgets(string, arrlen(string), pf); //recebendo o tamanho da matriz
  int tam_matriz = atoi(string); //transformando string pra inteiro
  int cenario[tam_matriz][tam_matriz];

  for (int i=0; fgets(string, arrlen(string), pf) != NULL && i<tam_matriz; i++){
    int k=0;
    for (int j=0; j<tam_matriz; j++){
      char strnum[4] = "";
      /*if(string[k]==' '){
        k++;
      }*/
      for(int l=0; string[k]!=' ';){
        strnum[l] = string[k];
        k++;
        l++;
      }
      cenario[i][j] = atoi(strnum);
      printf("%d ", cenario[i][j]);
    }
     printf("aaa\n");
    printf("\n");
  }



  /*for (int i=0; i<tam_matriz; i++){
    for (int j=0; j<tam_matriz; j++){
      printf("%d ", cenario[i][j]);
    }
    printf("\n");
  }
  */

  fclose(pf);
  return 0;
}

