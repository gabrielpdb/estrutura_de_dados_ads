/* Faça uma rotina recursiva para calcular a somatória de todos os números de 1 a N (N será lido do teclado).

Observação: se N é igual a 5 por exemplo, A somatória dos números será igual a 15, ou seja, 1+2+3+4+5 = 15 . */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int soma(int n);

int soma(int n)
{
    if (n == 1)
    {
        return n;
    }
    else
    {
        return n + soma(n - 1);
    }
}

main(void)
{
    int n;

    printf("Informe o N da soma: ");
    scanf("%d", &n);

    printf("A soma é: %d", soma(n));
}