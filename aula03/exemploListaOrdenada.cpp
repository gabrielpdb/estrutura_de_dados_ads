// programa que gerencia uma lista em memoria
// mant�m a lista ordenada em ordem alfab�tica crescente
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
void alocaOrdenado(LISTA *lista, DADOS info);
void mostralista(LISTA *lista);
DADOS lerElemento();
char menu();
int existe(LISTA *lista, DADOS info);
void exclui(LISTA *lista, DADOS info);

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
                if (existe(inicio, informa) == 0)
                    alocaOrdenado(inicio, informa);
                else
                    printf("\nCodigo ou Nome de Pessoa ja existe\n");
                system("pause");
            }
            break;
        case 'E':
            printf("\nE - excluir elemento\n");
            if (inicio == NULL)
            {
                printf("\nLista nao inicializada\n");
                system("pause");
            }
            else
            {
                informa = lerElemento();
                if (existe(inicio, informa) == 0)
                    printf("\nPessoa nao EXISTE!\n");
                else
                    exclui(inicio, informa);
                system("pause");
            }
            break;
        case 'M':
            printf("\nM - mostra lista\n");
            if (inicio == NULL)
                printf("\n Lista Vazia \n ");
            else
                mostralista(inicio);
            printf("\n");
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
    printf("Sistema de Gerencia de LISTA\n\n");
    printf("\nI - inicializa lista");
    printf("\nN - novo lista");
    printf("\nE - excluir elemento");
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
void alocaOrdenado(LISTA *lista, DADOS info)
{
    NODO *p, *q, *n; // n � o ponteiro para alocar o novo lista
    int incluiu = 0;
    n = (NODO *)malloc(sizeof(NODO));
    n->codigo = info.codigo;
    strcpy(n->nome, info.nome);
    n->proximo = NULL;
    if (lista->inicio != NULL)
    {
        p = lista->inicio; // p � o ponteiro para navega��o na lista
        if (strcmp(info.nome, p->nome) < 0)
        { // verifica se o novo elemento � menor que o primeiro da lista
            n->proximo = lista->inicio;
            lista->inicio = n;
            lista->qtd = lista->qtd + 1;
        }
        else
        {
            q = p->proximo; // q � o ponteiro do pr�ximo
            while ((q != NULL) && (incluiu == 0))
            {
                if (strcmp(info.nome, q->nome) < 0)
                {                // elemento novo fica entre ponteiro p e q
                    incluiu = 1; // indica que incluiu novo nodo
                    n->proximo = q;
                    p->proximo = n;
                    lista->qtd = lista->qtd + 1;
                }
                p = p->proximo;
                q = p->proximo;
            }
            if (incluiu == 0)
            { // indica que novo nodo ser� incluido no fim
                p->proximo = n;
                lista->fim = n;
                lista->qtd = lista->qtd + 1;
            }
        } // fim while
    }
    else
    { // inclui primeiro nodo da lista
        lista->inicio = n;
        lista->fim = n;
        lista->qtd = 1;
    }
}

// aloca novo lista na lista
void mostralista(LISTA *lista)
{
    NODO *p;
    int conta = 0;
    p = lista->inicio; // p � o ponteiro para navega��o na lista
    printf("\n\nCadastradas na lista: %d pessoas\n\n", lista->qtd);
    while (p != NULL)
    {
        conta++;
        printf("\nDados Pessoa[%d]\n", conta);
        printf("\nCodigo: %d", p->codigo);
        printf("\nNome: %s\n", p->nome);
        p = p->proximo; // navega��o na lista, p recebe o ponteiro do pr�ximo
    }
}

DADOS lerElemento()
{
    DADOS info;
    printf("\nINFORMANDO DADOS: \n");
    printf("\nDigite o codigo: ");
    scanf("%d", &info.codigo);
    printf("\nDigite o nome: ");
    fflush(stdin);
    gets(info.nome);
    return (info);
}

int existe(LISTA *lista, DADOS info)
{
    NODO *p;
    p = lista->inicio;
    while (p != NULL)
        if ((p->codigo == info.codigo) || (strcmp(p->nome, info.nome) == 0))
            return (1);
        else
            p = p->proximo;
    return (0);
}

void exclui(LISTA *lista, DADOS info)
{
    NODO *p, *q;
    int sai = 0;
    p = lista->inicio;
    if (lista->inicio != NULL) // lista n�o est� vazia
        if (lista->inicio == lista->fim)
        { // lista tem somente um elemento
            free(p);
            lista->inicio = NULL;
            lista->fim = NULL;
            lista->qtd = 0;
        }
        else // inicio � diferente de fim
        {
            if (((p->codigo == info.codigo) ||
                 (strcmp(p->nome, info.nome) == 0)) &&
                (lista->inicio == p))
            {
                // removendo primeiro elemento da lista
                lista->inicio = p->proximo;
                lista->qtd = lista->qtd - 1;
                free(p);
            }
            else
            {
                q = p->proximo;
                while ((sai == 0) && (q != NULL))
                {
                    if ((q->codigo == info.codigo) || (strcmp(q->nome, info.nome) == 0))
                    {
                        // ser� excluido o nodo q
                        p->proximo = q->proximo; // p que aponta para q passa a apontar para quem q aponta
                        if (lista->fim == q)
                            lista->fim = p; // atualiza fim da lista se q era o �ltimo elemento
                        free(q);
                        sai = 1;
                        lista->qtd = lista->qtd - 1;
                    }
                    else
                    {
                        p = p->proximo;
                        q = p->proximo;
                    }
                } // fim while
            }
        } // fim else lista tem mais de um elemento
}
