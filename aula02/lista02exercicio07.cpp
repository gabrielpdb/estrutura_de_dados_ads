/* Escreva uma função que receba um caractere c e transforme c em uma string (cadeia de caracteres), ou seja, devolva uma string de comprimento 1 tendo c como único elemento.  */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

char *devolveString(char c)
{
    static char s[1];
    s[0] = c;
    return s;
}

main(void)
{
    printf("String: %s", devolveString('u'));
}