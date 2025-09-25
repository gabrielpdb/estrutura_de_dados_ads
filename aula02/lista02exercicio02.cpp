/* Escreva uma função que recebe três parâmetros  A, B e C, e devolve o menor deles em A, o maior em C, e o valor do meio em B. Caso sejam  passados valores repetidos, a ordem da resposta entre eles não importa. Imprima no main os valores de A, B e C. */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void ordena(int *a, int *b, int *c)
{
    int maior, menor, meio;

    if (*a > *b && *a > *c)
        maior = *a;
    if (*b > *a && *b > *c)
        maior = *b;
    if (*c > *a && *c > *b)
        maior = *b;

    if (*a < *b && *a < *c)
        menor = *a;
    if (*b < *a && *b < *c)
        menor = *b;
    if (*c < *a && *c < *b)
        menor = *c;

    if (*a > menor && *a < maior)
        meio = *a;
    if (*b > menor && *b < maior)
        meio = *b;
    if (*c > menor && *c < maior)
        meio = *c;

    *a = menor;
    *b = meio;
    *c = maior;
}

main(void)
{
    int a = 3, b = 2, c = 1;

    ordena(&a, &b, &c);

    printf("Menor: %d\n", a);
    printf("Meio: %d\n", b);
    printf("Maior: %d\n", c);
}
