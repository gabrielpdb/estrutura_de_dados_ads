/* Undo/Redo com duas pilhas
Enunciado. Implemente do(x), undo(), redo() usando duas pilhas: U (ações feitas) e R (ações desfeitas). do(x) limpa R. Mostre uma simulação no main. (Base: empilhar/desempilhar no topo, política LIFO.) */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct
{
    char *dados[MAX];
    int topo;
} Pilha;

void init(Pilha *p)
{
    p->topo = -1;
}

int empty(Pilha *p)
{
    return (p->topo == -1);
}

int full(Pilha *p)
{
    return (p->topo == MAX - 1);
}

void push(Pilha *p, char *valor)
{
    if (full(p))
    {
        printf("Overflow da pilha!\n");
        exit(1);
    }
    p->dados[++(p->topo)] = valor;
}

char *pop(Pilha *p)
{
    if (empty(p))
    {
        printf("Underflow da pilha!\n");
        exit(1);
    }
    return p->dados[(p->topo)--];
}

char *topo(Pilha *p)
{
    if (empty(p))
    {
        return NULL;
    }
    return p->dados[p->topo];
}

void doIt(char *acao, Pilha *undo, Pilha *redo)
{
    push(undo, acao);
    redo->topo = -1;
    printf("Ação %s feita\n", acao);
}

void undo(Pilha *undo, Pilha *redo)
{
    char *acao = pop(undo);
    push(redo, acao);
    printf("Ação %s desfeita\n", acao);
}

void redo(Pilha *undo, Pilha *redo)
{
    char *acao = pop(redo);
    push(undo, acao);
    printf("Ação %s refeita\n", acao);
}

int main()
{
    Pilha U, R;
    init(&U);
    init(&R);

    doIt("cheirar", &U, &R);
    doIt("comer", &U, &R);
    doIt("andar", &U, &R);
    doIt("olhar", &U, &R);
    doIt("falar", &U, &R);

    undo(&U, &R);
    undo(&U, &R);
    undo(&U, &R);
    undo(&U, &R);

    redo(&U, &R);
    redo(&U, &R);

    undo(&U, &R);
    undo(&U, &R);

    return 0;
}
