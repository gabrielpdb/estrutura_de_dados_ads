/*  Escreva um programa em linguagem C que solicita ao usuário a quantidade de elementos inteiros que deseja ordenar.  Depois de ler os valores em uma função, ordene em ordem crescente(em outra função). Desenvolva um módulo para imprimir o vetor ordenado.

Obs: não deve ocorrer desperdício de  memória; e após ser utilizada a memória deve ser devolvida.  */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int *Aloca_Vetor(int tamanho);
void Libera_Vetor(int *vet);
void Le_Vetor(int *vet, int tamanho);
void Mostra_Vetor(int *vet, int tamanho);
void Ordena_Vetor(int *vet, int tamanho);

main(void)
{
    int tamanho, *vetor;

    printf("Informe o tamanho do vetor: ");
    scanf("%d", &tamanho);

    vetor = Aloca_Vetor(tamanho);

    Le_Vetor(vetor, tamanho);
    Mostra_Vetor(vetor, tamanho);
    Ordena_Vetor(vetor, tamanho);
    Mostra_Vetor(vetor, tamanho);

    Libera_Vetor(vetor);
}

int *Aloca_Vetor(int tamanho)
{
    int *vet;

    vet = (int *)calloc(tamanho, sizeof(int));

    if (!vet)
    {
        printf("Memória insuficiente!");
        exit(1);
    }

    return vet;
}

void Libera_Vetor(int *vet)
{
    free(vet);
}

void Le_Vetor(int *vet, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("[%d]: ", i);
        scanf("%d", &*(vet + i));
    }
}

void Mostra_Vetor(int *vet, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("[%d]: %d\n", i, vet[i]);
    }
}

void Ordena_Vetor(int *vetor, int tamanho)
{
    int temp;
    for (int i = 0; i < tamanho - 1; i++)
    {
        for (int j = 0; j < tamanho - 1; j++)
        {
            if (vetor[j] > vetor[j + 1])
            {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}
