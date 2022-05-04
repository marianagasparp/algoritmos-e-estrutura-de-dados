#include <stdio.h>
#include <stdlib.h>
//funcao que aloca memoria para o vetor
int *aloca_vetor(int tam_vetor) {
 int *vetor = malloc (tam_vetor * sizeof(int)) ;
 return vetor ;
}
// funcao que testa possibilidades
int testa_item(int tam_vetor, int peso_total, int *V, int peso_atual,int pos_atual,int * V_resp){

  if(peso_atual==peso_total) return 1 ; // caso o peso total tenha sido atingido a funcao retorna 1

  if (pos_atual>=tam_vetor) return 0 ;//caso posicao atual seja maior que o tamanho do vetor, retorna 0

  if(peso_atual > peso_total) return 0; // caso o peso atual ultrapasse o peso total, retorna 0
 // recursividade que testara proximo item sem adicionar o item da posicao atual no peso atual
 int nao_adiciona = testa_item(tam_vetor,peso_total, V, peso_atual, pos_atual+1, V_resp) ;
 if (nao_adiciona==1) { // caso nao adicione o item atual, aloca 0 no vetor resposta da posicao atual
   V_resp[pos_atual]= 0 ;
   return 1 ;
 }
// adiciona item atual ao peso atual
 peso_atual = peso_atual+V[pos_atual] ;

 // recursividade que testara proximo item adicionando o item da posicao atual no peso atual
 int adiciona = testa_item(tam_vetor,peso_total, V, peso_atual, pos_atual+1, V_resp)  ;
 if (adiciona==1) { // caso adicione o item atual, aloca 1 no vetor de resposta na posicao atual.
   V_resp[pos_atual]= 1 ;
   return 1;
 }

  return 0; // retorna 0 caso passe por todos os itens

}

int main(void) {

 int peso_total,peso_atual=0, tam_vetor, pos_atual=0 ;
 int *V, *V_resp ;
 scanf ("%d", &peso_total) ; // le o peso total
 scanf ("%d", &tam_vetor) ; // le a quantidade de objetivos inseridos
 V = aloca_vetor(tam_vetor)  ; // aloca vetor de pesos
 V_resp = aloca_vetor(tam_vetor)  ; // aloca vetor de respostas

 // responsavel por alocar os pesos de cada item na posicao correta do vetor
 for(int i=0 ; i<tam_vetor ; i++) {
   scanf ("%d", &V[i]) ;
 }
 // chama a funcao testa item
 testa_item(tam_vetor,peso_total,V, peso_atual, pos_atual, V_resp) ;

 // imprime o vetor resposta
for(int i=0 ; i<tam_vetor ; i++) {
   printf ("%d ", V_resp[i]) ;
 }
// libera memoria dos vetores
 free(V_resp) ;
 free(V) ;


}
