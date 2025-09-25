/* 1. Crie um programa “lse.cpp” contendo as seguintes funções:
    a) Inserção no início;
    b) Inserção no final;
    c) Remoção de um elemento v passado como parâmetro;
    d) Busca de um elemento v;
    e) Listagem dos elementos contidos na lista;
    f) Liberar a memória alocada. */

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
Lista *insereInicio(Lista *l, int valor);
Lista *insereFinal(Lista *l, int valor);
Lista *removeElemento(Lista *l, int v);
Lista *busca(Lista *l, int v);
void imprime(Lista *l);
void libera(Lista *l);

main(void)
{
    Lista *listaNumeros, *tmp;

    listaNumeros = inicializa();

    listaNumeros = insereInicio(listaNumeros, 50);
    listaNumeros = insereInicio(listaNumeros, 40);
    listaNumeros = insereInicio(listaNumeros, 30);
    listaNumeros = insereInicio(listaNumeros, 20);
    listaNumeros = insereInicio(listaNumeros, 10);
    listaNumeros = insereFinal(listaNumeros, 60);

    imprime(listaNumeros);

    tmp = busca(listaNumeros, 20);

    if (tmp != NULL)
    {
        printf("O valor foi encontrado: %d\n", tmp->info);
    }
    else
    {
        printf("O valor nao foi encontrado\n");
    }

    listaNumeros = removeElemento(listaNumeros, 30);

    imprime(listaNumeros);

    libera(listaNumeros);
}

Lista *inicializa(void)
{
    return NULL;
}

Lista *insereInicio(Lista *l, int valor)
{
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    novo->info = valor;
    novo->prox = l;
    return novo;
}

Lista *insereFinal(Lista *l, int valor)
{
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    novo->info = valor;
    novo->prox = NULL;

    if (l == NULL)
    {
        return novo;
    }

    Lista *p = l;
    while (p->prox != NULL)
    {
        p = p->prox;
    }

    p->prox = novo;
    return l;
}

void imprime(Lista *l)
{
    Lista *p;
    for (p = l; p != NULL; p = p->prox)
    {
        printf("info: %d\n", p->info);
    }
}

Lista *busca(Lista *l, int valor)
{
    Lista *p;
    for (p = l; p != NULL; p = p->prox)
    {
        if (p->info == valor)
        {
            return p;
        }
    }

    return NULL;
}

Lista *removeElemento(Lista *l, int v)
{
    Lista *ant = NULL;
    Lista *p = l;

    while (p != NULL && p->info != v)
    {
        ant = p;
        p = p->prox;
    }

    if (p == NULL)
    {
        return l;
    }

    if (ant == NULL)
    {
        l = p->prox;
    }
    else
    {
        ant->prox = p->prox;
    }

    free(p);
    return l;
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