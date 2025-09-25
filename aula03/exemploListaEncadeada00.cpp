#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct lista // Cria uma struct para armazenar um nó da lista por vez
{
    int info;           // Conteúdo do nó da lista
    struct lista *prox; // prox é um ponteiro para uma variável do tipo lista, ou seja, para o próximo item da lista
};

typedef struct lista Lista; // Serve só para não precisar escrever "struct lista" daqui pra frente, vai ser só "Lista"

Lista *inicializa(void);
Lista *insere(Lista *l, int valor);
void imprime(Lista *l);
int vazia(Lista *l);
Lista *busca(Lista *l, int v);
Lista *retira(Lista *l, int v);
void libera(Lista *l);

int main()
{
    Lista *listaNumeros;
    Lista *tmp;

    // Inicializa a lista;
    listaNumeros = inicializa();

    // Verifica se a lista esta vazia
    if (vazia(listaNumeros) == 1)
        printf("A lista esta vazia\n");
    else
        printf("A lista nao esta vazia\n");

    // Insere 5 valores
    listaNumeros = insere(listaNumeros, 10);
    listaNumeros = insere(listaNumeros, 15);
    listaNumeros = insere(listaNumeros, 20);
    listaNumeros = insere(listaNumeros, 23);
    listaNumeros = insere(listaNumeros, 34);

    // Imprime toda a lista
    imprime(listaNumeros);

    // Busca o valor 20
    tmp = busca(listaNumeros, 20);

    if (tmp != NULL)
        printf("O valor foi encontrado: %d\n", tmp->info);
    else
        printf("Valor nao encontrado\n");

    // Busca um elemento que nao existe
    tmp = busca(listaNumeros, 22);
    if (tmp != NULL)
        printf("O valor foi encontrado: %d\n", tmp->info);
    else
        printf("Valor nao encontrado\n");

    // Retira o valor 20
    listaNumeros = retira(listaNumeros, 20);

    // Imprime novamente se o valor 20
    imprime(listaNumeros);

    // Limpa a lista
    libera(listaNumeros);

    system("pause");
}

Lista *busca(Lista *l, int v)
{
    Lista *p;
    for (p = l; p != NULL; p = p->prox) // Percorre toda lista procurando o valor
        if (p->info == v)
            return p; // Retorna o valor encontrado

    return NULL; // Retorna NULL se não encontrar nada
}

int vazia(Lista *l)

{
    if (l == NULL)
        return 1;
    else
        return 0;
}

void imprime(Lista *l)
{
    Lista *p;                           // Ponteiro auxiliar para percorrer a lista
    for (p = l; p != NULL; p = p->prox) // p recebe a lista; até que p for diferente de NULL o for continua; p recebe o endereco do próximo item
        printf("info = %d\n", p->info);
}

Lista *insere(Lista *l, int valor)
{
    Lista *novo = (Lista *)malloc(sizeof(Lista)); // Aloca um novo nó
    novo->info = valor;                           // Coloca valor em info
    novo->prox = l;                               // Coloca o ponteiro da lista original no prox do novo nó
    return novo;                                  // Retorna o novo nó
}

Lista *inicializa(void) // Retorna um ponteiro para a lista. No caso, o primeiro item da lista na hora da inicialização recebe NULL
{
    return NULL;
}

Lista *retira(Lista *l, int v)
{
    Lista *ant = NULL; // Ponteiro para o elemento anterior
    Lista *p = l;      // Ponteiro para percorrer a lista

    while (p != NULL && p->info != v) // Executa enquanto o p não achar NULL e não for o valor procurado
    {
        ant = p;     // Elemento anterior recebe o atual
        p = p->prox; // Atual recebe o próximo
    }

    if (p == NULL) // p achou NULL, quer dizer que não encontrou o elemento procurado
        return l;  // Retorna lista original

    if (ant == NULL) // Se o anterior for NULL, significa que o elemento estava no início
    {
        l = p->prox; // Simplesmente passa para a lista original o próximo elemento
    }
    else // Se o anterior não for NULL, significa que o elemento estava no meio
    {
        ant->prox = p->prox; // O valor do próximo elemento no anterior recebe o próximo elemento do atual (o atual é o valor a ser removido)
    }
    free(p);  // Libera o p
    return l; // Retorna o ponteiro de início da lista, que n   ão mudou
}

void libera(Lista *l)
{
    Lista *p = l;
    while (p != NULL)
    {
        Lista *t = p->prox; // t recebe a referência do próximo item
        free(p);            // Libera a memória de p
        p = t;              // p recebe o próximo item que foi guardado antes
    }
}
