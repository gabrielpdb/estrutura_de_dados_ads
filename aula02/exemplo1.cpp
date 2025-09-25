
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int *Aloca_Vetor(int tam);
void Libera_Vetor(int *vet);
void Ler_Vetor(int *vet, int tamanho);
int Maior_Valor(int *vet, int tamanho);

main(void)
{
    int tamanho, *vetor, maiorValor;

    system("cls");
    printf("Digite a quantidade de numeros: ");
    scanf("%d", &tamanho);

    vetor = Aloca_Vetor(tamanho);

    Ler_Vetor(vetor, tamanho);

    maiorValor = Maior_Valor(vetor, tamanho);

    printf("O maior valor do vetor eh %d: ", maiorValor);

    Libera_Vetor(vetor);
    getch();
} // fim main

int *Aloca_Vetor(int tam)
{
    int *v;                              // ponteiro para o vetor
    v = (int *)calloc(tam, sizeof(int)); // Aloca tam n�meros inteiros; v pode agora ser tratado como um vetor com tam posi��es.
    if (!v)                              //(v == NULL)
    {
        printf("** Erro: Mem�ria Insuficiente **");
        exit(1);
    }
    return v; // retorna o ponteiro para o vetor
}

void Libera_Vetor(int *vet)
{
    free(vet);
}

void Ler_Vetor(int *vet, int tamanho)
{
    int i;
    for (i = 0; i < tamanho; i++)
    {
        system("cls");
        printf("Digite o valor da posicao %d: ", (i + 1));
        scanf("%d", &*(vet + i));
    }
}

int Maior_Valor(int *vet, int tamanho)
{
    int i, maiorValor;

    maiorValor = *(vet);

    for (i = 0; i < tamanho; i++)
    {
        if (maiorValor < *(vet + i))
        {
            maiorValor = *(vet + i);
        }
    }

    return maiorValor;
}
