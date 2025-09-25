/* Faça um programa que chame uma função que envia como parâmetros três valores inteiros (utilizar passagem por valor )  a, b e c e retorna a posição do maior(utilizar passagem por referência para os retornos das 2 posições) e a posição do menor valor. Exemplo: Se a = 7, b = 1 e c = 5, o procedimento deve retornar 2 como a posição do menor e 1 como a posição do maior. */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void menorMaior(int a, int b, int c, int *menor, int *maior)
{

    if (a > b && a > c)
        *maior = 1;
    if (b > a && b > c)
        *maior = 2;
    if (c > a && c > b)
        *maior = 3;

    if (a < b && a < c)
        *menor = 1;
    if (b < a && b < c)
        *menor = 2;
    if (c < a && c < b)
        *menor = 3;
}

main(void)
{
    int menor, maior;
    menorMaior(3, 4, 2, &menor, &maior);

    printf("Menor: %d\n", menor);
    printf("Maior: %d\n", maior);
}
