/* Aloque uma matriz dinamicamente e encontre o elemento minimax. Imprima no main o elemento encontrado. Utilizar os seguinte módulos: alocar memória, leitura da matriz, escrita da matriz, encontrar minimax e desalocar memória. Minimax de uma matriz é o menor elemento da linha onde se encontra o maior elemento da matriz. */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int **Aloca_Matriz(int lin, int col);
void Libera_Matriz(int **mat, int l);
void LeMatriz(int **mat, int lin, int col);
void MostraMatriz(int **mat, int lin, int col);
void EncontraMinimax(int **mat, int lin, int col);

main(void)
{
    int **matriz, linhas, colunas;

    printf("Número de linhas da matriz: ");
    scanf("%d", &linhas);
    printf("Número de colunas da matriz: ");
    scanf("%d", &colunas);

    matriz = Aloca_Matriz(linhas, colunas);

    LeMatriz(matriz, linhas, colunas);
    MostraMatriz(matriz, linhas, colunas);

    EncontraMinimax(matriz, linhas, colunas);

    Libera_Matriz(matriz, linhas);
}

int **Aloca_Matriz(int lin, int col)
{
    int **matriz;

    matriz = (int **)calloc(lin, sizeof(int *));

    if (matriz == NULL)
    {
        printf("Memória insuficiente!");
        exit(-1);
    }
    for (int i = 0; i < lin; i++)
    {
        matriz[i] = (int *)calloc(col, sizeof(int));
        if (matriz[i] == NULL)
        {
            printf("Memória insuficiente!");
            for (int j = i - 1; j >= 0; j--)
            {
                free(matriz[j]);
            }
            free(matriz);
            exit(-1);
        }
    }

    return matriz;
}

void Libera_Matriz(int **mat, int lin)
{
    for (int i = 0; i < lin; i++)
    {
        free(mat[i]);
    }

    free(mat);
}

void LeMatriz(int **mat, int lin, int col)
{
    printf("Informe os elementos da matriz");

    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("[%d][%d]: ", i, j);
            scanf("%d", &mat[i][j]);
        }
    }
}

void MostraMatriz(int **mat, int lin, int col)
{
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf(" %d ", mat[i][j]);
        }
        printf("\n");
    }
}

void EncontraMinimax(int **mat, int lin, int col)
{
    int linhaMaior = 0, minimax = 0, maior = 0;

    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {

            if (mat[i][j] > maior)
            {
                maior = mat[i][j];
                linhaMaior = i;
            }
        }
    }

    minimax = mat[linhaMaior][0];

    for (int j = 1; j < col; j++)
    {
        if (mat[linhaMaior][j] < minimax)
        {
            minimax = mat[linhaMaior][j];
        }
    }

    printf("Minimax: %d", minimax);
}