// programa que gerencia uma lista em memoria utilizando cabe�alho com header
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#define max 50
typedef char TEXTO[max];

typedef struct DADOS
{
    int codigo;
    TEXTO nome;
};

typedef struct NODO
{
    int codigo;
    TEXTO nome;
    NODO *proximo;
};

typedef struct LISTA
{
    NODO *inicio, *fim;
    int qtd;
};

LISTA *cria();
void aloca(LISTA *lista, DADOS info);
void mostralista(LISTA *lista);
DADOS lerElemento();
char menu();

main()
{

    LISTA *inicio;

    DADOS informa;
    char conf;
    char op = 'Z';
    inicio = NULL;
    while (op != 'F')
    {
        op = menu();
        switch (op)
        {
        case 'I':
            printf("\nI - inicializa lista\n");
            inicio = cria(); // aloca o in�cio da lista
            system("pause");
            break;
        case 'N':
            printf("\nN - novo lista\n");
            if (inicio == NULL)
            {
                printf("\nLista nao inicializada\n");
                system("pause");
            }
            else
            {
                informa = lerElemento();
                aloca(inicio, informa);
            }
            break;
        case 'M':
            printf("\nM - mostra lista\n");
            if (inicio == NULL)
                printf("\n Lista Vazia \n ");
            else
                mostralista(inicio);
            system("pause");
            break;

        case 'F':
            free(inicio);
            printf("\nfinalizando sistema\n");
            break;

        default:
            printf("\n opcao invalida \n");
            system("pause");
        }
    }
    printf("\n");
    system("pause");
}

char menu()
{
    system("cls");
    printf("\nI - inicializa lista");
    printf("\nN - novo lista");
    printf("\nM - mostra lista");
    printf("\nF - fim");
    printf("\nDigite opcao: ");
    fflush(stdin);
    return (toupper(getche()));
}

// fun��o que cria a lista
LISTA *cria()
{
    LISTA *p;
    p = (LISTA *)malloc(sizeof(LISTA));
    p->inicio = NULL;
    p->fim = NULL;
    p->qtd = 0;
    return (p);
}

// aloca novo lista na lista
void aloca(LISTA *lista, DADOS info)
{
    NODO *p, *n; // n � o ponteiro para alocar o novo lista

    n = (NODO *)malloc(sizeof(NODO));
    n->codigo = info.codigo;
    strcpy(n->nome, info.nome);
    n->proximo = NULL;
    if (lista->inicio == NULL)
    {
        lista->inicio = n;
        lista->fim = n;
        lista->qtd = 1;
    }
    else
    {

        // inser��o no final - uma forma de inser��o
        p = lista->inicio; // p � o ponteiro para navega��o na lista
        while (p->proximo != NULL)
            p = p->proximo; // navega��o na lista, p recebe o ponteiro do pr�ximo
        p->proximo = n;
        lista->fim = n;
        lista->qtd = lista->qtd + 1;
    }
}

// aloca novo lista na lista
void mostralista(LISTA *lista)
{
    NODO *p;
    int conta = 0;
    p = lista->inicio; // p � o ponteiro para navega��o na lista
    while (p != NULL)
    {
        conta++;
        printf("Dados [%d]\n", conta);
        printf("Codigo %d \n", p->codigo);
        printf("Nome %s \n", p->nome);
        p = p->proximo; // navega��o na lista, p recebe o ponteiro do pr�ximo
    }
}

DADOS lerElemento()
{
    DADOS info;
    printf("\nDigite o codigo: ");
    scanf("%d", &info.codigo);
    printf("\nDigite o nome: ");
    fflush(stdin);
    gets(info.nome);
    return (info);
}
