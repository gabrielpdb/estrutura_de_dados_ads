/*  Desenvolva um programa que calcule a soma  de duas matrizes MxN de números reais (double). A implementação deste programa  deve considerar as dimensões fornecida pelo  usuário (Dica: represente a matriz através de  variáveis do tipo double , usando alocação dinâmica de memória). Apos desaloque a memória utilizada. */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

double **Aloca_Matriz(int lin, int col);
void Libera_Matriz(double **mat, int l);
void LeMatriz(double **mat, int lin, int col);
void MostraMatriz(double **mat, int lin, int col);
void Soma_Matriz(double **mat1, double **mat2, double **matResult, int lin, int col);

main(void)
{
    double **matriz1, **matriz2, **matrizSoma;
    int linhas, colunas;

    printf("Número de linhas das matrizes: ");
    scanf("%d", &linhas);
    printf("Número de colunas das matrizes: ");
    scanf("%d", &colunas);

    matriz1 = Aloca_Matriz(linhas, colunas);
    LeMatriz(matriz1, linhas, colunas);
    MostraMatriz(matriz1, linhas, colunas);

    matriz2 = Aloca_Matriz(linhas, colunas);
    LeMatriz(matriz2, linhas, colunas);
    MostraMatriz(matriz2, linhas, colunas);

    matrizSoma = Aloca_Matriz(linhas, colunas);
    Soma_Matriz(matriz1, matriz2, matrizSoma, linhas, colunas);
    MostraMatriz(matrizSoma, linhas, colunas);

    Libera_Matriz(matriz1, linhas);
    Libera_Matriz(matriz2, linhas);
    Libera_Matriz(matrizSoma, linhas);
}

double **Aloca_Matriz(int lin, int col)
{
    double **matriz;

    matriz = (double **)calloc(lin, sizeof(double *));

    if (matriz == NULL)
    {
        printf("Memória insuficiente!");
        exit(-1);
    }
    for (int i = 0; i < lin; i++)
    {
        matriz[i] = (double *)calloc(col, sizeof(double));
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

void Libera_Matriz(double **mat, int lin)
{
    for (int i = 0; i < lin; i++)
    {
        free(mat[i]);
    }

    free(mat);
}

void LeMatriz(double **mat, int lin, int col)
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

void MostraMatriz(double **mat, int lin, int col)
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

void Soma_Matriz(double **mat1, double **mat2, double **matResult, int lin, int col)
{
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matResult[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}