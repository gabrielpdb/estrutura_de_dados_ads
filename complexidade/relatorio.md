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

//////////////////////////////////////////////////////////////////////////////////////////////////

void scan_line(const char *line, int lineno) {
const char *p = line;
while (*p) {
// Ignora espaços
if (*p == ' ' || \*p == '\t') { p++; continue; }

        // Comentário
        if (*p == '/' && *(p+1) == '/') {
            printf("Linha %d: TOKEN_COMMENT: %s\n", lineno, p);
            break; // resto da linha é comentário
        }

        // Símbolos
        if (strchr("(){}[];", *p)) {
            printf("Linha %d: TOKEN_SYMBOL: %c\n", lineno, *p);
            p++; continue;
        }

        // Palavra (identificador ou keyword)
        if (isalpha(*p) || *p == '_') {
            const char *start = p;
            while (isalnum(*p) || *p=='_') p++;
            int len = p - start;
            char buf[128];
            strncpy(buf, start, len); buf[len]='\0';
            // aqui você pode checar se é keyword (for, while, void...)
            printf("Linha %d: TOKEN_WORD: %s\n", lineno, buf);
            continue;
        }

        // Número
        if (isdigit(*p)) {
            const char *start = p;
            while (isdigit(*p)) p++;
            int len = p - start;
            char buf[64]; strncpy(buf, start, len); buf[len]='\0';
            printf("Linha %d: TOKEN_NUMBER: %s\n", lineno, buf);
            continue;
        }

        p++; // qualquer outro caractere
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////

Mano, **você tá exatamente no caminho certo** — isso é literalmente como todo _parser_ simples funciona.
E o seu projeto pede _exatamente esse tipo de análise estrutural_.
Então sim, tá **perfeito**.

Vamos direto ao ponto:

---

# ✔ Sua ideia da pilha de escopos está 100% correta.

## **1. Caminhar a linha char por char**

Isso permite detectar símbolos estruturais:

- `{` → abre bloco
- `}` → fecha bloco
- `(` → abre argumento/expressão
- `)` → fecha
- `[` → abre indexação
- `]` → fecha

---

# ✔ 2. Usar **pilha** para gerenciar escopos

### Quando achar um símbolo de abertura:

```c
push(pilha, simbolo);
```

### Quando achar um símbolo de fechamento:

```c
char top = pop(pilha);

// opcional: validar se combina corretamente
if (!combina(top, simbolo_fechando)) erro;
```

---

# ✔ 3. O **pulo do gato** no seu projeto

Quando você detecta o fechamento de um bloco **com }**, é aí que você consegue analisar a complexidade dentro dele.

Exemplo:

```
for (...) {
    for (...) {
    }
}
```

→ Você empilha `{`
→ Quando fecha `}`, você sabe exatamente **quantos loops estavam ativos** naquele nível.

E isso define:

- Um loop → O(n)
- Dois loops aninhados → O(n²)
- Três loops aninhados → O(n³)

---

# ✔ 4. Como estruturar a pilha

Você não vai guardar só o caractere `{`.

O ideal é guardar **tipo do escopo**:

```c
typedef enum {
    SCOPE_BLOCK,   // { }
    SCOPE_PAREN,   // ( )
    SCOPE_BRACKET, // [ ]
    SCOPE_FOR,     // corpo do for
    SCOPE_WHILE,
    SCOPE_IF,
    SCOPE_FUNCTION
} ScopeType;

typedef struct {
    ScopeType type;
    int line;
} Scope;
```

Assim você sabe:

- Esse `{` é de um `for` ou de um `if`?
- O bloco é parte da função?
- Esse `for` tem outro `for` dentro?

---

# ✔ 5. A lógica completa (resumo)

### A cada linha:

1. Remova espaços/brancos (`trim`).
2. Ignore comentários.
3. Caminhe char por char:

   - Se encontrar `"for"` → sinaliza que o próximo `{` é escopo de loop.
   - Se encontrar `"while"` → idem.
   - Se encontrar `"{"` → dá push na pilha com tipo detectado.
   - Se encontrar `"}"` → dá pop e ANALISA COMPLEXIDADE DO BLOCO FECHADO.

---

# ✔ 6. Esse método funciona para **todos os casos do seu projeto**

- loops aninhados → O(n^k)
- busca binária → se detectar divisão por 2 → O(log n)
- merge sort → detectar recursão + divisão → O(n log n)
- fibonacci recursivo → recursão dupla → O(2^n)
- funções → delimitadas por `{ }` e pela palavra `void`/tipo

---

# ✔ CONCLUSÃO

Sim, você acertou em cheio:
**pilha de escopos + leitura char a char = solução ideal para o analisador de complexidade.**

Se quiser, eu posso te dar:

👉 o código da pilha
👉 a estrutura completa de escopo
👉 o parse das palavras-chave
👉 o sistema de contagem de loops por nível

Só pedir.
