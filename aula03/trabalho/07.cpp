/* 7. Escreva um algoritmo que forneça o maior elemento, o menor elemento, e a média aritmética dos elementos de uma lista simplesmente encadeada. */

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
void maiorMenorMedia(Lista *l, int *maior, int *menor, float *media);

main(void)
{
    Lista *listaNumeros;
    int maior, menor;
    float media;

    listaNumeros = inicializa();

    listaNumeros = insere(listaNumeros, 50);
    listaNumeros = insere(listaNumeros, 50);
    listaNumeros = insere(listaNumeros, 30);
    listaNumeros = insere(listaNumeros, 40);
    listaNumeros = insere(listaNumeros, 40);

    imprime(listaNumeros);

    maiorMenorMedia(listaNumeros, &maior, &menor, &media);

    printf("\nResultado\n");
    printf("Maior: %d\n", maior);
    printf("Menor: %d\n", menor);
    printf("Media: %.2f\n", media);

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

void maiorMenorMedia(Lista *l, int *maior, int *menor, float *media)
{
    Lista *p = l;
    *maior = p->info;
    *menor = p->info;
    int soma = 0, cont = 0;

    while (p != NULL)
    {
        if (p->info > *maior)
        {
            *maior = p->info;
        }
        if (p->info < *menor)
        {
            *menor = p->info;
        }
        soma += p->info;
        cont++;
        p = p->prox;
    }

    *media = soma / cont;
}
