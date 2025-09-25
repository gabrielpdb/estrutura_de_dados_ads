#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct LISTA
{
    int codigo;
    char nome[50];
    int idade;
    LISTA *proximo;
};

void mostra(LISTA *i)
{
    LISTA *p;
    p = i;
    while (p != NULL)
    {
        printf("\nCod: %d - Nome: %s - Idade: %d", p->codigo, p->nome, p->idade);
        p = p->proximo;
    }
}

void aloca(LISTA *i)
{
    LISTA *p, *novo;
    p = i;
    while (p->proximo != NULL)
        p = p->proximo;
    novo = (LISTA *)malloc(sizeof(LISTA));
    printf("\ndigite codigo: ");
    scanf("%d", &novo->codigo);
    printf("\ndigite nome: ");
    fflush(stdin);
    gets(novo->nome);
    printf("\ndigite idade: ");
    scanf("%d", &novo->idade);
    novo->proximo = NULL;
    p->proximo = novo;
}

main()
{
    LISTA *inicio;
    int i;
    inicio = (LISTA *)malloc(sizeof(LISTA)); // inseri um elemento na lista
    printf("\ndigite codigo: ");
    scanf("%d", &inicio->codigo);
    printf("\ndigite nome: ");
    fflush(stdin);
    gets(inicio->nome);
    printf("\ndigite idade: ");
    scanf("%d", &inicio->idade);
    inicio->proximo = NULL;
    // insere outros registros
    for (i = 0; i < 3; i++)
        aloca(inicio); // insere outros elementos na lista atraves do m�dulo aloca
    mostra(inicio);

    system("pause");
}