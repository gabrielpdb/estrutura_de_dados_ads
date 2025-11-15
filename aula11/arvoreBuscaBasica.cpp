#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
  int dado;
  nodo *esquerda;
  nodo *direita;
} nodo;

typedef nodo *arvore;

// PROT�TIPO das fun��es
nodo *criaElemento();
nodo *insere(nodo *a, int valor);
void infixo(nodo *a);
void prefixo(nodo *a);
void posfixo(nodo *a);
void decrescente(nodo *a);
void prefixoDesloca(nodo *a);
void prefixo_nivel(nodo *a, int nivel, char texto);
// programa principal
main()
{
  nodo *minha, *buscar;
  minha = NULL;
  int i, numero, op, n;
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
    printf("0- Finalizar\n");
    printf("selecione: \n");
    scanf("%d", &op);
    switch (op)
    { // neste programa estamos inserindo um conjunto fixo de dados para teste
    case 1:
      for (i = 0; i < 20; i++)
      {
        numero = dados[i];
        minha = insere(minha, numero);
      }
      break;
    case 2:
      if (minha != NULL)
      {
        prefixoDesloca(minha);
      }
      break;
    case 3:
      if (minha != NULL)
      {
        infixo(minha);
      }
      break;
    case 4:
      if (minha != NULL)
      {
        prefixo(minha);
      }
      break;
    case 5:
      if (minha != NULL)
      {
        posfixo(minha);
      }
      break;
    case 6:
      if (minha != NULL)
      {
        decrescente(minha);
      }
      break;
    case 0:
      printf("finalizando...\n\n");
      break;
    default:
      printf("selecione opcao valida...\n\n");
      break;
    } // fim do switch
    system("pause");
  } while (op != 0);
}

// implementa��o das fun��es

// Cria um novo nodo, coloca o seu valor em dado, inicializa os ponteiros esquerda e direita com o valor NULL
// Retorno o endere�o da posi��o de mem�ria alocada
nodo *criaElemento(int valor)
{
  nodo *a;
  a = (nodo *)malloc(sizeof(nodo));
  a->dado = valor;
  a->esquerda = NULL;
  a->direita = NULL;
  return (a);
}

// Inclui um novo nodo na �rvore bin�ria de pesquisa
// a inclus�o respeita a regra de que os nodos:
//  a esquerda possuem valor menor que a raiz
//  a direita possuem valor maior que a raiz
//  fun��o recursiva
nodo *insere(nodo *a, int valor)
{
  if (a == NULL)
  {
    a = criaElemento(valor);
    printf("novo\n");
  }
  else if (valor <= a->dado)
  {
    printf("esquerda\n");
    a->esquerda = insere(a->esquerda, valor);
  }
  else
  {
    printf("direita\n");
    a->direita = insere(a->direita, valor);
  }
  printf("%d\n", a->dado);
  return (a);
}

// Varre e mostra todos os elementos da �rvore
// implementa o percurso infixo: SAE - Raiz - SAD
void infixo(nodo *a)
{
  if (a != NULL)
  {
    if (a->esquerda != NULL)
    {
      infixo(a->esquerda);
    }
    printf("%d - ", a->dado);
    if (a->direita != NULL)
    {
      infixo(a->direita);
    }
  }
}

// Varre e mostra todos os elementos da �rvore
// implementa o percurso prefixo: Raiz - SAE - SAD
// desloca espa�os na tela para indicar a diferen�a entre os n�veis dos nodos
void prefixoDesloca(nodo *a)
{
  prefixo_nivel(a, 0, 'R');
}
void prefixo_nivel(nodo *a, int nivel, char texto)
{
  if (a != NULL)
  {
    for (int i = 0; i <= nivel; i++)
      printf(" ");
    printf("%c %d\n", texto, a->dado);
    if (a->esquerda != NULL)
    {
      prefixo_nivel(a->esquerda, nivel + 2, 'E');
    }
    if (a->direita != NULL)
    {
      prefixo_nivel(a->direita, nivel + 2, 'D');
    }
  }
}

// ATIVIDADE - FAZER A IMPLEMENTA��O DAS FUN��ES A SEGUIR

// Varre e mostra todos os elementos da �rvore
// implementa o percurso prefixo: Raiz - SAE - SAD
void prefixo(nodo *a)
{
  // aqui voc� deve implementar a fun��o prefixo
  if (a != NULL)
  {
    printf("%d - ", a->dado);
    if (a->esquerda != NULL)
    {
      infixo(a->esquerda);
    }
    if (a->direita != NULL)
    {
      infixo(a->direita);
    }
  }
}

// Varre e mostra todos os elementos da �rvore
// implementa o percurso posfixo: SAE - SAD - Raiz
void posfixo(nodo *a)
{
  // aqui voc� deve implementar a fun��o posfixo
  if (a != NULL)
  {
    if (a->esquerda != NULL)
    {
      infixo(a->esquerda);
    }
    if (a->direita != NULL)
    {
      infixo(a->direita);
    }
    printf("%d - ", a->dado);
  }
}

// Varre e mostra todos os elementos da �rvore
// implementa o percurso infixo modificado: SAD - Raiz - SAE
void decrescente(nodo *a)
{
  // aqui voc� deve implementar a fun��o decrescente
  if (a != NULL)
  {
    if (a->direita != NULL)
    {
      infixo(a->direita);
    }
    printf("%d - ", a->dado);
    if (a->esquerda != NULL)
    {
      infixo(a->esquerda);
    }
  }
}
