// Objetivo: Mostra a aloca��o de mem�ria para uma matriz bidimensional,
// Dados de entrada: Dimens�es da matriz: n�mero de linhas e de colunas
// Dados de sa�da: A matriz inicializada
#include <stdio.h>
#include <conio.h>
#include <stdlib.h> // Para usar calloc( ) , free( ) e exit( )

int **Aloca_Matriz(int lin, int col);
void Libera_Matriz(int **mat);
void LeMatriz(int **mat, int lin, int col, char *nome_mat);
void MostraMatriz(int **mat, int lin, int col, char *nome_mat);

main(void)
{
    int **pmatriz, linha, coluna;
    system("cls");
    printf("Digite o n�mero de linhas dimensoes da matriz: ");
    scanf("%d", &linha);
    printf("Digite o n�mero de linhas dimensoes da matriz: ");
    scanf("%d", &coluna);
    pmatriz = Aloca_Matriz(linha, coluna);
    LeMatriz(pmatriz, linha, coluna, "PMATRIZ");
    MostraMatriz(pmatriz, linha, coluna, "PMATRIZ");
    Libera_Matriz(pmatriz);
    getch();
} // fim main

int **Aloca_Matriz(int lin, int col)
{
    int *posicao, **mat, i;
    mat = (int **)calloc(lin, sizeof(int *)); /* um vetor de lin ponteiros para
    inteiro */
    if (mat == NULL)
    {
        printf("Memoria insuficiente.\n");
        exit(-1);
    }
    posicao = (int *)calloc(lin * col, sizeof(int)); /* um vetor de
      lin*col para inteiros */

    if (posicao == NULL)
    {
        free(mat);
        printf("Memoria insuficiente.\n");
        exit(-1);
    }
    for (i = 0; i < lin; i++)
    {
        mat[i] = &posicao[i * col]; // faz com que cada linha aponte para
                                    //  o  inicio dos elementos da coluna
    }
    return mat;
}

void LeMatriz(int **mat, int lin, int col, char *nome_mat)
{
    int i, j;
    printf("\n Digite os elementos da matriz %s \n", nome_mat);
    for (i = 0; i < lin; i++)
        for (j = 0; j < col; j++)
        {
            printf("%s[%d][%d]:", nome_mat, i, j);
            scanf("%d", &mat[i][j]);
        }
}

void MostraMatriz(int **mat, int lin, int col, char *nome_mat)
{
    int i, j;
    printf("\n Os elementos da matriz %s sao: \n", nome_mat);
    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
            printf("%d ", mat[i][j]); // printf("%d ", *(*(mat+i)+j) );
        printf("\n");
    }
}

void Libera_Matriz(int **mat)
{
    free(mat[0]); // libera o vetor "posi��o" de inteiros
    free(mat);    // libera o vetor de ponteiros p/inteiros
}
