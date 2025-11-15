# Relatório sistema de análise de complexidade de algoritmos em C

## Cronologia de decisões sobre o projeto

1. Criar função que lê o arquivo de exemplos
   Armazena todo o conteúdo do arquivo em uma string
2. Separar cada linha da string lida do arquivo em um vetor de strings
   Agora temos um `char **rows` onde a cada posição temos uma linha do código de exemplos
3. Trimar cada linha, ou seja, remover espaços em branco no início e fim
   Agora é possível identificar o comando que inicia a linha
