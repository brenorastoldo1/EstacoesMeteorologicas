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

// Assinaturas de funcoes (a serem implementadas no futuro)

#endif // ESTACAO_H
