#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
  int dado;
  struct nodo *esquerda;
  struct nodo *direita;
} nodo;

typedef nodo *arvore;

nodo *criaElemento(int valor);
nodo *insere(nodo *a, int valor);
void infixo(nodo *a);
void prefixo(nodo *a);
void posfixo(nodo *a);
void decrescente(nodo *a);
void prefixoDesloca(nodo *a);
void prefixo_nivel(nodo *a, int nivel, char texto);
int procura(nodo *a, int valor);

int altura(nodo *a);
int nivel(nodo *a, int valor, int atual);
int grau(nodo *a, int valor);
void mostraFilhos(nodo *a, int valor);
void mostraPais(nodo *a, int valor);
void mostraAscendentes(nodo *a, int valor);
void mostraDescendentes(nodo *a, int valor);
nodo *buscaNodo(nodo *a, int valor);

int main()
{
  nodo *minha = NULL;
  int i, numero, op;
  int dados[20] = {50, 25, 75, 15, 30, 70, 80, 5, 85, 8, 36, 18, 3, 65, 73, 79, 16, 22, 27, 35};

  do
  {
    system("cls");
    printf("1- Inserir dados\n");
    printf("2- Mostrar arvore\n");
    printf("3- Percurso Infixo\n");
    printf("4- Percurso Prefixo\n");
    printf("5- Percurso Posfixo\n");
    printf("6- Ordem Decrescente\n");
    printf("7- Procurar\n");
    printf("8- Altura da arvore\n");
    printf("9- Nivel de um elemento\n");
    printf("10- Grau de um elemento\n");
    printf("11- Mostrar filhos\n");
    printf("12- Mostrar pais\n");
    printf("13- Mostrar ascendentes\n");
    printf("14- Mostrar descendentes\n");
    printf("0- Finalizar\n");
    printf("Selecione: ");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
      for (i = 0; i < 20; i++)
        minha = insere(minha, dados[i]);
      break;
    case 2:
      if (minha)
        prefixoDesloca(minha);
      break;
    case 3:
      if (minha)
        infixo(minha);
      break;
    case 4:
      if (minha)
        prefixo(minha);
      break;
    case 5:
      if (minha)
        posfixo(minha);
      break;
    case 6:
      if (minha)
        decrescente(minha);
      break;
    case 7:
      if (minha)
      {
        printf("Digite valor: ");
        scanf("%d", &numero);
        if (procura(minha, numero))
          printf("Encontrou!\n");
        else
          printf("Nao encontrou.\n");
      }
      break;
    case 8:
      printf("Altura da arvore: %d\n", altura(minha));
      break;
    case 9:
      printf("Digite valor: ");
      scanf("%d", &numero);
      printf("Nivel de %d: %d\n", numero, nivel(minha, numero, 0));
      break;
    case 10:
      printf("Digite valor: ");
      scanf("%d", &numero);
      printf("Grau de %d: %d\n", numero, grau(minha, numero));
      break;
    case 11:
      printf("Digite valor: ");
      scanf("%d", &numero);
      mostraFilhos(minha, numero);
      break;
    case 12:
      printf("Digite valor: ");
      scanf("%d", &numero);
      mostraPais(minha, numero);
      break;
    case 13:
      printf("Digite valor: ");
      scanf("%d", &numero);
      mostraAscendentes(minha, numero);
      break;
    case 14:
      printf("Digite valor: ");
      scanf("%d", &numero);
      mostraDescendentes(minha, numero);
      break;
    case 0:
      printf("Finalizando...\n");
      break;
    default:
      printf("Opcao invalida.\n");
    }
    system("pause");
  } while (op != 0);
}

nodo *criaElemento(int valor)
{
  nodo *a = (nodo *)malloc(sizeof(nodo));
  a->dado = valor;
  a->esquerda = NULL;
  a->direita = NULL;
  return a;
}

nodo *insere(nodo *a, int valor)
{
  if (a == NULL)
    return criaElemento(valor);
  if (valor < a->dado)
    a->esquerda = insere(a->esquerda, valor);
  else
    a->direita = insere(a->direita, valor);
  return a;
}

void infixo(nodo *a)
{
  if (a)
  {
    infixo(a->esquerda);
    printf("%d - ", a->dado);
    infixo(a->direita);
  }
}

void prefixo(nodo *a)
{
  if (a)
  {
    printf("%d - ", a->dado);
    prefixo(a->esquerda);
    prefixo(a->direita);
  }
}

void posfixo(nodo *a)
{
  if (a)
  {
    posfixo(a->esquerda);
    posfixo(a->direita);
    printf("%d - ", a->dado);
  }
}

void decrescente(nodo *a)
{
  if (a)
  {
    decrescente(a->direita);
    printf("%d - ", a->dado);
    decrescente(a->esquerda);
  }
}

int procura(nodo *a, int valor)
{
  if (!a)
    return 0;
  if (valor == a->dado)
    return 1;
  if (valor < a->dado)
    return procura(a->esquerda, valor);
  else
    return procura(a->direita, valor);
}

void prefixoDesloca(nodo *a)
{
  prefixo_nivel(a, 0, 'R');
}

void prefixo_nivel(nodo *a, int nivel, char texto)
{
  if (a)
  {
    for (int i = 0; i <= nivel; i++)
      printf(" ");
    printf("%c %d\n", texto, a->dado);
    prefixo_nivel(a->esquerda, nivel + 2, 'E');
    prefixo_nivel(a->direita, nivel + 2, 'D');
  }
}

int altura(nodo *a)
{
  if (a == NULL)
    return -1;
  int he = altura(a->esquerda);
  int hd = altura(a->direita);
  return (he > hd ? he : hd) + 1;
}

int nivel(nodo *a, int valor, int atual)
{
  if (a == NULL)
    return -1;
  if (a->dado == valor)
    return atual;
  if (valor < a->dado)
    return nivel(a->esquerda, valor, atual + 1);
  else
    return nivel(a->direita, valor, atual + 1);
}

int grau(nodo *a, int valor)
{
  nodo *n = buscaNodo(a, valor);
  if (!n)
    return -1;
  int grau = 0;
  if (n->esquerda)
    grau++;
  if (n->direita)
    grau++;
  return grau;
}

nodo *buscaNodo(nodo *a, int valor)
{
  if (!a)
    return NULL;
  if (a->dado == valor)
    return a;
  if (valor < a->dado)
    return buscaNodo(a->esquerda, valor);
  else
    return buscaNodo(a->direita, valor);
}

void mostraFilhos(nodo *a, int valor)
{
  nodo *n = buscaNodo(a, valor);
  if (!n)
  {
    printf("Valor nao encontrado.\n");
    return;
  }
  printf("Filhos de %d: ", valor);
  if (n->esquerda)
    printf("%d ", n->esquerda->dado);
  if (n->direita)
    printf("%d ", n->direita->dado);
  if (!n->esquerda && !n->direita)
    printf("Nao tem filhos");
  printf("\n");
}

void mostraPais(nodo *a, int valor)
{
  if (!a)
    return;
  if ((a->esquerda && a->esquerda->dado == valor) ||
      (a->direita && a->direita->dado == valor))
  {
    printf("Pai de %d: %d\n", valor, a->dado);
    return;
  }
  if (valor < a->dado)
    mostraPais(a->esquerda, valor);
  else
    mostraPais(a->direita, valor);
}

void mostraAscendentes(nodo *a, int valor)
{
  if (!a)
    return;
  if (a->dado == valor)
    return;
  if ((a->esquerda && a->esquerda->dado == valor) ||
      (a->direita && a->direita->dado == valor))
  {
    printf("%d ", a->dado);
    return;
  }
  if (valor < a->dado)
  {
    mostraAscendentes(a->esquerda, valor);
    if (procura(a->esquerda, valor))
      printf("%d ", a->dado);
  }
  else
  {
    mostraAscendentes(a->direita, valor);
    if (procura(a->direita, valor))
      printf("%d ", a->dado);
  }
}

void mostraDescendentes(nodo *a, int valor)
{
  nodo *n = buscaNodo(a, valor);
  if (!n)
  {
    printf("Valor nao encontrado.\n");
    return;
  }
  printf("Descendentes de %d: ", valor);
  if (n->esquerda)
    prefixo(n->esquerda);
  if (n->direita)
    prefixo(n->direita);
  printf("\n");
}
