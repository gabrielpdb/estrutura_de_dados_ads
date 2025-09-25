#include <stdio.h>

void LoopRecursivo(int passo) 
{
  if (passo < 5){
  		printf("Passo atual %d\n",passo);
	  
	  	LoopRecursivo((passo + 1));
  }
  printf("Passo atual %d\n",passo);
}

int main()
{
    LoopRecursivo(0);
   	return 0;
}
