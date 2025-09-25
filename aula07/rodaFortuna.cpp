#include <stdio.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>

struct no
{
    int valor;
    struct no *ant;
    struct no *prox;
};
typedef struct no No;

typedef struct
{
    No *cabeca;
} DEQUE;

DEQUE *cria(void)
{
    DEQUE *d = (DEQUE *)malloc(sizeof(DEQUE));
    d->cabeca = (No *)malloc(sizeof(No));
    d->cabeca->prox = d->cabeca;
    d->cabeca->ant = d->cabeca;
    return d;
}

int tamanho(DEQUE *d)
{
    // Avançando pelo primeiro nodo
    No *end = d->cabeca->prox;
    int tam = 0;
    while (end != d->cabeca)
    {
        tam++;
        end = end->prox;
    }
    return tam;
}

int tamanho2(DEQUE *d)
{
    // Avançando pelo último nodo
    No *end = d->cabeca->ant;
    int tam = 0;
    while (end != d->cabeca)
    {
        tam++;
        end = end->ant;
    }
    return tam;
}

void exibirDequeFim(DEQUE *d)
{
    No *end = d->cabeca->ant;
    while (end != d->cabeca)
    {
        if (end->valor > 0)
        {
            printf(" ");
        }
        if (end->valor < 10 && end->valor > 0)
        {
            printf("0");
        }
        printf("%i ", end->valor);
        if (end->valor > -10 && end->valor < 0)
        {
            printf("0");
        }
        end = end->ant;
    }
    printf("\n");
}

void mostrarSeletor(DEQUE *d, No *seletor)
{
    No *end = d->cabeca->ant;
    while (end != d->cabeca)
    {
        if (end == seletor)
        {
            printf(" ** ");
        }
        else
        {
            printf("    ");
        }

        end = end->ant;
    }
    printf("\n");
}

bool inserirDequeFim(DEQUE *d, int valor)
{
    No *novo = (No *)malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = d->cabeca;
    novo->ant = d->cabeca->ant;
    d->cabeca->ant = novo;
    novo->ant->prox = novo;
    return true;
}

int excluirElemDequeInicio(DEQUE *d)
{
    int valorRetorno;

    if (d->cabeca->prox == d->cabeca)
        return false;
    No *apagar = d->cabeca->prox;
    valorRetorno = apagar->valor;
    d->cabeca->prox = apagar->prox;
    apagar->prox->ant = d->cabeca;
    free(apagar);
    return valorRetorno;
}

void reinicializarDeque(DEQUE *d)
{
    No *end = d->cabeca->prox;
    while (end != d->cabeca)
    {
        No *apagar = end;
        end = end->prox;
        free(apagar);
    }
    d->cabeca->prox = d->cabeca;
    d->cabeca->ant = d->cabeca;
}

void preencheRoda(DEQUE *d)
{
    for (int i = 0; i < 15; i++)
    {
        int valor = rand() % 100; // número de 0 a 99
        if (rand() % 2 == 0)      // 50% de chance de negativo
            valor = -valor;
        inserirDequeFim(d, valor);
    }
}

void girar(DEQUE *d, No **seletor)
{
    int forca = rand() % 14 + 1;

    No *end = *seletor;
    for (int i = 0; i < forca; i++)
    {
        end = end->ant;
        if (end == d->cabeca)
            end = end->ant;
    }

    *seletor = end;
}

int main(void)
{
    DEQUE *roda;

    roda = cria();
    preencheRoda(roda);
    No *seletor = roda->cabeca->ant;
    bool sair = false;
    int escolha;
    int pontuacao = 0;

    printf("Bem vindo a Roda da Fortuna!\n");
    printf("\\/ Eis aqui a Roda \\/\n");
    do
    {
        exibirDequeFim(roda);
        mostrarSeletor(roda, seletor);
        printf("Sua pontuacao: %d\n\n", pontuacao);
        printf("O que deseja fazer?\n");
        printf("1 - Jogar\n");
        printf("2 - Sair\n");
        scanf("%d", &escolha);
        if (escolha == 1)
        {
            girar(roda, &seletor);
            pontuacao += seletor->valor;
        }
        else if (escolha == 2)
        {
            sair = true;
        }
        else
        {
            system("cls");
            printf("Opcao invalida!\n");
        }
    } while (!sair);
}