// Objetivo: Mostra a aloca��o de mem�ria para uma matriz bidimensional
// Dados de entrada: Dimens�es da matriz: n�mero de linhas e de colunas
// Dados de sa�da: A matriz inicializada
#include <stdio.h>
#include <conio.h>
#include <stdlib.h> // Para usar calloc( ) , free( ) e exit( )

int **Aloca_Matriz(int lin, int col);
void Libera_Matriz(int **mat, int l);
void LeMatriz(int **mat, int lin, int col, char *nome_mat);
void MostraMatriz(int **mat, int lin, int col, char *nome_mat);

main(void)
{
    int **pmatriz, // Matriz de inteiros
        linha, coluna;

    system("cls");
    printf("Digite o n�mero de linhas dimensoes da matriz: ");
    scanf("%d", &linha);
    printf("Digite o n�mero de colunas dimensoes da matriz: ");
    scanf("%d", &coluna);
    pmatriz = Aloca_Matriz(linha, coluna);
    LeMatriz(pmatriz, linha, coluna, "matriza");
    MostraMatriz(pmatriz, linha, coluna, "PMATRIZ");
    Libera_Matriz(pmatriz, linha);
    getch();
} // fim main()

int **Aloca_Matriz(int lin, int col)
{
    int **mat;
    int i, k;

    mat = (int **)calloc(lin, sizeof(int *)); // aloca um vetor com linha
                                              //  posi��es para armazenar
                                              //  ponteiros inteiros
    if (mat == NULL)
    {
        printf("Memoria insuficiente.\n");
        exit(-1);
    }
    for (i = 0; i < lin; i++)
    {
        mat[i] = (int *)calloc(col, sizeof(int)); // aloca um vetor com //coluna
                                                  //  posi��es para inteiros, em que o endere�o � atribu�do a
                                                  // cada linha da matriz
        if (mat[i] == NULL)
        {
            printf("Memoria insuficiente.\n");
            for (k = i - 1; k >= 0; k--) // devolve os blocos alocados
                free(mat[k]);
            free(mat);
            exit(-1); // abandona a tarefa
        } // fim if
    } // fim for
    return mat;
}

void Libera_Matriz(int **mat, int lin)
{
    int i;
    for (i = 0; i < lin; i++)
        free(mat[i]); // libera o vetor de inteiros com coluna posi��es para
                      // cada linha
    free(mat);        // libera o vetor de ponteiros com linha posi��es
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
