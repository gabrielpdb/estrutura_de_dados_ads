/* 6. Implemente uma função que receba como parâmetro uma lista encadeada e um valor inteiro n, e retire da lista todas as ocorrências de n, e retorne a lista resultante. Imprima a lista atualizada. Essa função deve obedecer ao protótipo:
Lista* retira_n (Lista* l, int n); */

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
Lista *retira_n(Lista *l, int n);

main(void)
{
    Lista *listaNumeros;

    listaNumeros = inicializa();

    listaNumeros = insere(listaNumeros, 50);
    listaNumeros = insere(listaNumeros, 40);
    listaNumeros = insere(listaNumeros, 30);
    listaNumeros = insere(listaNumeros, 40);
    listaNumeros = insere(listaNumeros, 40);

    imprime(listaNumeros);

    printf("Original\n");
    listaNumeros = retira_n(listaNumeros, 40);
    printf("Retirado\n");
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

Lista *retira_n(Lista *l, int n)
{
    Lista *anterior = NULL;
    Lista *atual = l;

    while (atual != NULL)
    {
        if (atual->info == n)
        {
            if (anterior == NULL)
            {
                l = atual->prox;
                free(atual);
                atual = l;
            }
            else
            {
                anterior->prox = atual->prox;
                free(atual);
                atual = anterior->prox;
            }
        }
        else
        {
            anterior = atual;
            atual = atual->prox;
        }
    }

    return l;
}
