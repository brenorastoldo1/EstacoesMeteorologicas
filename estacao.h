#ifndef ESTACAO_H
#define ESTACAO_H

struct DataLeitura {
    int dia;
    int mes;
    int ano;
};

struct Estacao {
    int id;
    char nome[60];
    char operador[60];
    char sensor[60];
    int n;
    float *leituras;
    float media;
    float variancia;
    float desvioPadrao;
    struct DataLeitura data;
};

// Cores ANSI para o Terminal (UX)
#define RESET "\x1b[0m"
#define COR_VERDE "\x1b[32m"
#define COR_VERMELHO "\x1b[31m"
#define COR_AZUL "\x1b[36m" // Usando Ciano para ficar mais legível em fundo preto
#define COR_AMARELO "\x1b[33m"

// Funções Auxiliares (Validações e UX)
void pausarTela();
int lerStringValida(char *destino, int tamanho, const char *mensagem);
int lerDataValida(struct DataLeitura *data);
int lerFloatSeguro(const char *mensagem, float *valor);
int lerIntSeguro(const char *mensagem, int min, int max);

// Estatísticas
void calcularEstatisticas(struct Estacao *estacao);
float calcularMediaRecursiva(float *leituras, int n, int indice, float somaAtual);

// Funções de CRUD (Interface de Negócios)
void adicionarEstacao(struct Estacao **estacoes, int *numEstacoes);
void editarEstacao(struct Estacao *estacoes, int numEstacoes);
void removerEstacao(struct Estacao **estacoes, int *numEstacoes);
void listarEstacoes(struct Estacao *estacoes, int numEstacoes);
void buscarPorOperador(struct Estacao *estacoes, int numEstacoes);
void detectarAnomalias(struct Estacao *estacoes, int numEstacoes);

// Manipulação de Arquivos CSV
void salvarCSV(struct Estacao *estacoes, int numEstacoes);
void carregarCSV(struct Estacao **estacoes, int *numEstacoes);

#endif // ESTACAO_H
