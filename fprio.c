//utilizada para implementar a fila de acontecimentos(a prio é o tempo)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fprio.h"

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fprio_t *fprio_cria (){
  struct fprio_t *nova_fila = malloc (sizeof(struct fprio_t));
  if (!nova_fila)
    return NULL;

  memset (nova_fila, 0, sizeof(struct fprio_t));
  return nova_fila;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fprio_t *fprio_destroi (struct fprio_t *f){
  if (!f)
    return NULL;

  struct fpnodo_t *aux;

  for (int i = 0; i < f -> num; i++){
    aux = f -> prim;
    f -> prim = aux -> prox;
    if (aux -> item)
      free(aux -> item);
    free(aux);
  }
  free(f);
  return NULL;
}


// Insere o item na fila, mantendo-a ordenada por prioridades crescentes (com FIFO caso =)
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio){
  if (!f || !item)
    return -1;

  struct fpnodo_t *busca_rep = f -> prim; //busca se tem item repetido, se não, ai aloca o novo nodo
  while (busca_rep != NULL) {
    if (busca_rep -> item == item)
      return -1; 
    busca_rep = busca_rep -> prox;
  }

  struct fpnodo_t *novo_nodo = malloc(sizeof(struct fpnodo_t));//aloca nodo
  
  if(!novo_nodo)
    return -1;

  memset(novo_nodo, 0, sizeof(struct fpnodo_t)); //inicializa nodo

  novo_nodo -> item = item;
  novo_nodo -> tipo = tipo;
  novo_nodo -> prio = prio;

  if (f -> num == 0)//fila vazia
    f-> prim = novo_nodo;

  else if (novo_nodo -> prio < f -> prim -> prio) { //insere no inicio (prio menor)
    novo_nodo -> prox = f -> prim;
    f -> prim = novo_nodo;
  }
  else { //insere no meio, ou seja prio é >= ao prim
    struct fpnodo_t *aux = f -> prim;
    while (aux -> prox != NULL && novo_nodo -> prio >= aux -> prox -> prio)
      aux = aux -> prox; //vai até uma pos depois

    if (aux -> prox == NULL)
      novo_nodo -> prox = NULL;
    else
      novo_nodo -> prox = aux -> prox;
    aux -> prox = novo_nodo;
  }

  return f -> num++;
}

// Retira o primeiro item da fila e o devolve; o tipo e a prioridade
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio){
  if (!f || !tipo || !prio || f -> num == 0)
    return NULL;
  struct fpnodo_t *aux = f -> prim; //elemento a ser removido

  *tipo = aux -> tipo;
  *prio = aux -> prio;
  void *item = aux -> item; //salva o item removido pra retorna-lo

  if (f -> num == 1) //só um elemento
    f -> prim = NULL;
  else 
    f -> prim = aux -> prox;

  f -> num--;
  free(aux);

  return item;
}

// Informa o número de itens na fila.
int fprio_tamanho (struct fprio_t *f){

  if (!f)
    return -1;
  
  return f -> num;
}

// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
void fprio_imprime (struct fprio_t *f){

  if (!f || f -> num == 0)
    return;

  struct fpnodo_t *aux = f -> prim;
  for (int i = 0; i < f -> num; i++){

    printf("(%d %d)", aux -> tipo, aux -> prio);

    if (i < f -> num - 1)
      printf(" ");

    aux = aux -> prox;
  }
}