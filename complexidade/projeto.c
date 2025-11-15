#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Ler arquivo de exemplos
char *read_file(const char *path) {
	// Abre arquivo em modo binário de leitura
	FILE *f = fopen(path, "rb");
	if (!f) return NULL;
	
	fseek(f, 0, SEEK_END); // Vai pro fim do arquivo
	long size = ftell(f); // Pega o tamanho do arquivo
	fseek(f,0,SEEK_SET); // Volta pro início do arquivo
	
	char *buffer = malloc(size + 1); // Cria uma string para armazenar o conteúdo do arquivo
	if (!buffer) {
		fclose(f);
		return NULL;
	}
	
	fread(buffer, 1, size, f); // Preenche a string com o conteúdo do arquivo
	buffer[size] = '\0'; // Coloca o terminador
	
	fclose(f);
	return buffer;
}

// Recebe a string do arquivo e quebra cada linha no array de strings
void split_rows(char *src, char ***rows, long * count) {
	int size = strlen(src);
	
	*count = 1;
	// Conta quantas quebras existem, consequentemente, quantas linhas
	for(long i = 0; i < size; i++) { 
		if(src[i] == '\n') (*count)++;
	}

	
	*rows = malloc(sizeof(char*) * (*count));
	if(!*rows) return;
	
	int idx = 0;
	char *start = src; // Início da string
	
	for (long i = 0; i < size; i++) {
		if(src[i] == '\n') { // Procura uma quebra de linha
			src[i] = '\0'; // Troca o \n por \0 pra finalizar a linha
			
			(*rows)[idx++] = start; // Salva o início da linha
			start = src + i + 1; // Avança o start para logo depois do \0 inserido
		}
	}
	
	(*rows)[idx++] = start; // A última linha não entra no if do for porque não tem \n
	
}

void trim_rows(char **rows, int count) {
	
	for(int i = 0; i < count; i++) {
		trim_string(rows[i]);
	}
}

void trim_string(char *str) {
	if (!str || !*str) return;

    // Remove espaços do fim
    char *end = str + strlen(str) - 1;
    while (end >= str && *end == ' ')
        end--;
    *(end + 1) = '\0';

    // Remove espaços do início
    char *start = str;
    while (*start == ' ')
        start++;

    if (start != str)
        memmove(str, start, strlen(start) + 1);
}

void analyze_row(char * row) {
	bool find = false;
	printf("%s", row);
	
	char *position = strstr(row, "//");
	
	if(position != NULL) {
		find = true;
	}
	
	if(find) {
		printf("\nACHOU\n");
	} else {
		printf("\nNAO ACHOU\n");
	}
}

void print_rows(char **rows, int count) {
	printf("\n");
	for(int i = 0; i < count; i++) {
		printf("Linha [%d]:%s\n", i, rows[i]);
	}
}


main()
{
	char *src = read_file("exemplosTeste.c");
	if(!src) {
		printf("Erro ao abrir arquivo de exemplos");
		return 1;
	}
	
	char **rows = NULL;
	long count = 0;
	split_rows(src, &rows, &count);
	print_rows(rows, count);
	trim_rows(rows, count);
	print_rows(rows, count);
	
	analyze_row(rows[0]);
	
	
	
	free(src);
	
	return 0;
    
}
