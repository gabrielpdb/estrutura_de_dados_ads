#include <stdio.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>

struct data
{
    int dia;
    int mes;
};
typedef struct data Data;

struct contato
{
    char nome[40];
    char telefone[15];
    char celular[15];
    char email[40];
    Data dataAniversario;
};
typedef struct contato Contato;

struct elemento
{
    Contato info;
    struct elemento *prox;
};
typedef struct elemento Elemento;

int menu();
Elemento *cria_agenda();
void insere_contato(Elemento **agenda);
void exibe_contato(Contato contato);
void lista_contatos(Elemento *agenda);
Elemento *busca_contato(Elemento *agenda);
void remove_contato(Elemento **agenda);
void atualiza_contato(Elemento **agenda);
void remove_duplicados(Elemento **agenda);
void libera_agenda(Elemento *agenda);

int main(void)
{
    Elemento *agenda;
    agenda = cria_agenda();
    bool sair = false;

    do
    {
        switch (menu())
        {
        case 7:
            libera_agenda(agenda);
            sair = true;
            break;
        case 1:
            insere_contato(&agenda);
            break;
        case 2:
            lista_contatos(agenda);
            break;
        case 3:
        {
            Elemento *encontrado = busca_contato(agenda);
            if (encontrado != NULL)
            {
                exibe_contato(encontrado->info);
                getch();
            }
            else
            {
                printf("Contato nao encontrado!");
                getch();
            }
            break;
        }
        case 4:
            atualiza_contato(&agenda);
            break;
        case 5:
            remove_contato(&agenda);
            break;
        case 6:
            remove_duplicados(&agenda);
        }
        system("cls");
    } while (!sair);
}

int menu()
{
    int opt;
    do
    {
        printf("Bem vindo a Agenda!\n\n");
        printf("1 - Inserir contato\n");
        printf("2 - Listar contatos\n");
        printf("3 - Buscar contato\n");
        printf("4 - Editar contato\n");
        printf("5 - Remover contato\n");
        printf("6 - Remover contatos duplicados\n");
        printf("7 - Sair\n");
        scanf("%d", &opt);

        if (opt < 0 || opt > 7)
        {
            system("cls");
            printf("Opcao invalida, tente novamente\n\n");
        }

    } while (opt < 0 || opt > 7);
    return opt;
}

Elemento *cria_agenda()
{
    return NULL;
}

void insere_contato(Elemento **agenda)
{

    Contato novo;

    system("cls");
    printf("Inserir contato\n\n");

    printf("Nome: ");
    scanf("%s", novo.nome);
    printf("Telefone: ");
    scanf("%s", novo.telefone);
    printf("Celular: ");
    scanf("%s", novo.celular);
    printf("Email: ");
    scanf("%s", novo.email);
    printf("Dia de aniversario: ");
    scanf("%d", &novo.dataAniversario.dia);
    printf("Mes de aniversario: ");
    scanf("%d", &novo.dataAniversario.mes);

    Elemento *atual = *agenda;
    Elemento *anterior = NULL;
    Elemento *novoElemento = (Elemento *)malloc(sizeof(Elemento));
    novoElemento->info = novo;

    while (atual != NULL && strcmp(atual->info.nome, novo.nome) < 0)
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior == NULL)
    {
        novoElemento->prox = *agenda;
        *agenda = novoElemento;
    }
    else
    {
        anterior->prox = novoElemento;
        novoElemento->prox = atual;
    }
}

void exibe_contato(Contato contato)
{
    printf("Nome: %s\n", contato.nome);
    printf("Telefone: %s\n", contato.telefone);
    printf("Celular: %s\n", contato.celular);
    printf("Email: %s\n", contato.email);
    printf("Dia de aniversario: %d\n", contato.dataAniversario.dia);
    printf("Mes de aniversario: %d\n", contato.dataAniversario.mes);
}

void lista_contatos(Elemento *agenda)
{
    Elemento *atual = agenda;

    while (atual != NULL)
    {
        printf("1\n");
        exibe_contato(atual->info);
        atual = atual->prox;
    }

    getch();
}

Elemento *busca_contato(Elemento *agenda)
{
    char busca[40];
    printf("Qual contato voce deseja buscar? ");
    scanf("%s", busca);

    Elemento *p = agenda;

    while (p != NULL)
    {
        if (strcmp(p->info.nome, busca) == 0)
        {
            return p;
        }

        p = p->prox;
    }

    return NULL;
}

void remove_contato(Elemento **agenda)
{
    char busca[40];
    printf("Qual contato voce deseja remover? ");
    scanf("%s", busca);

    Elemento *atual = *agenda;
    Elemento *anterior = NULL;

    while (atual != NULL && strcmp(atual->info.nome, busca) != 0)
    {

        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL)
    {
        if (anterior == NULL)
        {
            *agenda = atual->prox;
        }
        else
        {

            anterior->prox = atual->prox;
        }
        free(atual);
        printf("Contato removido!");
        getch();
    }
    else
    {
        printf("Contato nao encontrado!");
        getch();
    }
}

void atualiza_contato(Elemento **agenda)
{
    char busca[40];
    printf("Qual contato voce deseja editar? ");
    scanf("%s", busca);

    Elemento *atual = *agenda;
    Elemento *anterior = NULL;

    while (atual != NULL && strcmp(atual->info.nome, busca) != 0)
    {

        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL)
    {
        printf("Encontrado! Informe os dados atualizados:\n");
        printf("Nome: ");
        scanf("%s", atual->info.nome);
        printf("Telefone: ");
        scanf("%s", atual->info.telefone);
        printf("Celular: ");
        scanf("%s", atual->info.celular);
        printf("Email: ");
        scanf("%s", atual->info.email);
        printf("Dia de aniversario: ");
        scanf("%d", &atual->info.dataAniversario.dia);
        printf("Mes de aniversario: ");
        scanf("%d", &atual->info.dataAniversario.mes);

        printf("Atualizado com sucesso!");
        getch();
    }
    else
    {
        printf("Contato nao encontrado!");
        getch();
    }
}

void libera_agenda(Elemento *agenda)
{
    Elemento *p = agenda;
    while (p != NULL)
    {
        Elemento *t = p->prox;
        free(p);
        p = t;
    }
}

void remove_duplicados(Elemento **agenda)
{
    Elemento *atual = *agenda;

    while (atual != NULL && atual->prox != NULL)
    {
        if (strcmp(atual->info.nome, atual->prox->info.nome) == 0)
        {
            Elemento *dup = atual->prox;
            atual->prox = dup->prox;
            free(dup);
        }
        else
        {
            atual = atual->prox;
        }
    }
}