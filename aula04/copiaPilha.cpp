/* Implementar função para cópia de pilha
    usando somente funções primitivas
    trabalhando com a estrutura de dados
    comparar
 */

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
Lista *copia(Lista *original, Lista *nova);

main(void)
{
    Lista *listaOriginal, *listaCopia, *tmp;

    listaOriginal = inicializa();
    listaCopia = inicializa();

    listaOriginal = insereInicio(listaOriginal, 50);
    listaOriginal = insereInicio(listaOriginal, 40);
    listaOriginal = insereInicio(listaOriginal, 30);
    listaOriginal = insereInicio(listaOriginal, 20);
    listaOriginal = insereInicio(listaOriginal, 10);
    listaOriginal = insereFinal(listaOriginal, 60);

    printf("Original\n");
    imprime(listaOriginal);
    listaCopia = copia(listaOriginal, listaCopia);
    printf("Cópia\n");
    imprime(listaCopia);

    libera(listaOriginal);
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

Lista *copia(Lista *original, Lista *nova)
{

    Lista *p = original;
    Lista *aux;

    aux = inicializa();

    while (p != NULL)
    {

        aux = insereInicio(aux, p->info);

        p = p->prox;
    }

    while (aux != NULL)
    {
        nova = insereInicio(nova, aux->info);
        aux = aux->prox;
    }

    return nova;
}