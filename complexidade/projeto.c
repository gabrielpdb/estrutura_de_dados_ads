#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
        case TOKEN_IDENTIFIER:      return "IDENTIFIER";
        case TOKEN_NUMBER:          return "NUMBER";
        case TOKEN_STRING:          return "STRING";

        case TOKEN_VOID:            return "VOID";
        case TOKEN_INT:             return "INT";
        case TOKEN_FLOAT:           return "FLOAT";
        case TOKEN_CHAR:            return "CHAR";
        case TOKEN_FOR:             return "FOR";
        case TOKEN_WHILE:           return "WHILE";
        case TOKEN_IF:              return "IF";
        case TOKEN_ELSE:            return "ELSE";
        case TOKEN_RETURN:          return "RETURN";

        case OPEN_PAREN:            return "OPEN_PAREN";
        case CLOSE_PAREN:           return "CLOSE_PAREN";
        case OPEN_BRACE:            return "OPEN_BRACE";
        case CLOSE_BRACE:           return "CLOSE_BRACE";
        case OPEN_BRACKET:          return "OPEN_BRACKET";
        case CLOSE_BRACKET:         return "CLOSE_BRACKET";

        case SYMBOL_COMMA:          return "COMMA";
        case SYMBOL_SEMICOLON:      return "SEMICOLON";
        case SYMBOL_EQUALS:         return "EQUALS";
        case SYMBOL_MINUS:          return "MINUS";
        case SYMBOL_PLUSPLUS:       return "PLUSPLUS";
        case SYMBOL_LESS:           return "LESS";

        case LINE_COMMENT:          return "LINE_COMMENT";
        case BLOCK_COMMENT_START:   return "BLOCK_COMMENT_START";
        case BLOCK_COMMENT_END:     return "BLOCK_COMMENT_END";

        default:                    return "UNKNOWN";
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

int main()
{
	Stack * stack = create_stack();
	TokenList tokenList;
	initTokenList(&tokenList);
	
	char *src = read_file("exemplosTeste.c");
	if(!src) {
		printf("Erro ao abrir arquivo de exemplos");
		return 1;
	}
	system("pause");
	tokenize(src, &tokenList);
	system("pause");
	printTokenList(&tokenList);
	system("pause");
	
	return 0;
}

    
