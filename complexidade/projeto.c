#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Enum dos tokens possíveis de ler
typedef enum {
    TOKEN_VOID,
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_CHAR,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_FOR,
    TOKEN_WHILE,
    TOKEN_DO,
    TOKEN_RETURN,
    TOKEN_BREAK,
    TOKEN_CONTINUE,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_LBRACE,   // {
    TOKEN_RBRACE,   // }
    TOKEN_LPAREN,   // (
    TOKEN_RPAREN,   // )
    TOKEN_SEMICOLON // ;
} TokenType;

// Função que recebe uma string do token e retorna um elemento do enum para ser usado no analyzer
TokenType token_from_word(const char *token) {
    if(strcmp(token, "void") == 0) return TOKEN_VOID;
    if(strcmp(token, "int") == 0) return TOKEN_INT;
    if(strcmp(token, "float") == 0) return TOKEN_FLOAT;
    if(strcmp(token, "char") == 0) return TOKEN_CHAR;
    if(strcmp(token, "if") == 0) return TOKEN_IF;
    if(strcmp(token, "else") == 0) return TOKEN_ELSE;
    if(strcmp(token, "for") == 0) return TOKEN_FOR;
    if(strcmp(token, "while") == 0) return TOKEN_WHILE;
    if(strcmp(token, "do") == 0) return TOKEN_DO;
    if(strcmp(token, "return") == 0) return TOKEN_RETURN;
    if(strcmp(token, "break") == 0) return TOKEN_BREAK;
    if(strcmp(token, "continue") == 0) return TOKEN_CONTINUE;

    return TOKEN_IDENTIFIER;
}

// O tipo de escopo e a linha de início
typedef struct {
	char * type;
	int line;
} Scope;

// O nodo da pilha
typedef struct Node {
	Scope info;
	struct Node *next;
} Node;

// A pilha. Somente aponta para o primeiro elemento (topo).
typedef struct {
	Node *first;
} Stack;

// Cria uma pilha
Stack *create_stack() {
	Stack *s = malloc(sizeof(Stack));
	s->first = NULL;
	return s;
}

// Empilha
void push(Stack *s, Scope scope) {
	Node *n = malloc(sizeof(Node)); // Aloca novo nodo
	n->info = scope; // Dados do escopo
	n->next = s->first; // Apontador para o início da pilha
	s->first = n; // Troca o início da pilha para o novo nodo
}

// Desempilha
Scope pop(Stack *s) {
	if (!s->first) { // Verifica se a pilha está vazia ou não
		printf("Erro: pilha já está vazia");
		exit(1);
	}
	
	Node *n = s->first; // Auxiliar recebe o primeiro
	s->first = n->next; // Primeiro passa a ser o segundo
	Scope scope = n->info; // Salva o escopo que era o primeiro
	free(n); // Libera auxiliar
	
	return scope; // Retorna o escopo que era o primeiro
}

// Ver topo da pilha
Scope *peek(Stack *s) {
	if (!s->first) return NULL; // Se não tem nada, não retorna nada
	
	return &s->first->info; // Retorna info do primeiro
}

// Ver se a pilha está vazia
bool is_empty(Stack *s) {
    return s->first == NULL;
}

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

// Analisa o token via enum
void analyze_token(TokenType token, int line, Stack *stack) {

    switch (token) {

        case TOKEN_VOID:
        case TOKEN_INT:
        case TOKEN_FLOAT:
        case TOKEN_CHAR: { // Pode ser declaração de variável ou início de função
            Scope s;
            s.type = "function_candidate";
            s.line = line;
            push(stack, s);
            break;
        }

        case TOKEN_IDENTIFIER: {
            // Se o topo da pilha for function_candidate,
            // identificador é o nome da função
            Scope *top = peek(stack);
            if (top && strcmp(top->type, "function_candidate") == 0) {
                printf("[DEBUG] function name '%s' at line %d\n", lexeme, line);
            }
            break;
        }

        case TOKEN_LPAREN: {
            Scope *top = peek(stack);
            if (top && strcmp(top->type, "function_candidate") == 0) {
                printf("[DEBUG] parameters start for function at line %d\n", line);
            }
            break;
        }

        case TOKEN_LBRACE: {
            Scope *top = peek(stack);

            if (top && strcmp(top->type, "function_candidate") == 0) {
                // Agora virou função de verdade
                pop(stack);

                Scope s;
                s.type = "function";
                s.line = line;
                push(stack, s);

                printf("[DEBUG] FUNCTION BLOCK opened at line %d\n", line);
            }
            else {
                // É só um bloco normal
                Scope s;
                s.type = "block";
                s.line = line;
                push(stack, s);

                printf("[DEBUG] BLOCK opened at line %d\n", line);
            }
            break;
        }

        case TOKEN_RBRACE: {
            if (!is_empty(stack)) {
                Scope s = pop(stack);
                printf("[DEBUG] BLOCK closed (%s) started at line %d, closed at %d\n",
                       s.type, s.line, line);
            } else {
                printf("[DEBUG] ERROR: unmatched '}' at line %d\n", line);
            }
            break;
        }

        case TOKEN_FOR: {
            Scope s;
            s.type = "for";
            s.line = line;
            push(stack, s);

            printf("[DEBUG] FOR detected at line %d\n", line);
            break;
        }

        case TOKEN_WHILE: {
            Scope s;
            s.type = "while";
            s.line = line;
            push(stack, s);

            printf("[DEBUG] WHILE detected at line %d\n", line);
            break;
        }

        case TOKEN_IF: {
            Scope s;
            s.type = "if";
            s.line = line;
            push(stack, s);

            printf("[DEBUG] IF detected at line %d\n", line);
            break;
        }

        case TOKEN_DO: {
            Scope s;
            s.type = "do";
            s.line = line;
            push(stack, s);

            printf("[DEBUG] DO detected at line %d\n", line);
            break;
        }

        default:
            break;
    }
}


void analyze_rows(char **rows, int count, Stack * stack) {
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
			system("pause");
			
			// Espaços em branco, avança pro próximo
			if(*end == ' ' || *end == '\t') {
				end++;
				continue;
			}
			
			// Abertura de escopo
			if(strchr("({[", *end)) {
				printf("Linha %d: TOKEN_SYMBOL: %c\n", i, *end);
				end++;
				continue;
			}
			
			// Fechamento de escopo
			if(strchr(")}]", *end)) {
				printf("Linha %d: TOKEN_SYMBOL: %c\n", i, *end);
				end++;
				continue;
			}
			
			// ;
			if(strchr(";", *end)) {
				printf("Linha %d: TOKEN_SYMBOL: %c\n", i, *end);
				end++;
				continue;
			}
			
			// Palavra (nome ou keyword)
			if(isalpha(*end) || *end == '_') {
				const char *start = end; // Fixa o início no primeiro caracter alfanumérico encontrado
				
				while(isalnum(*end) || *end == '_') { // Percorre até que está encontrando letra, número ou _
					end++;
				}
				// Encontrou algo diferente, saiu do while deixando o ponteiro no último caracter
				
				int length = end - start; // último - primeiro
				char buffer[128]; // Declara uma string para armazenar o que achou
				strncpy(buffer, start, length); // Coloca o que achou na string
				buffer[length]='\0'; // Terminador de string
				
				printf("Linha %d: TOKEN_WORD: %s\n", i, buffer);
				continue;
			}
			
			// Número
			if(isdigit(*p)) {
				const char *start = end; // Fixa o início do primeiro caracter dígito
				
				while(isdigit(*end)) { // Percore todos os dígitos
					end++;
				}
				// Saiu deixando o ponteiro no último dígito
				
				int length = end - start; // último - primeiro
				char buffer[64]; // Declara uma string para armazenar o que achou
				strncpy(buffer, start, length); // Coloca o que achou na string
				buffer[length] = '\0'; // Terminador
				analyze_token(buffer, i, stack);
				printf("Linha %d: TOKEN_NUMBER: %s\n", i, buffer);
				continue;
			}
			
			end++;
			
		}
		
		
		
		system("pause");
		
	}
}


int main()
{
	Stack * stack = create_stack();
	char *src = read_file("exemplosTeste.c");
	if(!src) {
		printf("Erro ao abrir arquivo de exemplos");
		return 1;
	}
	
	char **rows = NULL;
	long count = 0;
	split_rows(src, &rows, &count);
	trim_rows(rows, count);
	
	analyze_rows(rows, count, stack);
	
	
	
	free(src);
	
	return 0;
    
}
