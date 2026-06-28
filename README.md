# Sistema de Monitoramento de Estacoes Meteorologicas

Ola! Este e o repositorio do meu trabalho pratico da disciplina. O objetivo principal deste projeto foi desenvolver um sistema em C para gerenciar e analisar dados de estacoes meteorologicas, aplicando conceitos importantes que aprendemos ao longo do semestre.

## O que tem debaixo do capo?

Escrevi o codigo focando em deixar a arquitetura bem modularizada (separando a logica de negocio da interface do usuario entre `main.c`, `estacao.c` e `estacao.h`). Abaixo estao os principais conceitos tecnicos que apliquei para fazer tudo funcionar perfeitamente:

- **Alocacao Dinamica de Memoria:** Como a quantidade de estacoes e o numero de leituras de cada estacao podem variar bastante, optei por nao usar vetores estaticos limitados. Usei ponteiros duplos e gerenciei tudo com `malloc`, `realloc` e, claro, o `free` (para garantir que nao haja nenhum "memory leak" quando excluímos uma estacao ou saimos do programa).
- **Structs Aninhadas:** Criei a estrutura base `Estacao` e uma estrutura auxiliar `DataLeitura`, agrupando os dados de cada estacao de forma limpa e organizada.
- **Estatistica & Anomalias:** O sistema calcula a Variancia e o Desvio-Padrao (utilizando a biblioteca `<math.h>`). Para o sistema acusar uma anomalia ambiental, o dado precisa ser superior a barreira matematica de `Media + (2 * Desvio-Padrao)` ou inferior a `Media - (2 * Desvio-Padrao)`. 
- **Recursividade:** Implementei a funcao `calcularMediaRecursiva()`, que percorre o vetor dinamico de leituras incrementando o indice ate o caso base, somando tudo sem precisar de laços `for` ou `while`!
- **Persistencia de Dados (CSV):** O sistema nao perde os dados ao ser fechado. Criei uma rotina de Leitura/Escrita manipulando o arquivo `.csv`. O maior desafio aqui foi utilizar a funcao `strtok` para separar corretamente as propriedades da estacao (que sao separadas por virgula `,`) e as leituras do sensor em si (que ficam em uma celula final agrupadas por ponto-e-virgula `;`).
- **Validacoes & Experiencia (UX):** Deixei o terminal bem mais amigavel! Adicionei limpezas de tela (`cls`), limpezas de buffer (`fflush`/`getchar`), e uso codigos ANSI para imprimir textos coloridos (verde para sucesso, vermelho para erros). Alem de travar bugs, o usuario pode digitar `-1` a qualquer momento em qualquer input do sistema para cancelar o processo e voltar ao menu de forma segura.

## Como compilar e testar

Para rodar o projeto na sua maquina, basta abrir o terminal na raiz do projeto e rodar a compilacao:

```bash
gcc main.c estacao.c -o sistema_estacoes.exe -lm
```
*(O parametro `-lm` no final e crucial em compiladores como o MinGW ou no Linux para linkar a biblioteca matematica `<math.h>` do desvio-padrao!)*

Depois de compilado, basta iniciar o executavel:
```bash
./sistema_estacoes.exe
```

Fique a vontade para testar as validacoes de letras, inserir anomalias matematicas no sensor e brincar com o codigo. Deu um trabalho excelente, mas serviu muito para sedimentar a logica de ponteiros na cabeca! Espero que goste da correcao!