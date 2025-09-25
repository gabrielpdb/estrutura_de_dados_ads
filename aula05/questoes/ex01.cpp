/* Fila circular (array fixo) com enqueue, dequeue, peek, size
Enunciado. Implemente uma fila circular com capacidade fixa N e funções: q_init, q_empty, q_full, q_size, enqueue, dequeue, peek. Trate overflow (não inserir se cheia) e underflow (não remover se vazia). (Base: inserção no fim e remoção no início; vetor tem tamanho pré-definido.) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define MAX 5

typedef struct
{
  int dados[MAX];
  int inicio;
  int fim;
  int tamanho;
} Fila;

Fila *q_init();
bool q_empty(Fila *f);
bool q_full(Fila *f);
int q_size(Fila *f);
void enqueue(Fila *f, int valor);
int dequeue(Fila *f);
int peek(Fila *f);

int main(void)
{

  Fila *filaComVetor;

  filaComVetor = q_init();
  enqueue(filaComVetor, 1);
  enqueue(filaComVetor, 2);
  enqueue(filaComVetor, 3);
  enqueue(filaComVetor, 4);
  enqueue(filaComVetor, 5);
  for (int i = 0; i < MAX; i++)
  {
    printf("[%d]: %d\n", i, filaComVetor->dados[i]);
  }
  dequeue(filaComVetor);
  printf("inicio: %d\n", peek(filaComVetor));
  for (int i = 0; i < MAX; i++)
  {
    printf("[%d]: %d\n", i, filaComVetor->dados[i]);
  }
  enqueue(filaComVetor, 12);
  printf("inicio: %d\n", peek(filaComVetor));
  for (int i = 0; i < MAX; i++)
  {
    printf("[%d]: %d\n", i, filaComVetor->dados[i]);
  }
}

Fila *q_init()
{
  Fila *f = (Fila *)malloc(sizeof(Fila));
  f->inicio = 0;
  f->fim = -1;
  f->tamanho = 0;

  return f;
}
