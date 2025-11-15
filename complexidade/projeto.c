#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    BLOCK,
    PAREN,   
    BRACKET, 
    FOR,     
    WHILE,
    IF,
    FUNCTION
} ScopeType;

typedef struct {
	ScopeType type;
	int line;
} Scope;

typedef struct Node {
	Scope data;
	Node *next;
}

typedef struct {
	Node *first;
} Stack;

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

// Recebe uma string e retorna se ela é vazia. Para linhas em branco
bool is_blank(const char *s) {
    while (*s) {
        if (*s != ' ' && *s != '\t' && *s != '\r')
            return false; // Não vazia
        s++;
    }
    return true; // Vazia
}

// Recebe uma linha e verifica se tem // no início
bool is_comment_at_start(const char *s) {
    if(s == NULL) return false;
    
    // Procura por // e guarda a posição
    char *p = strstr(s, "//");
    
    // Se a posição de p for s (início), true, senão, false
    return (p == s);
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

// Recebe uma string e remove os espaços em branco no início e fim
void trim_string(char *str) {
	if (!str || !*str) return; // Se é inválida, sai

    // Remove espaços do fim
    char *end = str + strlen(str) - 1; // Ponteiro pro fim
    while (end >= str && *end == ' ')
        end--; // Recua se encontrar espaço em branco
    *(end + 1) = '\0'; // Coloca fim no último caracter

    // Remove espaços do início
    char *start = str; // Ponteiro para o início
    while (*start == ' ')
        start++; // Avança se encontrar espaço em branco

	// Se start == str, não tem espaço em branco no início
	// Se start != str, move str para start, a quantidade de bytes necessária (tamanho de start + \0)
    if (start != str)
        memmove(str, start, strlen(start) + 1);
}

// Recebe o array de strings e passa uma a uma no trim para retirar espaços em branco no início e fim
void trim_rows(char **rows, int count) {
	for(int i = 0; i < count; i++) {
		trim_string(rows[i]);
	}
}

// Exibe todas as linhas do código de uma só vez. Com quebra
void print_rows(char **rows, int count) {
	printf("\n");
	for(int i = 0; i < count; i++) {
		printf("Linha [%d]:%s\n", i+1, rows[i]);
	}
}

void analyze_rows(char **rows, int count) {
	for(int i = 0; i < count; i++) {
		if(is_blank(rows[i])) // Se a linha está em branco, pula
			continue;
			
		if(is_comment_at_start(rows[i])) // Se tem // no início, pula
			continue;
			
		printf("Linha [%d]:%s\n", i+1, rows[i]);
		
		char *p = rows[i]; // Ponteiro para o início da string
		char *end = rows[i]; // Ponteiro no início, mas que vai caminhar por cada caracter
		
		while(*end != '\0') { // Enquanto não chegar ao fim da linha, continua andando
			printf("%c\n", *end);
			
			
			
			if(*end == ' '){ // Quando acha um espaço, pega o token da vez
				int length = end - p;
				char token[256];
				strncpy(token, p, length);
				token[length] = '\0';
				
				printf("%s\n", token);
				printf("FAZ ALGUMA COISA\n\n");
				p = end;
			}
			
				
			
			end++;
				trim_string(p);
		}
		
		
		
		system("pause");
		
	}
}


int main()
{
	char *src = read_file("exemplosTeste.c");
	if(!src) {
		printf("Erro ao abrir arquivo de exemplos");
		return 1;
	}
	
	char **rows = NULL;
	long count = 0;
	split_rows(src, &rows, &count);
	trim_rows(rows, count);
	
	analyze_rows(rows, count);
	
	
	
	free(src);
	
	return 0;
    
}
