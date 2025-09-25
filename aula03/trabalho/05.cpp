/* 5. Implemente uma função que tenha como valor de retorno um ponteiro para o último n de uma lista encadeada que contém um determinado valor inteiro x. Imprima o último elemento. Essa função deve obedecer ao protótipo:
    Lista2* ultimo_x (Lista2* l, int x); */

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
void imprimeUm(Lista *l);
void libera(Lista *l);
Lista *ultimo_x(Lista *l, int x);

main(void)
{
    Lista *listaNumeros;

    listaNumeros = inicializa();

    listaNumeros = insere(listaNumeros, 50);
    listaNumeros = insere(listaNumeros, 40);
    listaNumeros = insere(listaNumeros, 30);
    listaNumeros = insere(listaNumeros, 20);
    listaNumeros = insere(listaNumeros, 10);

    imprime(listaNumeros);

    Lista *ultimo = ultimo_x(listaNumeros, 40);
    printf("Último \n");
    imprimeUm(ultimo);

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

void imprimeUm(Lista *l)
{
    printf("info: %d\n", l->info);
    printf("prox: %d\n", l->prox);
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

Lista *ultimo_x(Lista *l, int x)
{
    Lista *p = l;
    Lista *retorno;

    while (p != NULL)
    {
        if (p->info == x)
        {
            retorno = p;
        }
        p = p->prox;
    }

    return retorno;
}