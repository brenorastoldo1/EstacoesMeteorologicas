#include "estacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

void pausarTela() {
    printf(COR_AMARELO "\nPressione ENTER para continuar..." RESET);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void mostrarEstacoesDisponiveis(struct Estacao *estacoes, int numEstacoes) {
    if (numEstacoes == 0) return;
    printf(COR_AZUL "\n--- Estacoes Cadastradas no Sistema ---\n" RESET);
    for (int i = 0; i < numEstacoes; i++) {
        printf("ID: %04d | Nome: %s\n", estacoes[i].id, estacoes[i].nome);
    }
    printf(COR_AZUL "---------------------------------------\n\n" RESET);
}

void mostrarOperadoresDisponiveis(struct Estacao *estacoes, int numEstacoes) {
    if (numEstacoes == 0) return;
    printf(COR_AZUL "\n--- Operadores Cadastrados ---\n" RESET);
    for (int i = 0; i < numEstacoes; i++) {
        printf(" - %s\n", estacoes[i].operador);
    }
    printf(COR_AZUL "------------------------------\n\n" RESET);
}

int lerStringValida(char *destino, int tamanho, const char *mensagem) {
    int valido;
    do {
        valido = 1;
        printf("%s", mensagem);
        if (fgets(destino, tamanho, stdin) != NULL) {
            destino[strcspn(destino, "\n")] = 0; // remover newline
            
            if (strcmp(destino, "-1") == 0) return 0; // cancelado
            
            if (strlen(destino) == 0) {
                valido = 0;
            } else {
                for (int i = 0; destino[i] != '\0'; i++) {
                    if (!isalpha(destino[i]) && destino[i] != ' ') {
                        valido = 0;
                        break;
                    }
                }
            }
            if (!valido) {
                printf(COR_VERMELHO "Entrada invalida. Use apenas letras e espacos.\n" RESET);
            }
        }
    } while (!valido);
    return 1;
}

int ehBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int lerDataValida(struct DataLeitura *data) {
    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int valido = 0;
    char linha[100];
    
    do {
        printf("Digite a data (DD MM AAAA) ou -1 para cancelar: ");
        if (fgets(linha, sizeof(linha), stdin) != NULL) {
            linha[strcspn(linha, "\n")] = 0;
            if (strcmp(linha, "-1") == 0) return 0; // cancelado
            
            if (sscanf(linha, "%d %d %d", &data->dia, &data->mes, &data->ano) == 3) {
                if (data->ano > 0 && data->mes >= 1 && data->mes <= 12) {
                    int maxDias = diasNoMes[data->mes];
                    if (data->mes == 2 && ehBissexto(data->ano)) {
                        maxDias = 29;
                    }
                    if (data->dia >= 1 && data->dia <= maxDias) {
                        valido = 1;
                    }
                }
            }
        }
        
        if (!valido) {
            printf(COR_VERMELHO "Data invalida. Certifique-se de usar espacos (Ex: 15 10 2025).\n" RESET);
        }
    } while (!valido);
    
    return 1;
}

int lerFloatSeguro(const char *mensagem, float *valor) {
    char linha[100];
    do {
        printf("%s", mensagem);
        if (fgets(linha, sizeof(linha), stdin) != NULL) {
            linha[strcspn(linha, "\n")] = 0;
            if (strcmp(linha, "-1") == 0) return 0; // cancelado
            
            if (sscanf(linha, "%f", valor) == 1) {
                return 1; // sucesso
            }
        }
        printf(COR_VERMELHO "Entrada invalida. Digite um numero real.\n" RESET);
    } while (1);
}

int lerIntSeguro(const char *mensagem, int min, int max) {
    int valor;
    int lido;
    do {
        printf("%s", mensagem);
        lido = scanf("%d", &valor);
        limparBuffer();
        if (lido != 1 || (valor < min && valor != -1) || valor > max) {
            printf(COR_VERMELHO "Entrada invalida. Digite um numero entre %d e %d.\n" RESET, min, max);
            lido = 0;
        }
    } while (lido != 1);
    return valor;
}

float calcularMediaRecursiva(float *leituras, int n, int indice, float somaAtual) {
    if (indice == n) {
        return somaAtual / n;
    }
    return calcularMediaRecursiva(leituras, n, indice + 1, somaAtual + leituras[indice]);
}

void calcularEstatisticas(struct Estacao *estacao) {
    if (estacao->n <= 0) return;
    
    estacao->media = calcularMediaRecursiva(estacao->leituras, estacao->n, 0, 0.0);
    
    float somaDiferencasQuadrado = 0.0;
    for (int i = 0; i < estacao->n; i++) {
        float diferenca = estacao->leituras[i] - estacao->media;
        somaDiferencasQuadrado += (diferenca * diferenca);
    }
    
    estacao->variancia = somaDiferencasQuadrado / estacao->n;
    estacao->desvioPadrao = sqrt(estacao->variancia);
}

void adicionarEstacao(struct Estacao **estacoes, int *numEstacoes) {
    struct Estacao nova;
    
    nova.id = lerIntSeguro("Digite o ID da estacao (0-9999) ou -1 para cancelar: ", 0, 9999);
    if (nova.id == -1) {
        printf(COR_AMARELO "Operacao cancelada pelo usuario.\n" RESET);
        return;
    }
    
    for (int i = 0; i < *numEstacoes; i++) {
        if ((*estacoes)[i].id == nova.id) {
            printf(COR_VERMELHO "Erro: ID ja existe.\n" RESET);
            return;
        }
    }
    
    if (!lerStringValida(nova.nome, 60, "Digite o nome da estacao (ou -1 para cancelar): ")) { printf(COR_AMARELO "Cancelado.\n" RESET); return; }
    if (!lerStringValida(nova.operador, 60, "Digite o operador responsavel (ou -1 para cancelar): ")) { printf(COR_AMARELO "Cancelado.\n" RESET); return; }
    if (!lerStringValida(nova.sensor, 60, "Digite o tipo de sensor (ou -1 para cancelar): ")) { printf(COR_AMARELO "Cancelado.\n" RESET); return; }
    
    if (!lerDataValida(&nova.data)) { printf(COR_AMARELO "Cancelado.\n" RESET); return; }
    
    nova.n = lerIntSeguro("Digite a quantidade de leituras (1-9998) ou -1 para cancelar: ", 1, 9998);
    if (nova.n == -1) { printf(COR_AMARELO "Cancelado.\n" RESET); return; }
    
    nova.leituras = (float *)malloc(nova.n * sizeof(float));
    if (nova.leituras == NULL) {
        printf(COR_VERMELHO "Erro de alocacao de memoria.\n" RESET);
        return;
    }
    
    for (int i = 0; i < nova.n; i++) {
        char msg[100];
        snprintf(msg, sizeof(msg), "Leitura %d (ou -1 para cancelar): ", i + 1);
        if (!lerFloatSeguro(msg, &nova.leituras[i])) {
            printf(COR_AMARELO "Cancelado pelo usuario.\n" RESET);
            free(nova.leituras);
            return;
        }
    }
    
    calcularEstatisticas(&nova);
    
    struct Estacao *temp = realloc(*estacoes, (*numEstacoes + 1) * sizeof(struct Estacao));
    if (temp == NULL) {
        printf(COR_VERMELHO "Erro ao redimensionar memoria para estacoes.\n" RESET);
        free(nova.leituras);
        return;
    }
    
    *estacoes = temp;
    (*estacoes)[*numEstacoes] = nova;
    (*numEstacoes)++;
    
    printf(COR_VERDE "Estacao adicionada com sucesso!\n" RESET);
}

void editarEstacao(struct Estacao *estacoes, int numEstacoes) {
    if (numEstacoes == 0) {
        printf(COR_VERMELHO "Nenhuma estacao para editar.\n" RESET);
        return;
    }
    
    mostrarEstacoesDisponiveis(estacoes, numEstacoes);
    int id = lerIntSeguro("Digite o ID da estacao a editar (ou -1 para cancelar): ", 0, 9999);
    if (id == -1) {
        printf(COR_AMARELO "Operacao cancelada pelo usuario.\n" RESET);
        return;
    }
    
    for (int i = 0; i < numEstacoes; i++) {
        if (estacoes[i].id == id) {
            printf("Estacao encontrada: %s\n", estacoes[i].nome);
            printf("1-Nome, 2-Operador, 3-Sensor, 4-Data\n");
            int opcao = lerIntSeguro("O que deseja editar (1-4) ou -1 para cancelar? ", -1, 4);
            
            if (opcao == -1) {
                printf(COR_AMARELO "Edicao cancelada pelo usuario.\n" RESET);
                return;
            }
            
            if (opcao == 1) {
                if (!lerStringValida(estacoes[i].nome, 60, "Novo nome (ou -1 para cancelar): ")) { printf(COR_AMARELO "Cancelado.\n" RESET); return; }
            }
            else if (opcao == 2) {
                if (!lerStringValida(estacoes[i].operador, 60, "Novo operador (ou -1 para cancelar): ")) { printf(COR_AMARELO "Cancelado.\n" RESET); return; }
            }
            else if (opcao == 3) {
                if (!lerStringValida(estacoes[i].sensor, 60, "Novo sensor (ou -1 para cancelar): ")) { printf(COR_AMARELO "Cancelado.\n" RESET); return; }
            }
            else if (opcao == 4) {
                if (!lerDataValida(&estacoes[i].data)) { printf(COR_AMARELO "Cancelado.\n" RESET); return; }
            }
            
            printf(COR_VERDE "Estacao atualizada com sucesso!\n" RESET);
            return;
        }
    }
    printf(COR_VERMELHO "Estacao com ID %d nao encontrada.\n" RESET, id);
}

void removerEstacao(struct Estacao **estacoes, int *numEstacoes) {
    if (*numEstacoes == 0) {
        printf(COR_VERMELHO "Nenhuma estacao para remover.\n" RESET);
        return;
    }
    
    mostrarEstacoesDisponiveis(*estacoes, *numEstacoes);
    int id = lerIntSeguro("Digite o ID da estacao a remover (ou -1 para cancelar): ", 0, 9999);
    if (id == -1) {
        printf(COR_AMARELO "Operacao cancelada pelo usuario.\n" RESET);
        return;
    }
    
    for (int i = 0; i < *numEstacoes; i++) {
        if ((*estacoes)[i].id == id) {
            free((*estacoes)[i].leituras);
            
            for (int j = i; j < *numEstacoes - 1; j++) {
                (*estacoes)[j] = (*estacoes)[j + 1];
            }
            
            (*numEstacoes)--;
            
            if (*numEstacoes > 0) {
                struct Estacao *temp = realloc(*estacoes, (*numEstacoes) * sizeof(struct Estacao));
                if (temp != NULL) {
                    *estacoes = temp;
                }
            } else {
                free(*estacoes);
                *estacoes = NULL;
            }
            
            printf(COR_VERDE "Estacao removida com sucesso.\n" RESET);
            return;
        }
    }
    printf(COR_VERMELHO "Estacao com ID %d nao encontrada.\n" RESET, id);
}

void listarEstacoes(struct Estacao *estacoes, int numEstacoes) {
    if (numEstacoes == 0) {
        printf(COR_VERMELHO "Nenhuma estacao cadastrada.\n" RESET);
        return;
    }
    
    for (int i = 0; i < numEstacoes; i++) {
        printf(COR_AZUL "\n--- Estacao ID: %04d ---\n" RESET, estacoes[i].id);
        printf("Nome:\t\t%s\nOperador:\t%s\nSensor:\t\t%s\n", 
            estacoes[i].nome, estacoes[i].operador, estacoes[i].sensor);
        printf("Data:\t\t%02d/%02d/%04d\n", 
            estacoes[i].data.dia, estacoes[i].data.mes, estacoes[i].data.ano);
        printf("N. Leituras:\t%d\n", estacoes[i].n);
        printf(COR_VERDE "Media:\t\t%.2f\nVariancia:\t%.2f\nDesvio-Padrao:\t%.2f\n" RESET, 
            estacoes[i].media, estacoes[i].variancia, estacoes[i].desvioPadrao);
    }
}

void buscarPorOperador(struct Estacao *estacoes, int numEstacoes) {
    if (numEstacoes == 0) {
        printf(COR_VERMELHO "Nenhuma estacao cadastrada.\n" RESET);
        return;
    }
    mostrarOperadoresDisponiveis(estacoes, numEstacoes);
    
    char operador[60];
    if (!lerStringValida(operador, 60, "Digite o nome do operador para busca (ou -1 para cancelar): ")) {
        printf(COR_AMARELO "Busca cancelada.\n" RESET);
        return;
    }
    
    int encontrou = 0;
    for (int i = 0; i < numEstacoes; i++) {
        if (strcmp(estacoes[i].operador, operador) == 0) {
            printf(COR_VERDE "\nID: %04d | Nome: %s\n" RESET, estacoes[i].id, estacoes[i].nome);
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf(COR_VERMELHO "Nenhuma estacao encontrada para o operador '%s'.\n" RESET, operador);
    }
}

void detectarAnomalias(struct Estacao *estacoes, int numEstacoes) {
    if (numEstacoes == 0) {
        printf(COR_VERMELHO "Nenhuma estacao cadastrada para checar.\n" RESET);
        return;
    }
    mostrarEstacoesDisponiveis(estacoes, numEstacoes);
    int id = lerIntSeguro("Digite o ID da estacao para checar (ou -1 para cancelar): ", 0, 9999);
    if (id == -1) {
        printf(COR_AMARELO "Operacao cancelada pelo usuario.\n" RESET);
        return;
    }
    
    for (int i = 0; i < numEstacoes; i++) {
        if (estacoes[i].id == id) {
            printf(COR_AMARELO "Checando anomalias na estacao %s...\n" RESET, estacoes[i].nome);
            printf("Limites matematicos da amostra: (Media: %.2f | 2*Desvio: %.2f)\n", 
                estacoes[i].media, 2 * estacoes[i].desvioPadrao);
            
            int encontrou = 0;
            for (int j = 0; j < estacoes[i].n; j++) {
                if (fabs(estacoes[i].leituras[j] - estacoes[i].media) > 2 * estacoes[i].desvioPadrao) {
                    printf(COR_VERMELHO "  [!] ALERTA - Leitura %d: %.2f se afasta muito da media!\n" RESET, j + 1, estacoes[i].leituras[j]);
                    encontrou = 1;
                }
            }
            if (!encontrou) {
                printf(COR_VERDE "  Nenhuma anomalia detectada matematicamente.\n" RESET);
            }
            return;
        }
    }
    printf(COR_VERMELHO "Estacao com ID %d nao encontrada.\n" RESET, id);
}

void salvarCSV(struct Estacao *estacoes, int numEstacoes) {
    if (numEstacoes == 0) {
        printf(COR_VERMELHO "Nao ha dados para salvar no CSV.\n" RESET);
        return;
    }
    
    FILE *arquivo = fopen("dados.csv", "w");
    if (arquivo == NULL) {
        printf(COR_VERMELHO "Erro ao criar o arquivo CSV.\n" RESET);
        return;
    }
    
    fprintf(arquivo, "ID,Nome,Operador,Sensor,Data,N,Media,Variancia,DesvioPadrao,Leituras\n");
    
    for (int i = 0; i < numEstacoes; i++) {
        fprintf(arquivo, "%d,%s,%s,%s,%02d/%02d/%04d,%d,%.2f,%.2f,%.2f,", 
            estacoes[i].id, estacoes[i].nome, estacoes[i].operador, estacoes[i].sensor,
            estacoes[i].data.dia, estacoes[i].data.mes, estacoes[i].data.ano,
            estacoes[i].n, estacoes[i].media, estacoes[i].variancia, estacoes[i].desvioPadrao);
            
        for (int j = 0; j < estacoes[i].n; j++) {
            fprintf(arquivo, "%.2f%s", estacoes[i].leituras[j], (j == estacoes[i].n - 1) ? "" : ";");
        }
        fprintf(arquivo, "\n");
    }
    
    fclose(arquivo);
    printf(COR_VERDE "Dados salvos com sucesso em dados.csv!\n" RESET);
}

void carregarCSV(struct Estacao **estacoes, int *numEstacoes) {
    FILE *arquivo = fopen("dados.csv", "r");
    if (arquivo == NULL) {
        printf(COR_VERMELHO "Arquivo dados.csv nao encontrado. Salve primeiro.\n" RESET);
        return;
    }
    
    for (int i = 0; i < *numEstacoes; i++) {
        free((*estacoes)[i].leituras);
    }
    free(*estacoes);
    *estacoes = NULL;
    *numEstacoes = 0;
    
    char linha[1024];
    fgets(linha, sizeof(linha), arquivo);
    
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strcspn(linha, "\n")] = 0;
        
        struct Estacao nova;
        char *token = strtok(linha, ",");
        if (token == NULL) continue;
        nova.id = atoi(token);
        
        token = strtok(NULL, ","); strcpy(nova.nome, token);
        token = strtok(NULL, ","); strcpy(nova.operador, token);
        token = strtok(NULL, ","); strcpy(nova.sensor, token);
        
        token = strtok(NULL, ",");
        sscanf(token, "%d/%d/%d", &nova.data.dia, &nova.data.mes, &nova.data.ano);
        
        token = strtok(NULL, ","); nova.n = atoi(token);
        token = strtok(NULL, ","); nova.media = atof(token);
        token = strtok(NULL, ","); nova.variancia = atof(token);
        token = strtok(NULL, ","); nova.desvioPadrao = atof(token);
        
        nova.leituras = (float *)malloc(nova.n * sizeof(float));
        token = strtok(NULL, ","); 
        
        if (token != NULL) {
            char *ptr = token;
            for (int i = 0; i < nova.n; i++) {
                nova.leituras[i] = strtof(ptr, &ptr);
                if (*ptr == ';') ptr++;
            }
        }
        
        struct Estacao *temp = realloc(*estacoes, (*numEstacoes + 1) * sizeof(struct Estacao));
        *estacoes = temp;
        (*estacoes)[*numEstacoes] = nova;
        (*numEstacoes)++;
    }
    
    fclose(arquivo);
    printf(COR_VERDE "Dados carregados com sucesso! (%d estacoes encontradas)\n" RESET, *numEstacoes);
}
