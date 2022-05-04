#include <stdio.h>
#include <stdlib.h>


typedef struct bloco{
  int id;
  int altura;
  struct bloco* prox;
} bloco;
typedef struct bloco * p_Bloco;

typedef struct Macaco{
  int altura;
  struct bloco* lista_blocos;
} Macaco;
typedef struct Macaco * p_Macaco;


//funcao que cria os macacos
p_Macaco inicializa_macacos(int num_macacos) {
 p_Macaco M ;
 M = (p_Macaco) malloc (num_macacos * sizeof(Macaco)) ; //aloca memoria para os macacos
 for(int i=0;i<num_macacos;i++){
   M[i].altura=0 ;  // zera altura
   M[i].lista_blocos=NULL ; // zera lista de blocos
 }
 return M ; // retorn o vetor de macacos
}

// funcao que adiciona blocos na lista de cada macaco
p_Bloco adc_bloco(p_Bloco lista,int id, int altura ) {

  p_Bloco bloco =(p_Bloco) malloc(sizeof(bloco)) ; // aloca memoria para o bloco

  bloco->id=id ;  // aloca id do bloco
  bloco->altura=altura ; // aloca altura do bloco
  bloco->prox=lista ; // passa lista para o proximo bloco

  return bloco ;
}
// funcao que adiciona bloco ao macaco de menor altura
void bota_no_menor(p_Macaco M,int num_macacos,int id_bloco,int altura_bloco){

 int posicao_menor=0 ;
 for(int i=1;i<num_macacos ; i++){ // procura o macaco com a menor altura
   if (M[posicao_menor].altura>M[i].altura){
     posicao_menor=i ; // salva a posicao do macaco com menor altura
   }
  }

 M[posicao_menor].altura=M[posicao_menor].altura+altura_bloco ; // adiciona altura do bloco na altura total do macaco

 M[posicao_menor].lista_blocos=adc_bloco(M[posicao_menor].lista_blocos, id_bloco, altura_bloco) ;
// adiciona bloco na lista de blocos do macaco
}

//SUGESTAO DE FUNCOES PARA IMPRESSAO
//PODE MUDAR SE QUISER
void imprime_blocos(p_Bloco lista){
  if(lista == NULL) return;
  imprime_blocos(lista->prox);
  printf(" %d %d", lista->id, lista->altura);
}

void imprime_macacos(p_Macaco M, int num_macacos){
  for(int i = 0; i < num_macacos; i++){
    printf("M[%d] altura = %d:", i, M[i].altura);
    imprime_blocos(M[i].lista_blocos);
    printf("\n");
  }
}
// libera todos os blocos
void libera_blocos(p_Bloco blocos) {
  if (blocos == NULL) return;
  libera_blocos(blocos->prox);
  free(blocos);
}
// libera todos os macacos
void libera_macacos(p_Macaco M,int num_macacos){
 for (int i=0;i<num_macacos;i++){
   libera_blocos(M[i].lista_blocos); //
 }
 free(M) ;
}



//******************************
//VOCE NAO PODE MODIFICAR A MAIN
//******************************
int main(int argc, char * argv[]){

  p_Macaco M;
  int num_macacos;
  int id_bloco;
  int altura_bloco;

  //le o numero de macacos
  scanf("%d", &num_macacos);

  M = inicializa_macacos(num_macacos);

  //le o primeiro bloco
  scanf("%d %d", &id_bloco, &altura_bloco);
  while(id_bloco != -1){
    bota_no_menor(M, num_macacos, id_bloco, altura_bloco);
    //le o proximo bloco
    scanf("%d %d", &id_bloco, &altura_bloco);
  }

  imprime_macacos(M, num_macacos);

  //Lembre que cada macaca tem uma lista que precisa ser liberada
  libera_macacos(M, num_macacos);
  return 0;
}
