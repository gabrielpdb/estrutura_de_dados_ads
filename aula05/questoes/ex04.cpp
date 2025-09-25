/* Delimitadores balanceados ()[]{} com pilha
Enunciado. Verifique se uma string tem parênteses/colchetes/chaves balanceados. Ao ler um abridor, empilhe; ao ler um fechador, verifique o topo e desempilhe. (Último aberto fecha primeiro — LIFO.) */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

typedef struct
{
    char dados[MAX];
    int topo;
} Pilha;

void erroBalanceamento()
{
    printf("Expressão desbalanceada!\n");
    exit(1);
}

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

char topo(Pilha *p)
{
    return p->dados[p->topo];
}

char pop(Pilha *p)
{
    if (empty(p))
    {
        printf("Underflow da pilha!\n");
        exit(1);
    }
    return p->dados[(p->topo)--];
}

void avaliaDelimitadores(const char *expr)
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

        switch (expr[i])
        {
        case '(':
            push(&p, expr[i]);
            break;
        case '[':
            push(&p, expr[i]);
            break;
        case '{':
            push(&p, expr[i]);
            break;
        case ')':
            if (topo(&p) == '(')
            {
                pop(&p);
            }
            else
            {
                erroBalanceamento();
            }
            break;
        case ']':
            if (topo(&p) == '[')
            {
                pop(&p);
            }
            else
            {
                erroBalanceamento();
            }
            break;
        case '}':
            if (topo(&p) == '{')
            {
                pop(&p);
            }
            else
            {
                erroBalanceamento();
            }
            break;

        default:
            break;
        }

        i++;
    }

    printf("Expressão balanceada");
}

int main()
{
    char expr[] = "{[(]}";
    printf("Expressao: %s\n", expr);
    avaliaDelimitadores(expr);
    return 0;
}
