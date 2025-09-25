/* Um ponteiro pode ser usado para dizer a uma função onde ela deve depositar o resultado de seus cálculos.
  Escreva uma função hm que converta minutos em horas-e-minutos.
  A função recebe um inteiro mnts e os endereços de duas variáveis inteiras, digamos h e m, e atribui valores a essas variáveis de modo que m seja menor que 60 e que 60*h + m seja igual a mnts.
  Escreva também uma função main que use a função hm. */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void hm(int mnts, int *h, int *m)
{
    *h = (mnts / 60);
    *m = (mnts % 60);
}

main(void)
{
    int mnts = 375, h, m;

    hm(mnts, &h, &m);
    printf("%d minutos = %d:%02d\n", mnts, h, m);
}
