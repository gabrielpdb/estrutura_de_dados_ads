/* Crie um programa que calcula o máximo divisor comum entre dois números usando a recursão.

Observação : Dois números naturais sempre têm divisores comuns. Assim, o máximo divisor comum entre os dois é o maior de seus divisores.

Exemplificando...os divisores comuns de 12 e 18 são 1,2,3 e 6. Dentre eles, 6 é o maior. Então, chamamos o 6 de máximo divisor comum de 12 e 18 e indicamos m.d.c.(12,18) = 6. */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int mdc(int n1, int n2)
{
    int resto = n1 % n2;
    if (resto == 0)
    {
        return n2;
    }
    else
    {
        return mdc(n2, resto);
    }
}

main(void)
{
    printf("%d", mdc(48, 18));
}