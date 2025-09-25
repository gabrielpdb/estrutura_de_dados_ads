#include <stdlib.h>
#include <stdio.h>

struct lista
{
    int info;
    struct lista *prox;
};

typedef struct lista Lista;

Lista *insere(Lista *l, int i)
{
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    novo->info = i;
    novo->prox = l;
    return novo;
}

/* fun��o de inicializa��o: retorna uma lista vazia */

Lista *inicializa(void)
{
    return NULL;
}

/* fun��o imprime: imprime valores dos elementos */
void imprime(Lista *l)
{
    Lista *p; /* vari�vel auxiliar para percorrer a lista */
    for (p = l; p != NULL; p = p->prox)
        printf("info = %d\n", p->info);
}

/* fun��o vazia: retorna 1 se vazia ou 0 se n�o vazia */

int vazia(Lista *l)

{
    if (l == NULL)
        return 1;
    else
        return 0;
}

/* fun��o vazia: retorna 1 se vazia ou 0 se n�o vazia
// outra forma de escrever o vazio

int vazia (Lista* l)
{
return (l == NULL);
}
*/

/* fun��o busca: busca um elemento na lista */

Lista *busca(Lista *l, int v)
{
    Lista *p;
    for (p = l; p != NULL; p = p->prox)
        if (p->info == v)
            return p;
    return NULL; /* n�o achou o elemento */
}

/* fun��o retira: retira elemento da lista */

Lista *retira(Lista *l, int v)
{
    Lista *ant = NULL; /* ponteiro para elemento anterior */
    Lista *p = l;      /* ponteiro para percorrer a lista*/

    /* procura elemento na lista, guardando anterior */
    while (p != NULL && p->info != v)
    {
        ant = p;
        p = p->prox;
    }

    /* verifica se achou elemento */
    if (p == NULL)
        return l; /* n�o achou: retorna lista original */

    /* retira elemento */

    if (ant == NULL)
    {
        /* retira elemento do inicio */
        l = p->prox;
    }
    else
    {
        /* retira elemento do meio da lista */
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
        Lista *t = p->prox; /* guarda refer�ncia para o pr�ximo
                     elemento */
        free(p);            /* libera a mem�ria apontada por p */
        p = t;              /* faz p apontar para o pr�ximo */
    }
}

int main(void)
{

    Lista *l;          /* declara uma lista n�o iniciada */
    l = inicializa();  /* inicia lista vazia */
    l = insere(l, 23); /* insere na lista o elemento 23 */
    l = insere(l, 45); /* insere na lista o elemento 45 */
    l = insere(l, 56); /* insere na lista o elemento 56 */
    l = insere(l, 78); /* insere na lista o elemento 78 */
    imprime(l);        /* imprimir�: 78 56 45 23 */
    l = retira(l, 78);
    printf(" retirado elemento 78\n");
    imprime(l); /* imprimir�: 56 45 23 */
    l = retira(l, 45);
    printf(" retirado elemento 45\n");
    imprime(l); /* imprimir�: 56 23 */
    libera(l);
    system("pause");
    return 0;
}