/* Fila encadeada + concatenação O(1)
Enunciado. Implemente uma fila encadeada com insere e remove. Em seguida, escreva concatena(A,B) que anexa todos os elementos de B ao fim de A em O(1), ajustando apenas ponteiros. (Dica: ao esvaziar, mantenha inicio e fim coerentes.) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
typedef struct Node
{
    int valor;
    struct Node *prox;
};

typedef struct
{
    Node *inicio;
    Node *fim;
    int tamanho;
} Fila;

Fila *q_init();
bool q_empty(Fila *f);
int q_size(Fila *f);
void enqueue(Fila *f, int valor);
int dequeue(Fila *f);
int peek(Fila *f);
void concatena(Fila *A, Fila *B);

int main(void)
{
    Fila *A = q_init();
    enqueue(A, 1);
    enqueue(A, 2);
    enqueue(A, 3);
    printf("Primeiro da fila: %d\n", peek(A));
    Fila *B = q_init();
    enqueue(B, 4);
    enqueue(B, 5);
    enqueue(B, 6);
    concatena(A, B);
    printf("Primeiro da fila: %d\n", peek(A));
    dequeue(A);
    dequeue(A);
    dequeue(A);
    printf("Primeiro da fila: %d\n", peek(A));
    dequeue(A);
    printf("Primeiro da fila: %d\n", peek(A));
}

Fila *q_init()
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;

    return f;
}

bool q_empty(Fila *f)
{
    return (f->tamanho == 0);
}

int q_size(Fila *f)
{
    return f->tamanho;
}

void enqueue(Fila *f, int valor)
{
    Node *novo = (Node *)malloc(sizeof(Node));
    novo->valor = valor;
    novo->prox == NULL;

    if (q_empty(f))
    {
        f->inicio = novo;
    }
    else
    {
        f->fim->prox = novo;
    }
    f->fim = novo;
    f->tamanho++;

    printf("Inseriu\n");
}

int dequeue(Fila *f)
{
    if (q_empty(f))
    {
        printf("Fila vazia\n");
        exit(1);
    }

    Node *temp = f->inicio;
    int valor = temp->valor;
    f->inicio = f->inicio->prox;

    if (f->inicio == NULL)
    {
        f->fim = NULL;
    }

    free(temp);
    f->tamanho--;

    return valor;
}

int peek(Fila *f)
{
    if (q_empty(f))
    {

        printf("Fila vazia\n");
        exit(0);
    }

    return f->inicio->valor;
}

void concatena(Fila *A, Fila *B)
{
    if (A->inicio == NULL)
        return;
    if (B->inicio == NULL)
        return;

    A->fim->prox = B->inicio;
    A->fim = B->fim;
    A->tamanho += B->tamanho;

    B->inicio = NULL;
    B->fim = NULL;
    B->tamanho = 0;
}