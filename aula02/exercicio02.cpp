/* Crie um programa em Linguagem C que conte os dígitos de um determinado número usando recursão.

Observação: se o usuário inserir o número 250, a saída esperada deve ser : o número digitado tem 3 dígitos. */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int contaDigito(int v)
{
    if (v < 10 && v > -10)
    {
        return 1;
    }
    else
    {
        return 1 + contaDigito(v / 10);
    }
}

main(void)
{
    int n;

    printf("Informe o número: ");
    scanf("%d", &n);

    printf("Tem %d dígitos", contaDigito(n));
}