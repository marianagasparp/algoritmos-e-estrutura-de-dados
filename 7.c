#include <stdio.h>
#include <stdlib.h>

#define MAX 5000
//estrutura da torre
typedef struct Torre{
  int vida;
  int id;
} torre;
//ponteiro da torre
typedef torre* p_t;

// estrutura da fila de prioridade
typedef struct Fila{
  int tamanho_fila;
  torre* torres;
} fila;
// ponteiro da fila de prioridade
typedef fila* p_fp;

// função para inventer posição das torres
void inverte_posicao (p_fp f, int i, int j){
  torre aux = f->torres[j];
  f->torres[j] = f->torres[i];
  f->torres[i] = aux;
}

//criação de fila vazia
p_fp criar_f_prio(int maximo){
  p_fp f = malloc(sizeof(fila));
  f->tamanho_fila = 0;
  f->torres = malloc(maximo * sizeof(p_t));
  return f;
}

// função para contar quantidade de elementos na fila
int tamanho_fila(p_fp f){
  int tamanho_total=f->tamanho_fila ;
  return tamanho_total;
}

// elemento vai subir na fila de prioridade 
void filho_vira_pai(p_fp f, int i){
  int j = ((i-1)/2);// j = posicao do pai de i

  if (f->torres[i].vida == f->torres[j].vida){ // caso id do pai seja igual do filho
    if (f->torres[i].id < f->torres[j].id){ //compara o id e caso o do filho seja menor
      inverte_posicao ( f, i, j) ; // inverte as posicoes 
      filho_vira_pai(f, j); // recursão para o filho ir trocando com o pai conforme a necessidade. 
      return ;
    }
  } 
  if (f->torres[i].vida < f->torres[j].vida){ // caso a vida do pais seja maior que o do filho
   inverte_posicao ( f, i, j) ; // inverte posicoes
   filho_vira_pai(f, j); // recursao para o filho ir trocando com o pai conforme a necessidade
  }
}

//inserção da torre na fila
void insere(p_fp f, int torre_id, int torre_vida){
  f->torres[f->tamanho_fila].id = torre_id;// insere id
  f->torres[f->tamanho_fila].vida = torre_vida; //insere vida
  f->tamanho_fila++; //aumenta tamanho da fila
  filho_vira_pai(f, tamanho_fila(f)- 1);  // função que altera o elemento filho para virar pai conforme necessidade
}

//funcao que pai vira filho na lista de prioridade
void pai_vira_filho(p_fp f, int i){
  int filho_esq = (2*i+1);//filho_esq de i 
  int filho_dir = filho_esq+1 ; // filho_dir de i
  int filho_menor = filho_esq ; // coloca o menor como esquerdo

  if (f->torres[filho_esq].vida==0){ //Se o filho esquerdo for igual a 0, ele nao existe
    return;
  }
  
  if (f->torres[filho_dir].vida>0){ // se a vida do filho direito for maior que 0 , ele existe
    if (f->torres[filho_dir].vida < f->torres[filho_esq].vida){ //e se ele tiver vida menor que o esquerdo
      filho_menor = filho_dir; // o filho direito sera o novo menor
    }
    if (f->torres[filho_dir].vida == f->torres[filho_esq].vida){ // se o filho direito tiver vida igual ao esquerdo
      if (f->torres[filho_dir].id < f->torres[filho_esq].id){ // e se o direito tiver id menor que o esquerdo
        filho_menor = filho_dir; // o direito sera o novo filho melhor
      }
    }
  }

  if (f->torres[i].vida == f->torres[filho_menor].vida){ // se o pai tem vida igual ao menor
    if (f->torres[i].id > f->torres[filho_menor].id){ // e se o id do pai for maior que o do menor
      inverte_posicao ( f, i, filho_menor) ; // pai inverte posicao com o filho
      pai_vira_filho(f, filho_menor); // recursao para o filho ir trocando com o pai conforme a necessidade
      return;
    }
  }
  else if (f->torres[i].vida > f->torres[filho_menor].vida){// se nao, se vida do pai maior que a do filho
    inverte_posicao ( f, i, filho_menor) ; // pai inverte posicao com o filho
    pai_vira_filho(f, filho_menor); // recursao para o filho ir trocando com o pai conforme a necessidade
   return ;
  }
}

//função para remoção do elemento com menor vida da fila
torre extrai_minimo(p_fp f){ 
  torre menor_torre = f->torres[0];// a torre da raiz vira a menor torre
  f->torres[0] = f->torres[tamanho_fila(f)- 1]; // coloca a ultima torre da fila como raiz
  f->tamanho_fila--; //diminui o tamanho da fila
  pai_vira_filho(f, 0); // raiz vira filho conforme a necessidade 
  return menor_torre; // retorna menor torre
}

int main(int argc, char* argv[]){

  p_fp f = criar_f_prio(MAX);
  int torre_id = 0;
  int turnos = 0;
  int dano_jogador = 0;

  //lendo a quantidade de turnos
  scanf("%d", &turnos);

  //semente para o gerador de numeros aleatorios
  srand(turnos);

  //enquanto houverem turnos
  while (turnos > 0)
{
    //Nasce uma nova torre com vida sorteada aleatoriamente
    //entre 1 e 20
    if (tamanho_fila(f)< MAX)
  {
      int vida = (rand()% 20)+ 1;
      printf("Nova torre %d: %d\n", torre_id, vida);
      insere(f, torre_id, vida);
      torre_id++;
    }

    //Encontrando o proximo alvo e atacando (remove 10 de vida)
    torre torre_alvo = extrai_minimo(f);
    printf("Atk %d: %d -> %d\n", torre_alvo.id, torre_alvo.vida, torre_alvo.vida - 10);
    torre_alvo.vida = torre_alvo.vida - 10;
    if (torre_alvo.vida > 0)
  {
      //Torre nao caiu, volta para f
      insere(f, torre_alvo.id, torre_alvo.vida);
    }
    else{
      printf("t%d caiu\n", torre_alvo.id);
    }

    //Cada torre viva causa 1 de dado no jogador
    int num_torres_vivas = tamanho_fila(f);
    printf("%d dano\n\n", num_torres_vivas);
    dano_jogador = dano_jogador + num_torres_vivas;
    turnos--;
  }

  printf("\nFINAL:\n");
  printf("Jogador tomou %d dano\n", dano_jogador);

  return 0;
}
