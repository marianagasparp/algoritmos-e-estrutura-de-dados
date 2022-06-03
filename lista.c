#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

p_pilha criar_pilha(){
  p_pilha nova= malloc (sizeof(Pilha));
  nova->topo=NULL ; 
  return nova ;
}

void empilha(p_pilha PIL, void* e){
 p_no novo_no = malloc (sizeof(No)); // cria novo no
 novo_no->dado = (void*) e ;// aloca o dado atual no no
 novo_no->prox = PIL->topo ; // aloca o topo da lista no ponteiro do no
 PIL->topo = novo_no ; // aloca o novo no como topo da pihla
}

void* desempilha (p_pilha PIL){
   p_no topo_antigo = PIL->topo ; // aloca o no topo na variavel topo_antigo
   void* x = topo_antigo->dado ; // aloca o dado do topo em x
   PIL->topo = topo_antigo->prox ; // o prox do topo vira o novo topo
   free(topo_antigo) ; // libera memoria do topo
   return x ;
}

void destroi_pilha(p_pilha PIL, int tamanho){
while (tamanho!= 0) { // repete a funcao desempilha ate o ultimo dado
   p_no topo_antigo = PIL->topo ;
   PIL->topo = topo_antigo->prox ;
   free(topo_antigo) ;
   tamanho-- ;
  }
}
