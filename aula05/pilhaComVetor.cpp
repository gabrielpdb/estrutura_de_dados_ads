#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define MAX 50

typedef struct pilha
{
    int n;
    float vet[MAX];
} Pilha;

Pilha *cria(void);
Pilha *push(Pilha *p, float v);
Pilha *pop(Pilha *p);
int vazia(Pilha *p);
void libera(Pilha *p);
void escreve(Pilha *p);

int main()
{
    Pilha *P;

    // Cria a pilha
    P = cria();

    P = push(P, 10);
    escreve(P);
    P = push(P, 11);
    P = push(P, 33);
    escreve(P);

    P = pop(P);
    escreve(P);

    getch();
}

Pilha *cria(void)
{
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    p->n = 0; /* inicializa com zero elementos */
    return p;
}

Pilha *push(Pilha *p, float v)
{
    if (p->n == MAX)
    { /* capacidade esgotada */
        printf("Capacidade da pilha estourou.\n");
        exit(1); /* aborta programa */
    }

    /* insere elemento na pr�xima posi��o livre */
    p->vet[p->n] = v;
    p->n++;
    return p;
}

Pilha *pop(Pilha *p)
{
    if (vazia(p))
    {
        printf("Pilha vazia.\n");
        exit(1); /* aborta programa */
    }
    /* retira elemento do topo */
    p->vet[p->n - 1] = 0.0;
    p->n--;
    return p;
}

int vazia(Pilha *p)
{
    return (p->n == 0);
}

void libera(Pilha *p)
{
    free(p);
}

void escreve(Pilha *p)
{
    int i;
    for (i = 0; i < p->n; i++)
    {
        printf("%f ", p->vet[i]);
    }
    printf("\n");
}
