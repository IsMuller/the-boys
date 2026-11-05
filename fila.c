//usamos para implementar a fila de cada base
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fila_t *fila_cria (){
    struct fila_t *nova_fila = malloc (sizeof(struct fila_t));
    if (!nova_fila)
        return NULL;
    memset (nova_fila, 0, sizeof(struct fila_t));
    return nova_fila;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fila_t *fila_destroi (struct fila_t *f){
  if (!f)
    return NULL;

  struct fila_nodo_t *aux;

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

// Insere o item na fila
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fila_insere (struct fila_t *f, void *item){
  if (!f || !item)
    return -1;

  struct fila_nodo_t *busca_rep = f -> prim; //busca se tem item repetido, se não, ai aloca o novo nodo
  while (busca_rep != NULL) {
    if (busca_rep -> item == item)
      return -1; 
    busca_rep = busca_rep -> prox;
  }

  struct fila_nodo_t *novo_nodo = malloc(sizeof(struct fila_nodo_t));//aloca nodo
  
  if(!novo_nodo)
    return -1;

  memset(novo_nodo, 0, sizeof(struct fila_nodo_t)); //inicializa nodo

  novo_nodo -> item = item;

  if (f -> num == 0){//fila vazia
    f-> prim = novo_nodo;
    f-> fim = novo_nodo;
  }
  else { //insere no fim (regra FIFO)
    f -> fim -> prox = novo_nodo;
    f -> fim = novo_nodo;
  }

  f -> num++;
  return f -> num;
}

// Retira o primeiro item da fila e o devolve
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fila_retira (struct fila_t *f){
  if (!f || f -> num == 0)
    return NULL;
  struct fila_nodo_t *aux = f -> prim; //elemento a ser removido
  void *item = aux -> item; //salva o item removido pra retorna-lo
  if (f -> num == 1){ //só um elemento
    f -> prim = NULL;
    f -> fim = NULL;
  }
  else 
    f -> prim = aux -> prox;

  f -> num--;
  free(aux);

  return item;
}


// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fila_tamanho (struct fila_t *f){
  if (!f)
    return -1;
  
  return f -> num;
}

// Imprime o conteúdo da fila 
void fila_imprime (struct fila_t *f){
  if (!f || f -> num == 0)
    return;

  struct fila_nodo_t *aux = f -> prim;
  for (int i = 0; i < f -> num; i++){

    printf("%d", *((int *)(aux -> item))); //item é um ponteiro void. Entao o caracterizamos como um ponteiro para inteiros e pegamos seu valor

    if (i < f -> num - 1)
      printf(" ");

    aux = aux -> prox;
  }
}
