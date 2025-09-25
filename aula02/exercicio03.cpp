/* Faça uma rotina recursiva em C para encontrar o fatorial de um número.

Por exemplo :
>> Digite o número: 5!
>> Saída do dado : 5*4*3*2*1 = 120    */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int fatorial(int v)
{
    if (v == 1)
    {
        return 1;
    }
    else
    {
        return v * fatorial(v - 1);
    }
}

main(void)
{
    int n;

    printf("Informe o número: ");
    scanf("%d", &n);

    printf("Fatorial: %d", fatorial(n));
}