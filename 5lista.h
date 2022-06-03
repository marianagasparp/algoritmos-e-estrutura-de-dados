typedef struct no{
    void* dado ;
   struct no *prox ;
}No ;
typedef struct no *p_no ;

typedef struct pilha {
    struct no *topo ;
}Pilha;
typedef struct pilha *p_pilha ;

p_pilha criar_pilha() ; 

void empilha(p_pilha, void*) ;

void* desempilha (p_pilha) ;

void destroi_pilha(p_pilha, int);
