# Relatório sistema de análise de complexidade de algoritmos em C

## Cronologia de decisões sobre o projeto

1. Criar função que lê o arquivo de exemplos
   Armazena todo o conteúdo do arquivo em uma string
2. Separar cada linha da string lida do arquivo em um vetor de strings
   Agora temos um `char **rows` onde a cada posição temos uma linha do código de exemplos
3. Trimar cada linha, ou seja, remover espaços em branco no início e fim
   Agora é possível identificar o comando que inicia a linha
4. Fazer função que identifica linhas em branco como primeiro teste em cada linha a ser analisada (is_blank)
   Quando encontrar linha em branco, avança direto pra próxima
5. Criar uma pilha que empilhe as aberturas de escopo. Quando encontrar um fechamento de escopo, analisar o que há dentro da pilha até a abertura daquele escopo em específico.
   Exemplo:
   for() { // -> abre o escopo de um for
   if(){} // -> abre e fecha escopo de um if
   for() {} // -> abre e fecha escopo de um for
   } // -> fecha o escopo de um for
   Encontrou fechamento
6. Criar um enum com os tipos de escopo possíveis
   BLOCK, PAREN, BRACKET, FOR, WHILE, IF, FUNCTION

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
