/* Avaliador de expressão pós‑fixa Enunciado. Implemente a avaliação de expressões posfixas com inteiros e + - * /. Cada número empilha; um operador desempilha dois operandos, aplica, empilha o resultado. (Base: Top/Push/Pop no topo; política LIFO.) */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

typedef struct
{
    int dados[MAX];
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

void push(Pilha *p, int valor)
{
    if (p->topo == MAX - 1)
    {
        printf("Overflow da pilha!\n");
        exit(1);
    }
    p->dados[++(p->topo)] = valor;
}

int pop(Pilha *p)
{
    if (empty(p))
    {
        printf("Underflow da pilha!\n");
        exit(1);
    }
    return p->dados[(p->topo)--];
}

int avaliaPosfixa(const char *expr)
{
    Pilha p;
    init(&p);

    int i = 0;
    while (expr[i] != '\0')
    {
        if (isspace(expr[i]))
        {
            i++;
            continue;
        }

        if (isdigit(expr[i]))
        {
            int num = 0;
            while (isdigit(expr[i]))
            {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            push(&p, num);
        }
        else
        {
            int b = pop(&p);
            int a = pop(&p);
            int r;

            switch (expr[i])
            {
            case '+':
                r = a + b;
                break;
            case '-':
                r = a - b;
                break;
            case '*':
                r = a * b;
                break;
            case '/':
                r = a / b;
                break;
            default:
                printf("Operador invalido: %c\n", expr[i]);
                exit(1);
            }
            push(&p, r);
            i++;
        }
    }

    return pop(&p);
}

int main()
{
    char expr[] = "5 3 2 * + 4 -";
    printf("Expressao: %s\n", expr);
    int resultado = avaliaPosfixa(expr);
    printf("Resultado: %d\n", resultado);
    return 0;
}
