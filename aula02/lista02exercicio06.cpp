/* O que há de errado com o seguinte trecho de código?

char *a, *b;
a = "abacate";
b = "uva";
if (a < b)
   printf ("%s vem antes de %s no dicionário", a, b);
else
   printf ("%s vem depois de %s no dicionário", a, b); */

/* O teste condicional a < b está comparando os endereços de memória onde estão armazenados os valores de a e b. O retorno desse teste é imprevisível pois depende de onde o computador alocou o dado naquele momento de execução e pode variar. */