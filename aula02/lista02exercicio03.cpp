/* Faça um programa que tenha uma função que receba um valor inteiro do main como referência e retorne o resto da divisão deste número por 10.  Imprima o resultado no main. */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

int resto(int *v)
{
    return *v % 10;
}

main(void)
{
    int v = 58;

    printf("Resto: %d", resto(&v));
}
