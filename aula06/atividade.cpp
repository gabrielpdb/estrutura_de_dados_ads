#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct Node
{
    int codigo;
    char nome[50];
    int diaAniversario;
    int mesAniversario;
    struct Node *prox;
};

typedef struct
{
    Node *inicio;
    Node *fim;
    int tamanho;
} Fila;

Fila *q_init();
bool q_empty(Fila *f);
int q_size(Fila *f);
void enqueue(Fila *f, Node valor);
void dequeue(Fila *f);
Node *peek(Fila *f);
int menu();
void mostraNodo(Node *n);
void inserir(Fila *f);
void mostrarLista(Fila *principal, Fila *auxiliar);
void removerNodo(Fila *principal);
void mostraTamanhos(Fila *principal, Fila *auxiliar);
void copia(Fila *principal, Fila *auxiliar);
void transfere(Fila *principal, Fila *auxiliar);
void divide(Fila *principal, Fila *auxiliar);

int main(void)
{
    Fila *Principal = q_init();
    Fila *Auxiliar = q_init();
    bool exit = false;

    do
    {
        switch (menu())
        {
        case 0:
            exit = true;
            break;
        case 1:
            inserir(Principal);
            break;
        case 2:
            mostrarLista(Principal, Auxiliar);
            break;
        case 3:
            removerNodo(Principal);
            break;
        case 4:
            mostraTamanhos(Principal, Auxiliar);
            break;
        case 5:
            copia(Principal, Auxiliar);
            break;
        case 6:
            transfere(Principal, Auxiliar);
            break;
        case 7:
            divide(Principal, Auxiliar);
            break;
        }
    } while (!exit);

    printf("Saiu do switch\n");
}

int menu()
{
    int opt = 0;
    bool isValid = true;

    do
    {

        system("cls");
        if (!isValid)
        {
            printf("Opcao invalida, tente de novo");
        }

        printf("1 - Inserir elemento na lista\n"); // Na lista principal
        printf("2 - Mostrar a lista\n");           // Solicitar que o usuário informe qual lista mostrar (principal / auxiliar)
        printf("3 - Remover elemento da lista\n"); // Será informado um código e chamada a função para remover um elemento da lista principal
        printf("4 - Mostrar tamanho\n");           // Mostra a quantidade de elementos nas duas listas (principal / auxiliar);
        printf("5 - Copia\n");                     // Duplicar a lista principal, gerando uma nova lista igual
        printf("6 - Transfere\n");                 // Retira os elementos da lista principal, colocando na auxiliar e mantendo a ordem
        printf("7 - Divide\n");                    // A primeira metade da lista fica na principal, a outra metade vai pra auxiliar
        printf("0 - Finalizar\n");
        scanf("%d", &opt);

        if (opt < 0 || opt > 7)
        {
            isValid = false;
        }
        else
        {
            isValid = true;
            system("cls");
        }

    } while (!isValid);

    return opt;
}

Fila *q_init()
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;

    return f;
}

bool q_empty(Fila *f)
{
    return (f->tamanho == 0);
}

int q_size(Fila *f)
{
    return f->tamanho;
}

void enqueue(Fila *f, Node novo)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->codigo = novo.codigo;
    strcpy(n->nome, novo.nome);
    n->diaAniversario = novo.diaAniversario;
    n->mesAniversario = novo.mesAniversario;
    n->prox = NULL;

    if (q_empty(f))
    {
        f->inicio = n;
    }
    else
    {
        f->fim->prox = n;
    }
    f->fim = n;
    f->tamanho++;
}

void dequeue(Fila *f)
{
    if (q_empty(f))
    {
        printf("Fila vazia\n");
        exit(1);
    }

    Node *temp = f->inicio;
    f->inicio = f->inicio->prox;

    if (f->inicio == NULL)
    {
        f->fim = NULL;
    }

    free(temp);
    f->tamanho--;
}

Node *peek(Fila *f)
{
    if (q_empty(f))
    {
        printf("Fila vazia\n");
        exit(0);
    }

    return f->inicio;
}

void mostraNodo(Node *n)
{
    printf("Codigo: %d\n", n->codigo);
    printf("Nome: %s\n", n->nome);
    printf("Dia de aniversario: %d\n", n->diaAniversario);
    printf("Mes de aniversario: %d\n", n->mesAniversario);
}

void inserir(Fila *f)
{
    Node novo;

    printf("Informe o codigo: ");
    scanf("%d", &novo.codigo);
    printf("Informe o nome: ");
    scanf("%s", &novo.nome);
    printf("Informe o dia de aniversario: ");
    scanf("%d", &novo.diaAniversario);
    printf("Informe o mes de aniversario: ");
    scanf("%d", &novo.mesAniversario);

    enqueue(f, novo);
}

void mostrarLista(Fila *principal, Fila *auxiliar)
{
    int opt;
    bool exit = false;
    do
    {
        printf("Qual lista voce deseja ver?\n");
        printf("1 - Principal\n");
        printf("2 - Auxiliar\n");
        scanf("%d", &opt);
    } while (opt < 1 || opt > 2);

    switch (opt)
    {
    case 1:
    {
        if (!q_empty(principal))
        {

            Node *p = principal->inicio;
            while (p != NULL)
            {

                mostraNodo(p);
                printf("\n");
                p = p->prox;
            }
        }
        else
        {
            printf("Lista vazia\n");
            getch();
        }
        getch();
        break;
    }
    case 2:
    {
        if (!q_empty(auxiliar))
        {
            Node *q = auxiliar->inicio;
            while (q != NULL)
            {

                mostraNodo(q);
                printf("\n");
                q = q->prox;
            }
        }
        else
        {
            printf("Lista vazia\n");
            getch();
        }

        getch();
        break;
    }
    }
    getch();
}

void removerNodo(Fila *principal)
{
    if (q_empty(principal))
    {
        printf("Lista vazia\n");
        return;
    }

    int codigo;
    printf("Informe o codigo para remover: ");
    scanf("%d", &codigo);

    Node *p = principal->inicio;
    Node *anterior = NULL;

    while (p != NULL)
    {
        if (p->codigo == codigo)
        {
            if (anterior == NULL)
            { // removendo o primeiro
                principal->inicio = p->prox;
                if (principal->inicio == NULL) // lista ficou vazia
                    principal->fim = NULL;
            }
            else
            {
                anterior->prox = p->prox;
                if (p->prox == NULL) // removendo o último
                    principal->fim = anterior;
            }
            free(p);
            principal->tamanho--;
            return;
        }
        anterior = p;
        p = p->prox;
    }

    printf("Codigo nao encontrado\n");
}

void mostraTamanhos(Fila *principal, Fila *auxiliar)
{
    system("cls");
    printf("Tamanho da lista Principal: %d\n", q_size(principal));
    printf("Tamanho da lista Auxiliar: %d\n", q_size(auxiliar));
    getch();
}

void copia(Fila *principal, Fila *auxiliar)
{
    Node *p = principal->inicio;

    while (p != NULL)
    {
        Node aux;
        aux.codigo = p->codigo;
        strcpy(aux.nome, p->nome);
        aux.diaAniversario = p->diaAniversario;
        aux.mesAniversario = p->mesAniversario;
        aux.prox = NULL;

        enqueue(auxiliar, aux);

        p = p->prox;
    }
}

void transfere(Fila *principal, Fila *auxiliar)
{
    auxiliar->inicio = principal->inicio;
    auxiliar->fim = principal->fim;
    auxiliar->tamanho = principal->tamanho;
    principal->inicio = NULL;
    principal->fim = NULL;
    principal->tamanho = 0;
}

void divide(Fila *principal, Fila *auxiliar)
{
    auxiliar->inicio = NULL;
    auxiliar->fim = principal->fim;
    int metade = principal->tamanho / 2;
    auxiliar->tamanho = principal->tamanho - metade;
    principal->tamanho = metade;

    Node *p = principal->inicio;

    for (int i = 1; i < metade; i++)
    {
        p = p->prox;
    }

    principal->fim = p;
    auxiliar->inicio = p->prox;
    p->prox = NULL;
}