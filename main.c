#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main(){
char funcao;
char* dado=0 ;
 int tamanho=0 ;
  p_pilha PIL = criar_pilha() ;
  
 
  do {
    scanf ("%c", &funcao ) ;
    switch (funcao){
      case 'e':
        dado = malloc (4 * sizeof(No)) ;
        scanf ("%s", dado) ;
        empilha(PIL, dado) ;
        tamanho++ ;
      break ;
      case 'd':
        printf("%s\n", desempilha(PIL)) ;
        tamanho-- ;
      break ;
      case 't':
        printf("%d\n", tamanho) ;
      break ;
    } 
  } while (funcao != 'x') ;
   destroi_pilha(PIL, tamanho) ;
 return 0 ;
}
