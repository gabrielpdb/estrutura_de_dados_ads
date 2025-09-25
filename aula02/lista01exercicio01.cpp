/* Crie uma estrutura utilizando um vetor inteiro onde será realizada as operações de leitura, escrita, encontrar o maior valor, encontrar o menor valor, a média. Imprimir os resultados encontrados.(utilizar módulos e alocação dinâmica). Utilizar os seguinte módulos: alocar memória, leitura do vetor, escrita do vetor, encontrar elementos maior e menor, desalocar memória. */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int *Aloca_Vetor(int tam);
void Libera_Vetor(int *vet);
void Ler_Vetor(int *vet, int tamanho);
int Maior_Valor(int *vet, int tamanho);
int Menor_Valor(int *vet, int tamanho);

main(void)
{
    int tamanho, *vetor;

    system("cls");
    printf("Informe o tamanho do vetor: ");
    scanf("%d", &tamanho);

    vetor = Aloca_Vetor(tamanho);

    Ler_Vetor(vetor, tamanho);

    printf("O maior valor do vetor: %d", Maior_Valor(vetor, tamanho));

    printf("O menor valor do vetor: %d", Menor_Valor(vetor, tamanho));

    Libera_Vetor(vetor);
    getch();
}

int *Aloca_Vetor(int tam)
{
    int *v;

    v = (int *)calloc(tam, sizeof(int));
    if (!v)
    {
        printf("Erro: Memória insuficiente!");
        exit(1);
    }
    return v;
}

void Libera_Vetor(int *vet)
{
    free(vet);
}

void Ler_Vetor(int *vet, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        system("cls");
        printf("Digite o valor de [%d]: ", i);
        scanf("%d", &*(vet + i));
    }
}

int Maior_Valor(int *vet, int tamanho)
{
    int maior = *vet;
    for (int i = 1; i < tamanho; i++)
    {
        if (*(vet + i) > maior)
        {
            maior = *(vet + i);
        }
    }

    return maior;
}

int Menor_Valor(int *vet, int tamanho)
{
    int menor = *vet;
    for (int i = 1; i < tamanho; i++)
    {
        if (*(vet + i) < menor)
        {
            menor = *(vet + i);
        }
    }

    return menor;
}
