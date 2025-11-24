# Relatório sistema de análise de complexidade de algoritmos em C

## Cronologia de decisões sobre o projeto

1.  Criar função que lê o arquivo de exemplos
    Armazena todo o conteúdo do arquivo em uma string
2.  Separar cada linha da string lida do arquivo em um vetor de strings
    Agora temos um `char **rows` onde a cada posição temos uma linha do código de exemplos
3.  Trimar cada linha, ou seja, remover espaços em branco no início e fim
    Agora é possível identificar o comando que inicia a linha
4.  Fazer função que identifica linhas em branco como primeiro teste em cada linha a ser analisada (is_blank)
    Quando encontrar linha em branco, avança direto pra próxima
5.  Fazer função que identifica quando a linha começa com comentário //
    Quando encontrar, avança para a próxima
6.  Agora vamos pegar linha a linha e percorrer ela um caracter por vez testando o seguinte:
    "({[" -> Abertura de escopo
    ")}]" -> Fechamento de escopo
    ";" -> Fim do comando
    Alfanumérico -> Quando encontra uma letra. Avança um por vez testando se ainda é letra, ou número nesse caso, ou "\_". Esse teste cobre declaração de palavras chave e nomes de variáveis ou funções.
    Dígito -> Quando encontra de primeira um número. Avança um por testando se ainda é número.
7.  Criar uma pilha que empilhe as aberturas de escopo. Quando encontrar um fechamento de escopo, analisar o que há dentro da pilha até a abertura daquele escopo em específico.
    Exemplo:
    for() { // -> abre o escopo de um for
    if(){} // -> abre e fecha escopo de um if
    for() {} // -> abre e fecha escopo de um for
    } // -> fecha o escopo de um for
    Encontrou fechamento
8.  Criar um enum com os tipos de escopo possíveis
    BLOCK, PAREN, BRACKET, FOR, WHILE, IF, FUNCTION
9.  Nesse ponto aqui percebemos que a análise linha a linha tinha obstáculos complexos. Quando havia uma declaração de função por exemplo (int identificador(){}), o parser tinha que analisar o token "int" e os elementos que o seguiam para entender que era de fato uma função e não uma variável por exemplo. Muitas ou todas as vezes o "}" estava em outra linha. Essa outra linha não estava na chamada do parser. Virou um caos.
    A partir daqui a ideia é "tokenizar" tudo. O código vai ser lido todo de uma vez só, sem quebras de linha.
    Vamos exemplificar no seguinte código:

    // comentário de exemplo
    void bubble_sort(int arr[], int n) {

        for (int i = 0; i < n - 1; i++) {

            for (int j = 0; j < n - i - 1; j++) {

                if (arr[j] > arr[j + 1]) {

                    int temp = arr[j];

                    arr[j] = arr[j + 1];

                    arr[j + 1] = temp;

                }

            }

        }

    }

    Esse código vira uma lista encadeada (pelo tamanho variável) de tokens. Cada token guarda seu tipo, conteúdo e linha de ocorrência. Fica mais ou menos assim (gerado pelo GPT para evitar a fadiga):
    [
    LINE_COMMENT, "comentário de exemplo", 1,
    TOKEN_VOID, "void", 2,
    IDENTIFIER, "bubble_sort", 2,
    OPEN_PAREN, "(", 2,
    TOKEN_INT, "int", 2,
    IDENTIFIER, "arr", 2,
    OPEN_BRACKET, "[", 2,
    CLOSE_BRACKET, "]", 2,
    SYMBOL_COMMA, ",", 2,
    TOKEN_INT, "int", 2,
    IDENTIFIER, "n", 2,
    CLOSE_PAREN, ")", 2,
    OPEN_BRACE, "{", 2,
    TOKEN_FOR, "for", 4,
    OPEN_PAREN, "(", 4,
    TOKEN_INT, "int", 4,
    IDENTIFIER, "i", 4,
    SYMBOL_EQUALS, "=", 4,
    NUMBER, "0", 4,
    SYMBOL_SEMICOLON, ";", 4,
    IDENTIFIER, "i", 4,
    SYMBOL_LESS, "<", 4,
    IDENTIFIER, "n", 4,
    SYMBOL_MINUS, "-", 4,
    NUMBER, "1", 4,
    SYMBOL_SEMICOLON, ";", 4,
    IDENTIFIER, "i", 4,
    SYMBOL_PLUSPLUS, "++", 4,
    CLOSE_PAREN, ")", 4,
    OPEN_BRACE, "{", 4,
    TOKEN_FOR, "for", 6,
    OPEN_PAREN, "(", 6,
    TOKEN_INT, "int", 6,
    IDENTIFIER, "j", 6,
    SYMBOL_EQUALS, "=", 6,
    NUMBER, "0", 6,
    SYMBOL_SEMICOLON, ";", 6,
    IDENTIFIER, "j", 6,
    SYMBOL_LESS, "<", 6,
    IDENTIFIER, "n", 6,
    SYMBOL_MINUS, "-", 6,
    IDENTIFIER, "i", 6,
    SYMBOL_MINUS, "-", 6,
    NUMBER, "1", 6,
    SYMBOL_SEMICOLON, ";", 6,
    IDENTIFIER, "j", 6,
    SYMBOL_PLUSPLUS, "++", 6,
    CLOSE_PAREN, ")", 6,
    OPEN_BRACE, "{", 6,
    TOKEN_IF, "if", 8,
    OPEN_PAREN, "(", 8,
    IDENTIFIER, "arr", 8,
    OPEN_BRACKET, "[", 8,
    IDENTIFIER, "j", 8,
    CLOSE_BRACKET, "]", 8,
    SYMBOL_GREATER, ">", 8,
    IDENTIFIER, "arr", 8,
    OPEN_BRACKET, "[", 8,
    IDENTIFIER, "j", 8,
    SYMBOL_PLUS, "+", 8,
    NUMBER, "1", 8,
    CLOSE_BRACKET, "]", 8,
    CLOSE_PAREN, ")", 8,
    OPEN_BRACE, "{", 8,
    TOKEN_INT, "int", 10,
    IDENTIFIER, "temp", 10,
    SYMBOL_EQUALS, "=", 10,
    IDENTIFIER, "arr", 10,
    OPEN_BRACKET, "[", 10,
    IDENTIFIER, "j", 10,
    CLOSE_BRACKET, "]", 10,
    SYMBOL_SEMICOLON, ";", 10,
    IDENTIFIER, "arr", 12,
    OPEN_BRACKET, "[", 12,
    IDENTIFIER, "j", 12,
    CLOSE_BRACKET, "]", 12,
    SYMBOL_EQUALS, "=", 12,
    IDENTIFIER, "arr", 12,
    OPEN_BRACKET, "[", 12,
    IDENTIFIER, "j", 12,
    SYMBOL_PLUS, "+", 12,
    NUMBER, "1", 12,
    CLOSE_BRACKET, "]", 12,
    SYMBOL_SEMICOLON, ";", 12,
    IDENTIFIER, "arr", 14,
    OPEN_BRACKET, "[", 14,
    IDENTIFIER, "j", 14,
    SYMBOL_PLUS, "+", 14,
    NUMBER, "1", 14,
    CLOSE_BRACKET, "]", 14,
    SYMBOL_EQUALS, "=", 14,
    IDENTIFIER, "temp", 14,
    SYMBOL_SEMICOLON, ";", 14,
    CLOSE_BRACE, "}", 16,
    CLOSE_BRACE, "}", 18,
    CLOSE_BRACE, "}", 20,
    CLOSE_BRACE, "}", 22,
    ]

10. Agora vamos começar a analisar os tokens para identificar estruturas do tipo: funções, laços (for, while), if else, chamadas de funções. Identificamos que normalmente todas essas estruturas tem em comum pelo menos uma abertura de escopo, seja com parênteses ou chaves. A seguir as estruturas comuns:

    - Declaração de FUNCTION:
      TOKEN\_<RETORNO>
      IDENTIFIER
      OPEN_PAREN
      <DECLARAÇÕES DE VARIÁVEIS OU NÃO>
      CLOSE_PAREN
      OPEN_BRACE
      <CONTEÚDO DA FUNÇÃO>
      CLOSE_BRACE
    - Declaração de FUNCTION CALL:
      IDENTIFIER
      OPEN_PAREN
      <PARÂMETROS>
      CLOSE_PAREN
      SYMBOL_SEMICOLON
    - Declaração de FOR:
      TOKEN_FOR
      OPEN_PAREN
      <DECLARAÇÕES DO FOR>
      CLOSE_PAREN
      OPEN_BRACE
      <CONTEÚDO DO FOR>
      CLOSE_BRACE
    - Declaração de WHILE:
      TOKEN_WHILE
      OPEN_PAREN
      <CONDIÇÃO DO WHILE>
      CLOSE_PAREN
      OPEN_BRACE
      <CONTEÚDO DO WHILE>
      CLOSE_BRACE
    - Declaração de IF:
      TOKEN_IF
      OPEN_PAREN
      <CONDIÇÕES DO IF>
      CLOSE_PAREN
      OPEN_BRACE
      <CONTEÚDO DO IF>
      CLOSE_BRACE
    - Declaração de IF ELSE:
      TOKEN_IF
      OPEN_PAREN
      <CONDIÇÕES DO IF>
      CLOSE_PAREN
      OPEN_BRACE
      <CONTEÚDO DO IF>
      CLOSE_BRACE
      TOKEN_ELSE
      OPEN_BRACE
      <CONTEÚDO DO ELSE>
      CLOSE_BRACE
    - Declaração de IF ELSE IF:
      TOKEN_IF
      OPEN_PAREN
      <CONDIÇÕES DO IF>
      CLOSE_PAREN
      OPEN_BRACE
      <CONTEÚDO DO IF>
      CLOSE_BRACE
      TOKEN_ELSE
      TOKEN_IF
      OPEN_BRACE
      <CONTEÚDO DO ELSE IF>
      CLOSE_BRACE

      - Note que não estamos tratando DO WHILE nesse caso para simplificar a abordagem. Nem SWITCH CASE, pelo mesmo motivo.

      Faz sentido então iniciar a busca pelo primeiro "(". Depois analisamos o elemento imediatamente anterior e então definimos que estrutura é. Definida a estrutura, temos uma estrutura de pilha já estruturada e fazemos o push no início da estrutura "{". Nesse ponto do desenvolvimento vamos implementar os 6 algoritmos de ordenação para testar se a pilha está funcionando. O retorno da impressão da pilha pós análise dos tokens deve conter, em ordem, a declaração da função e as estruturas de repetição e condição presentes em seu interior. Isso deve se repetir para cada função presente no arquivo.

11. Tivemos o retorno esperado, mas ele não é suficiente para a análise de algoritmos mais complexos, com chamadas de outras funções por exemplo.
12. Decidimos separar cada algoritmo em um arquivo a parte e fazer o programa abrir um por vez. Isso principalmente por causa dos algoritmos que demandam duas funções.
13. Agora vamos criar uma lista para armazenar os dados das funções que encontrarmos na análise do código. Isso estava faltando pois não tínhamos controle sobre qual função estava em execução e qual chamava outra ou a si mesmo.
14. Durante a leitura dos tokens, quando encontramos uma declaração de função, armazenamos ela como uma variável dentro da leitura, guardando seu nome e a linha de início. Conforme vamos identificando outros elementos dentro dessa função (ainda não encontramos o fechamento do escopo de função), vamos empilhando e desempilhando escopos (if, for e while). Toda vez que o escopo é for ou while, calculamos a profundidade da pilha de escopos e se ela for maior do que a função atual em análise, incrementamos isso na função. Quando chegamos no fim da função, ou seja, o peek da pilha de escopos é um TOKEN_FUNCTION, setamos a endLine da função, calculamos a complexidade (ainda não implementado) e jogamos ela na lista de funções.
15. Ainda com a leitura dentro da função, também identificamos FUNCTION CALL, ou seja, quando uma função é chamada, seja ela recursiva ou não. Quando encontramos, armazenamos essa informação na função em análise, a quantidade de vezes e o nome de cada função chamada. Depois, podemos dizer se é recursivo quando o nome da função chamada for o mesmo da função de análise.
16. Após desenvolver a função que recebe a lista de funções e calcula a complexidade, percebemos que as métricas utilizadas não são suficientes para determinar a complexidade exata em casos de log n ou n log n. Isso por que o analisador sintático apenas determina o que é função, loop ou if/else. Em nenhum momento ele infere sobre a semântica das declarações de variáveis ou condições de parada dos loops, por exemplo.
17. Tentaremos, então, fazer uma análise heurística dos algoritmos. Primeiramente vamos usar o binary search como exemplo a ser solucionado. O binary search, a cada nova iteração do while, divide o problema ao meio. Ou seja, precisamos entender quais variáveis controlam a execução do while e quais alterações elas sofrem no corpo do while. De alguma forma é preciso identificar que há uma espécie de halving nessa execução e, após feita essa identificação, marcaremos uma flag na lista de funções, orientando que aquela função (binary_search) sofre halving. Dessa forma, quando passarmos essa função pelo calculador de complexidade, ele poderá afirmar heuristicamente a complexidade de log n.

//////////////////////////////////////////////////////////////////////////////////////////////////

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

void initFunctionDataList(FunctionDataList \*list) {
list->head = NULL;
list->tail = NULL;
}

void resetFunctionData(FunctionData \*f) {
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
FunctionData \*newFunction = malloc(sizeof(FunctionData)); // Aloca

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
FunctionData \*next = f->next;
free(f); // somente isso!
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
const char\* tokenTypeToString(TokenType type) {
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
char \*text; // Conteúdo
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
void initTokenList(TokenList \*list) {
list->head = NULL;
list->tail = NULL;
}

// Adicionar token no final da lista
void addToken(TokenList *list, TokenType type, const char *text, int line) {
Token \*newToken = malloc(sizeof(Token)); // Aloca

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
Token \*next = t->next;
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
struct Node \*next;
} Node;

// A pilha. Somente aponta para o primeiro elemento (topo).
typedef struct {
Node \*first;
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
Scope pop(Stack \*s) {
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

int getLoopDepth(Stack \*s) {
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
bool is_empty(Stack \*s) {
return s->first == NULL;
}

// Ler arquivo de exemplos
char *read_file(const char *path) {
// Abre arquivo em modo binário de leitura
FILE \*f = fopen(path, "rb");
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
if (strcmp(buffer, "void") == 0) return TOKEN_VOID;
if (strcmp(buffer, "int") == 0) return TOKEN_INT;
if (strcmp(buffer, "float") == 0) return TOKEN_FLOAT;
if (strcmp(buffer, "char") == 0) return TOKEN_CHAR;
if (strcmp(buffer, "for") == 0) return TOKEN_FOR;
if (strcmp(buffer, "while") == 0) return TOKEN_WHILE;
if (strcmp(buffer, "if") == 0) return TOKEN_IF;
if (strcmp(buffer, "else") == 0) return TOKEN_ELSE;
if (strcmp(buffer, "return") == 0) return TOKEN_RETURN;

    // Se não é keyword é Identifier
    return TOKEN_IDENTIFIER;

}

// Função que recebe o código bruto inteiro e converte para lista de tokens
void tokenize(const char *src, TokenList *list) {
int line = 1;
const char \*p = src;

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
const char \*files[] = { // Arquivos a serem lidos
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
    	freeFunctionDataList(&functionList);
    }

    return 0;

}
