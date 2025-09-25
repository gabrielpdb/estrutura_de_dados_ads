/* 4. Implemente uma função que receba como parâmetros uma lista encadeada e dois caracteres (original e novo) e troque todas as ocorrências do caractere original pelo caractere novo. Essa função deve obedecer ao protótipo:
    void troca (Lista2* l, char original, char novo); */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct lista
{
    char info;
    struct lista *prox;
};

typedef struct lista Lista;

Lista *inicializa(void);
Lista *insere(Lista *l, char valor);
void imprime(Lista *l);
void libera(Lista *l);
void troca(Lista *l, char original, char novo);

main(void)
{
    Lista *listaChar;

    listaChar = inicializa();

    listaChar = insere(listaChar, 'A');
    listaChar = insere(listaChar, 'B');
    listaChar = insere(listaChar, 'C');
    listaChar = insere(listaChar, 'D');
    listaChar = insere(listaChar, 'E');
    listaChar = insere(listaChar, 'C');
    listaChar = insere(listaChar, 'C');

    imprime(listaChar);
    troca(listaChar, 'C', 'X');
    printf("Trocado\n");
    imprime(listaChar);

    libera(listaChar);
}

Lista *inicializa(void)
{
    return NULL;
}

Lista *insere(Lista *l, char valor)
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
        printf("info: %c\n", p->info);
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

void troca(Lista *l, char original, char novo)
{
    Lista *p = l;

    while (p != NULL)
    {
        if (p->info == original)
        {
            p->info = novo;
        }
        p = p->prox;
    }
}
