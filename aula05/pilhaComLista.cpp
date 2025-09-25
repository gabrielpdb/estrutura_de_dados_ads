#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct no
{
    float info;
    struct no *prox;
};

typedef struct no No;

typedef struct pilha
{
    No *prim;
} Pilha;

Pilha *cria(void);
void push(Pilha *p, float v);
float pop(Pilha *p);
int vazia(Pilha *p);
void libera(Pilha *p);
void escreve(Pilha *p);
No *ins_ini(No *l, float v);
No *ret_ini(No *l);

int main()
{
    Pilha *P;

    // Cria a pilha
    P = cria();

    push(P, 10);
    escreve(P);
    push(P, 11);
    push(P, 33);
    escreve(P);

    pop(P);
    escreve(P);

    getch();
}

Pilha *cria(void)
{
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    p->prim = NULL;
    return p;
}

No *ins_ini(No *l, float v)
{
    No *p = (No *)malloc(sizeof(No));
    p->info = v;
    p->prox = l;
    return p;
}

/* fun��o auxiliar: retira do in�cio */
No *ret_ini(No *l)
{
    No *p = l->prox;
    free(l);
    return p;
}

void push(Pilha *p, float v)
{
    p->prim = ins_ini(p->prim, v);
}

float pop(Pilha *p)
{
    float v;
    if (vazia(p))
    {
        printf("Pilha vazia.\n");
        exit(1); /* aborta programa */
    }

    v = p->prim->info;
    p->prim = ret_ini(p->prim);
    return v;
}

int vazia(Pilha *p)
{
    return (p->prim == NULL);
}

void libera(Pilha *p)
{
    No *q = p->prim;
    while (q != NULL)
    {
        No *t = q->prox;
        free(q);
        q = t;
    }
    free(p);
}

void escreve(Pilha *p)
{
    No *q;

    for (q = p->prim; q != NULL; q = q->prox)
    {
        printf("%f ", q->info);
    }
    printf("\n");
}
