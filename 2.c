#include <stdio.h>
#include <stdlib.h>


 // funcao responsavel por alocar as posicoes necessarias no vetor.
 int* iniciaVetor(int posicoes) {
    int* conjunto ;
   conjunto = (int*) malloc (posicoes * sizeof(int)) ;
   return conjunto ; // retornar o vetor
 }
  // funcao responsavel por liberar a memoria dos conjuntos
 void liberaConjunto(int *conjunto){
   free(conjunto) ;
  }
  // funcao responsavel por imprimir todas as posicoes do vetor.
 void imprimeConjunto(int* conjunto, int posicoes){
   for (int i =0 ; i<posicoes ; i++) {
     printf("%d ", conjunto[i]) ;
    }
    printf("\n");
  }
 // funcao responsavel por unir dois conjuntos
int* uniao(int *cA, int nA,int *cB,int nB, int *nC) {
  // vetor que vai ficar alocada a uniao
  int*cC;
  cC=(int*) malloc((nA+nB)*sizeof(int)) ;
  *nC = 0 ;
  //for responsavel por alocar os numeros do conjunto A para o C
  for (int i=0;i<nA;i++){
    int testavalor=0, j ;
    for( j=0 ; j<(*nC);j++) { // responsavel por verificar todos os numeros ja alocados em C
      if(cC[j]==cA[i]){ // verifica se tem algum numero igual
        testavalor++ ;
      }
    }
    if (testavalor==0){ // caso nao tenha numero igual, aloca no conjunto C
      cC[j] = cA[i];
      (*nC)++ ; // variavel responsavel pela quantidade de posicoes ja utilizadas no conjunto C
    }
  }

  int tamanho= *nC; // variavel responsavel por nao alterar o valor de *nC durante o processo
  for (int j=0;j<nB;j++){ // for responsavel por alocar os numeros do conjunto B pro C
    int testavalor=0;
    for (int k=0;k<tamanho+j; k++){ // responsavel por verificar todos os numeros ja alocados em C
      if (cC[k]==cB[j]){ // verifica se tem numero igual
        testavalor++ ;
      }
    }
    if (testavalor==0){ // caso nao tem numero igual, aloca o valor em C
      cC[(*nC)++] = cB[j];

    }
  }
 // vetor criado para passar os valores de C para F e impedir lixo de memoria.
  int*cF;
  cF=(int*) malloc((*nC)*sizeof(int));
  for (int i=0;i<(*nC);i++){ // aloca valores de C em F
    cF[i] = cC[i];
  }

  liberaConjunto(cC) ; // libera memoria de C

  int aux ;
  for (int j=0;j<(*nC);j++){ // for responsavel por ordenar os valores
    for (int k=0;k<j; k++){
      if (cF[j]<cF[k]){ //caso o ultimo valor seja menor que seus anteriores, troca de posicoes.
        aux=cF[j];
        cF[j]=cF[k] ;
        cF[k]= aux ;
      }
    }
  }

  return cF; // retorna conjunto f/uniao
}





 // funcao criada para verificar pontos de interseccao
int* interseccao(int* cA,int nA,int* cB,int nB,int *nD){
   int*cD; // conjunto criado para a interseccao
   cD=(int*) malloc(nA+nB*sizeof(int)) ;
   *nD  = 0 ; // variavel responsavel pela quantidade de valores armazenados em D
  int l=0 ;
  for (int j=0;j<nB;j++){ // responsavel por passar pelo B inteiro
    int testavalor=0;
    for (int k=0;k<nA+j; k++){ // responsavel por passar em A e nos valores armazenados
      if (cA[k]==cB[j]){ // testa caso tenha algum valor igual
        testavalor++ ;
      }
    }
    if (testavalor>0){ // caso tenha valor igual adicionara no conjunto D, adicionara uma posicao extra a *nD
      cD[l]=cB[j];
      (*nD)++ ;
      l++ ; // auxiliar a alocar os valores corretamente em D
    }
  }
 return cD ;
}

//NAO ALTERE A MAIN
int main(int argc, char * argv[]){
  int* A;
  int* B;
  int* C;
  int* D;
  int nA, nB, nC, nD, aux;

  //inicializando e lendo o conjunto A
  scanf("%d", &nA);
  A = iniciaVetor(nA);
  for(int i = 0; i < nA; i++){
    scanf("%d", &aux);
    A[i] = aux;
  }
  //inicializando e lendo o conjunto B
  scanf("%d", &nB);
  B = iniciaVetor(nB);
  for(int i = 0; i < nB; i++){
    scanf("%d", &aux);
    B[i] = aux;
  }

  //calcula e imprime a uniao e a interseccao
  C = uniao(A, nA, B, nB, &nC);
  imprimeConjunto(C, nC);

  D = interseccao(A, nA, B, nB, &nD);
  imprimeConjunto(D, nD);

  //libera a memoria dos 4 vetores
  liberaConjunto(A);
  liberaConjunto(B);
  liberaConjunto(C);
  liberaConjunto(D);

  return 0;
}
