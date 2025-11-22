#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct FunctionData {
	char name[64];
	int startLine;
	int endLine;

	int loops;
	int nestedDepth;

	int calls;
	char calledFunctions[16][64];
	int callCount;

	char complexity[32];

	struct FunctionData *next;
	struct FunctionData *prev;
} FunctionData;

typedef struct {
	FunctionData *head;
	FunctionData *tail;
	long count;
} FunctionDataList;

void initFunctionDataList(FunctionDataList *list) {
	list->head = NULL;
	list->tail = NULL;
}

void resetFunctionData(FunctionData *f) {
    if (f == NULL) return;

    // Zera tudo
    memset(f->name, 0, sizeof(f->name));
    f->startLine = 0;
    f->endLine = 0;

    f->loops = 0;
    f->nestedDepth = 0;

    f->calls = 0;

    // Limpa todas as funções chamadas
    for (int i = 0; i < 16; i++) {
        memset(f->calledFunctions[i], 0, sizeof(f->calledFunctions[i]));
    }
    f->callCount = 0;

    memset(f->complexity, 0, sizeof(f->complexity));

    // Como é um "objeto corrente", limpamos também ponteiros
    f->next = NULL;
    f->prev = NULL;
}


void addFunctionData(FunctionDataList *list, FunctionData *f) {
	FunctionData *newFunction = malloc(sizeof(FunctionData)); // Aloca

	// Copia valores simples
	newFunction->startLine  = f->startLine;
	newFunction->endLine    = f->endLine;
	newFunction->loops      = f->loops;
	newFunction->nestedDepth = f->nestedDepth;
	newFunction->calls       = f->calls;
	newFunction->callCount   = f->callCount;

	// Copia nome da função
	strcpy(newFunction->name, f->name);

	// Copia complexidade
	strcpy(newFunction->complexity, f->complexity);

	// Copia lista de funções chamadas
	for (int i = 0; i < f->callCount; i++) {
		strcpy(newFunction->calledFunctions[i], f->calledFunctions[i]);
	}

	newFunction->next = NULL;

	if (list->head == NULL) {
		newFunction->prev = NULL;
		list->head = newFunction;
		list->tail = newFunction;
	} else {
		newFunction->prev = list->tail;
		list->tail->next = newFunction;
		list->tail = newFunction;
	}

}

void freeFunctionDataList(FunctionDataList *list) {
	FunctionData *f = list->head;
	while (f) {
		FunctionData *next = f->next;
		free(f->name);
		free(f);
		f = next;
	}
}

void printFunctionDataList(FunctionDataList *list) {
	FunctionData *f = list->head;

	while (f != NULL) {
		printf("\n================= FUNCAO =================\n");
		printf("Nome:           %s\n", f->name);
		printf("Inicio na linha: %d\n", f->startLine);
		printf("Fim na linha:    %d\n", f->endLine);

		printf("\n--- Metricas ---\n");
		printf("Loops totais:        %d\n", f->loops);
		printf("Profundidade maxima: %d\n", f->nestedDepth);
		printf("Chamadas totais:     %d\n", f->calls);

		printf("\n--- Funcoes chamadas (%d) ---\n", f->callCount);
		if (f->callCount == 0) {
			printf("  (nenhuma)\n");
		} else {
			for (int i = 0; i < f->callCount; i++) {
				printf("  - %s\n", f->calledFunctions[i]);
			}
		}

		printf("\nComplexidade estimada: %s\n", f->complexity);
		printf("===========================================\n\n");

		f = f->next;
	}
}


// Enum dos tokens possíveis de ler
typedef enum {
	TOKEN_IDENTIFIER,
	TOKEN_NUMBER,
	TOKEN_STRING,

	TOKEN_VOID,
	TOKEN_INT,
	TOKEN_FLOAT,
	TOKEN_CHAR,
	TOKEN_FOR,
	TOKEN_WHILE,
	TOKEN_IF,
	TOKEN_ELSE,
	TOKEN_RETURN,
	TOKEN_FUNCTION,
	TOKEN_FUNCTION_CALL,

	OPEN_PAREN,     // (
	CLOSE_PAREN,    // )
	OPEN_BRACE,     // {
	CLOSE_BRACE,    // }
	OPEN_BRACKET,   // [
	CLOSE_BRACKET,  // ]

	SYMBOL_COMMA,       // ,
	SYMBOL_SEMICOLON,   // ;
	SYMBOL_EQUALS,      // =
	SYMBOL_MINUS,       // -
	SYMBOL_MINUSMINUS,  // --
	SYMBOL_PLUS,    	// +
	SYMBOL_PLUSPLUS,    // ++
	SYMBOL_LESS,        // <

	LINE_COMMENT,
	BLOCK_COMMENT_START,
	BLOCK_COMMENT_END,

	TOKEN_UNKNOWN
} TokenType;

// Para print, token vira string
const char* tokenTypeToString(TokenType type) {
	switch (type) {
		case TOKEN_IDENTIFIER:
			return "IDENTIFIER";
		case TOKEN_FUNCTION:
			return "FUNCTION";
		case TOKEN_FUNCTION_CALL:
			return "FUNCTION_CALL";
		case TOKEN_NUMBER:
			return "NUMBER";
		case TOKEN_STRING:
			return "STRING";

		case TOKEN_VOID:
			return "VOID";
		case TOKEN_INT:
			return "INT";
		case TOKEN_FLOAT:
			return "FLOAT";
		case TOKEN_CHAR:
			return "CHAR";
		case TOKEN_FOR:
			return "FOR";
		case TOKEN_WHILE:
			return "WHILE";
		case TOKEN_IF:
			return "IF";
		case TOKEN_ELSE:
			return "ELSE";
		case TOKEN_RETURN:
			return "RETURN";

		case OPEN_PAREN:
			return "OPEN_PAREN";
		case CLOSE_PAREN:
			return "CLOSE_PAREN";
		case OPEN_BRACE:
			return "OPEN_BRACE";
		case CLOSE_BRACE:
			return "CLOSE_BRACE";
		case OPEN_BRACKET:
			return "OPEN_BRACKET";
		case CLOSE_BRACKET:
			return "CLOSE_BRACKET";

		case SYMBOL_COMMA:
			return "COMMA";
		case SYMBOL_SEMICOLON:
			return "SEMICOLON";
		case SYMBOL_EQUALS:
			return "EQUALS";
		case SYMBOL_MINUS:
			return "MINUS";
		case SYMBOL_PLUSPLUS:
			return "PLUSPLUS";
		case SYMBOL_LESS:
			return "LESS";

		case LINE_COMMENT:
			return "LINE_COMMENT";
		case BLOCK_COMMENT_START:
			return "BLOCK_COMMENT_START";
		case BLOCK_COMMENT_END:
			return "BLOCK_COMMENT_END";

		default:
			return "UNKNOWN";
	}
}

// Elemento da lista
typedef struct Token {
	TokenType type;
	char *text;   // Conteúdo
	int line;

	struct Token *next;
	struct Token *prev;
} Token;

// Lista
typedef struct {
	Token *head;
	Token *tail;
	long count;
} TokenList;

// Iniciar lista de tokens
void initTokenList(TokenList *list) {
	list->head = NULL;
	list->tail = NULL;
}

// Adicionar token no final da lista
void addToken(TokenList *list, TokenType type, const char *text, int line) {
	Token *newToken = malloc(sizeof(Token)); // Aloca

	// Insere conteúdo do novo token
	newToken->type = type;
	newToken->text = strdup(text);
	newToken->line = line;
	newToken->next = NULL;

	if (list->head == NULL) {
		newToken->prev = NULL;
		list->head = newToken;
		list->tail = newToken;
	} else {
		newToken->prev = list->tail;
		list->tail->next = newToken;
		list->tail = newToken;
	}

}

// Liberar memória da lista de tokens
void freeTokenList(TokenList *list) {
	Token *t = list->head;
	while (t) {
		Token *next = t->next;
		free(t->text);
		free(t);
		t = next;
	}
}

// Imprime lista de tokens
void printTokenList(TokenList *list) {
	Token *cur = list->head;

	while (cur != NULL) {
		printf("Linha %d:\t%-22s\t'%s'\n",
		       cur->line,
		       tokenTypeToString(cur->type),
		       cur->text);
		cur = cur->next;
	}
}

// O tipo de escopo e a linha de início
typedef struct {
	TokenType type;
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

// Imprime a pilha
void printStack(Stack *s) {
	Node *cur = s->first;

	printf("\n=== STACK CONTENT ===\n");

	if (!cur) {
		printf("(vazia)\n");
		return;
	}

	while (cur != NULL) {
		printf("Scope: %-18s  Line: %d\n",
		       tokenTypeToString(cur->info.type),
		       cur->info.line);
		cur = cur->next;
	}

	printf("======================\n\n");
}

int getLoopDepth(Stack *s) {
	int depth = 0;

	Node *node = s->first;

	while(node != NULL) {
		if(node->info.type == TOKEN_FOR ||
		        node->info.type == TOKEN_WHILE) {
			depth++;
		}

		node = node->next;

	}

	return depth;
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

// Recebe uma string, devolve um tipo de token
TokenType string_to_token(char buffer[128]) {
	// Keywords
	if (strcmp(buffer, "void") == 0)   return TOKEN_VOID;
	if (strcmp(buffer, "int") == 0)    return TOKEN_INT;
	if (strcmp(buffer, "float") == 0)  return TOKEN_FLOAT;
	if (strcmp(buffer, "char") == 0)   return TOKEN_CHAR;
	if (strcmp(buffer, "for") == 0)    return TOKEN_FOR;
	if (strcmp(buffer, "while") == 0)  return TOKEN_WHILE;
	if (strcmp(buffer, "if") == 0)     return TOKEN_IF;
	if (strcmp(buffer, "else") == 0)   return TOKEN_ELSE;
	if (strcmp(buffer, "return") == 0) return TOKEN_RETURN;

	// Se não é keyword é Identifier
	return TOKEN_IDENTIFIER;
}

// Função que recebe o código bruto inteiro e converte para lista de tokens
void tokenize(const char *src, TokenList *list) {
	int line = 1;
	const char *p = src;

	while(*p) {
		// Pular espaços
		if(*p == ' ' || *p == '\t' || *p == '\r') {
			p++;
			continue;
		}

		// Pula quebra de linha
		if(*p == '\n') {
			line++;
			p++;
			continue;
		}

		// Identifiers ou Keywords
		if(isalpha(*p) || *p == '_') {
			const char *start = p; // Fixa o início em um alfanumérico
			p++;

			while(isalnum(*p) || *p == '_') {
				p++;
			} // Avança até que encontra letra, número ou _
			// Aqui o ponteiro está logo após o último caracter válido

			char buffer[128];
			int length = p - start; // Fim - início
			strncpy(buffer, start, length); // Joga o elemento no buffer
			buffer[length] = '\0'; // Coloca o terminador no buffer

			addToken(list, string_to_token(buffer), buffer, line);
			continue;
		}

		// Números
		if(isdigit(*p)) {
			const char *start = p;

			while (isdigit(*p)) p++;

			char buffer[128];
			int length = p - start;
			strncpy(buffer, start, length);
			buffer[length] = '\0';

			addToken(list, TOKEN_NUMBER, buffer, line);
			continue;
		}

		// Símbolos
		switch (*p) {
			case '(':
				addToken(list, OPEN_PAREN, "(", line);
				p++;
				continue;

			case ')':
				addToken(list, CLOSE_PAREN, ")", line);
				p++;
				continue;

			case '{':
				addToken(list, OPEN_BRACE, "{", line);
				p++;
				continue;

			case '}':
				addToken(list, CLOSE_BRACE, "}", line);
				p++;
				continue;

			case '[':
				addToken(list, OPEN_BRACKET, "[", line);
				p++;
				continue;

			case ']':
				addToken(list, CLOSE_BRACKET, "]", line);
				p++;
				continue;

			case ',':
				addToken(list, SYMBOL_COMMA, ",", line);
				p++;
				continue;

			case ';':
				addToken(list, SYMBOL_SEMICOLON, ";", line);
				p++;
				continue;

			case '=':
				addToken(list, SYMBOL_EQUALS, "=", line);
				p++;
				continue;

			case '-':
				// --
				if (*(p + 1) == '-') {
					addToken(list, SYMBOL_MINUSMINUS, "--", line);
					p += 2;
					continue;
				}
				addToken(list, SYMBOL_MINUS, "-", line);
				p++;
				break;

			case '<':
				addToken(list, SYMBOL_LESS, "<", line);
				p++;
				continue;

			case '+':
				// ++
				if (*(p + 1) == '+') {
					addToken(list, SYMBOL_PLUSPLUS, "++", line);
					p += 2;
					continue;
				}
				addToken(list, SYMBOL_PLUS, "+", line);
				p++;
				break;

			case '/':
				// "//" comentário de linha
				if (*(p + 1) == '/') {
					addToken(list, LINE_COMMENT, "//", line);
					p += 2;
					while (*p && *p != '\n') p++; // Ignora o resto da linha até a quebra
					continue;
				}

				// "/*" início de comentário de bloco
				if (*(p + 1) == '*') {
					addToken(list, BLOCK_COMMENT_START, "/*", line);
					p += 2;

					// Avança até achar */
					while (*p) {

						// Controle de linha
						if (*p == '\n') {
							line++;
						}

						// Acha fim do bloco e ignora tudo
						if (*p == '*' && *(p + 1) == '/') {
							addToken(list, BLOCK_COMMENT_END, "*/", line);
							p += 2;
							break;
						}

						p++;
					}

					continue;
				}

				break;


		}

		p++;
	}
}


void parse (TokenList *list, Stack *stack, FunctionDataList *functionList) {
	Token *cur = list->head;

	FunctionData *currentFunction;

	while (cur != NULL) {
		if(cur->type == OPEN_PAREN) {
			Token *prev = cur->prev;

			switch(prev->type) {
				case TOKEN_IDENTIFIER: {
					if(prev->prev->type == TOKEN_VOID ||
					        prev->prev->type == TOKEN_INT ||
					        prev->prev->type == TOKEN_FLOAT ||
					        prev->prev->type == TOKEN_CHAR) {
						// Se antes do IDENTIFICADOR for algum tipo de função, é declaraçao de função

						while(cur->type != OPEN_BRACE) { // Avança até o "{"
							cur = cur->next;
						}

						currentFunction = malloc(sizeof(FunctionData));
						strcpy(currentFunction->name, prev->text);
						currentFunction->startLine = prev->line;

						push(stack, (Scope) {
							TOKEN_FUNCTION, prev->line
						}); // Empilha o escopo

					} else { // FUNCTION CALL

						while(cur->type != CLOSE_PAREN) { // Avança até o ")"
							cur = cur->next;
						}

						currentFunction->calls++;
						
						strncpy(currentFunction->calledFunctions[currentFunction->callCount], prev->text, 63);
						
						currentFunction->callCount++;

					}
					break;
				}
				case TOKEN_FOR: {
					while(cur->type != OPEN_BRACE) {
						cur = cur->next;
					}
					push(stack, (Scope) {
						TOKEN_FOR, prev->line
					}); // Empilha o FOR
					int depth = getLoopDepth(stack);
					currentFunction->loops++;
					if(depth > currentFunction->nestedDepth) {
						currentFunction->nestedDepth = depth;
					}
					break;
				}
				case TOKEN_WHILE: {
					while(cur->type != OPEN_BRACE) {
						cur = cur->next;
					}
					push(stack, (Scope) {
						TOKEN_WHILE, prev->line
					}); // Empilha o WHILE
					int depth = getLoopDepth(stack);
					currentFunction->loops++;
					if(depth > currentFunction->nestedDepth) {
						currentFunction->nestedDepth = depth;
					}
					break;
				}
				case TOKEN_IF: {
					while(cur->type != OPEN_BRACE) {
						cur = cur->next;
					}
					push(stack, (Scope) {
						TOKEN_IF, prev->line
					}); // Empilha o IF
					break;
				}
				
				

			}
		} 
		
		if (cur->type == OPEN_BRACE && cur->prev->type == TOKEN_ELSE) { // Tratamento exclusivo do else
			while(cur->type != OPEN_BRACE) {
				cur = cur->next;
			}
			push(stack, (Scope) {
				TOKEN_ELSE, cur->prev->line
			}); // Empilha o ELSE
		}

		

		if(cur->type == CLOSE_BRACE) {
			Scope *peek_scope = peek(stack);

			if(peek_scope->type == TOKEN_FUNCTION) {
				//CALCULAR COMPLEXIDADE AQUI
				currentFunction->endLine = cur->line;
				addFunctionData(functionList, currentFunction);
				resetFunctionData(currentFunction);
			}

			printf("CLOSE_BRACE_TOKEN_TYPE: %s\n", tokenTypeToString(peek_scope->type));
			pop(stack);
			
		
		}
		
		printf("CUR: %s\n", cur->text);
		cur = cur->next; // Próximo
	}
}

int main() {
	const char *files[] = { // Arquivos a serem lidos
		"linear_search.c",
		"bubble_sort.c",
		"merge_sort.c",
		"binary_search.c",
		"fibonacci.c",
		"triple_loop.c"
	};

	int totalFiles = sizeof(files) / sizeof(files[0]);

	for (int i = 0; i < totalFiles; i++) { // Um arquivo por vez
		printf("\n=======================================\n");
		printf("Processando arquivo: %s\n", files[i]);
		printf("=======================================\n\n");

		Stack * stack = create_stack();
		TokenList tokenList;
		initTokenList(&tokenList);
		FunctionDataList functionList;
		initFunctionDataList(&functionList);

		char *src = read_file(files[i]);
		if(!src) {
			printf("Erro ao abrir arquivo");
			return 1;
		}

		tokenize(src, &tokenList);
		parse(&tokenList, stack, &functionList);

		printStack(stack);
		printFunctionDataList(&functionList);

		system("pause");   // só no Windows
		printf("\n\n");
		system("cls");

		freeTokenList(&tokenList);
	}

	return 0;
}





