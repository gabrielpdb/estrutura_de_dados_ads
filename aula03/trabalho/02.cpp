/* 2. Implemente uma função que tenha como valor de retorno o comprimento de uma lista encadeada, isto é, calcule o número de nós da lista. Esta função deve obedecer ao protótipo:
    int comprimento (lista* l); */

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
void libera(Lista *l);
int comprimento(lista *l);

main(void)
{
    Lista *listaNumeros;

    listaNumeros = inicializa();

    listaNumeros = insere(listaNumeros, 50);
    listaNumeros = insere(listaNumeros, 40);
    listaNumeros = insere(listaNumeros, 30);
    listaNumeros = insere(listaNumeros, 20);
    listaNumeros = insere(listaNumeros, 10);

    printf("Comprimento: %d\n", comprimento(listaNumeros));

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

int comprimento(lista *l)
{
    Lista *p = l;
    int cont = 0;
    while (p != NULL)
    {
        p = p->prox;
        cont++;
    }

    return cont;
}
