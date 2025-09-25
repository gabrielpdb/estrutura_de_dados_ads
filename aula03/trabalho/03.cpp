/* 3. Escreva um algoritmo que inverta a ordem dos elementos de uma lista simplesmente encadeada. A inversão deve ser realizada de forma a não alterar a ordem física dos elementos na lista. */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct lista
{
    int info;
    struct lista *prox;
};

typedef struct lista Lista;

Lista *inicializa(void);
Lista *insere(Lista *l, int valor);
void imprime(Lista *l);
void libera(Lista *l);
Lista *inverte(Lista *l);

main(void)
{
    Lista *listaNumeros;

    listaNumeros = inicializa();

    listaNumeros = insere(listaNumeros, 50);
    listaNumeros = insere(listaNumeros, 40);
    listaNumeros = insere(listaNumeros, 30);
    listaNumeros = insere(listaNumeros, 20);
    listaNumeros = insere(listaNumeros, 10);

    printf("Normal\n");
    imprime(listaNumeros);
    listaNumeros = inverte(listaNumeros);
    printf("Invertido\n");
    imprime(listaNumeros);

    libera(listaNumeros);
}

Lista *inicializa(void)
{
    return NULL;
}

Lista *insere(Lista *l, int valor)
{
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    novo->info = valor;
    novo->prox = l;
    return novo;
}

void imprime(Lista *l)
{
    Lista *p;
    for (p = l; p != NULL; p = p->prox)
    {
        printf("info: %d\n", p->info);
    }
}

void libera(Lista *l)
{
    Lista *p = l;
    while (p != NULL)
    {
        Lista *t = p->prox;
        free(p);
        p = t;
    }
}

Lista *inverte(Lista *l)
{
    Lista *anterior = NULL;
    Lista *atual = l;
    Lista *proximo = NULL;

    while (atual != NULL)
    {
        proximo = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = proximo;
    }

    return anterior;
}
