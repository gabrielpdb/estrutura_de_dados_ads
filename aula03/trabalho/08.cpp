/* 8. Duas listas com valores int, não ordenados, simplesmente encadeados, solicite para o usuário informar o numero de elementos das listas para que possa ser utilizado para saber quantos elementos devem ser lidos pelo usuário.  Apresente um programa que intercale as duas listas, de forma que a lista resultante contenha todos os elementos das duas listas. */

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
Lista *leitura(Lista *l, int n);
void imprime(Lista *l);
void libera(Lista *l);
Lista *intercala(Lista *l1, Lista *l2, Lista *lIntercalada);

main(void)
{
    Lista *lista1, *lista2, *lI;
    int n;

    lista1 = inicializa();
    lista2 = inicializa();
    lI = inicializa();

    printf("Informe quantos elementos terá cada lista: ");
    scanf("%d", &n);

    lista1 = leitura(lista1, n);
    printf("\n");
    lista2 = leitura(lista2, n);
    imprime(lista1);
    imprime(lista2);

    lI = intercala(lista1, lista2, lI);
    printf("Intercalada\n");
    imprime(lI);
}

Lista *inicializa(void)
{
    return NULL;
}

Lista *leitura(Lista *l, int n)
{
    int temp;
    for (int i = 0; i < n; i++)
    {
        Lista *novo = (Lista *)malloc(sizeof(Lista));
        printf("[%d]: ", i);
        scanf("%d", &temp);
        novo->info = temp;
        novo->prox = l;
        l = novo;
    }
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

Lista *intercala(Lista *l1, Lista *l2, Lista *lIntercalada)
{
    Lista *p1 = l1, *p2 = l2;
    while (p1 != NULL && p2 != NULL)
    {
        Lista *novo1 = (Lista *)malloc(sizeof(Lista));
        novo1->info = p1->info;
        novo1->prox = lIntercalada;
        lIntercalada = novo1;
        Lista *novo2 = (Lista *)malloc(sizeof(Lista));
        novo2->info = p1->info;
        novo2->prox = lIntercalada;
        lIntercalada = novo2;

        p1 = p1->prox;
        p2 = p2->prox;
    }

    return lIntercalada;
}
