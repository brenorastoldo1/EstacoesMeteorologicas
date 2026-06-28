#include <stdio.h>
#include <stdlib.h>
#include "estacao.h"

void exibirMenu() {
    printf("\n=== Sistema de Monitoramento de Estacoes Meteorologicas ===\n");
    printf("1 - Adicionar\n");
    printf("2 - Editar\n");
    printf("3 - Remover\n");
    printf("4 - Listar\n");
    printf("5 - Buscar por Operador\n");
    printf("6 - Detectar Anomalias\n");
    printf("7 - Salvar CSV\n");
    printf("8 - Carregar CSV\n");
    printf("0 - Sair\n");
    printf("=============================================================\n");
}

int lerOpcao() {
    int opcao;
    printf("Escolha uma opcao: ");
    if (scanf("%d", &opcao) != 1) {
        // Limpar o buffer em caso de entrada invalida
        while (getchar() != '\n');
        return -1;
    }
    return opcao;
}

int main() {
    int opcao;
    struct Estacao *estacoes = NULL;
    int numEstacoes = 0;

    do {
        exibirMenu();
        opcao = lerOpcao();

        switch (opcao) {
            case 1:
                adicionarEstacao(&estacoes, &numEstacoes);
                break;
            case 2:
                editarEstacao(estacoes, numEstacoes);
                break;
            case 3:
                removerEstacao(&estacoes, &numEstacoes);
                break;
            case 4:
                listarEstacoes(estacoes, numEstacoes);
                break;
            case 5:
                buscarPorOperador(estacoes, numEstacoes);
                break;
            case 6:
                detectarAnomalias(estacoes, numEstacoes);
                break;
            case 7:
                salvarCSV(estacoes, numEstacoes);
                break;
            case 8:
                carregarCSV(&estacoes, &numEstacoes);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                // Liberar memoria alocada antes de sair
                for (int i = 0; i < numEstacoes; i++) {
                    if (estacoes[i].leituras != NULL) {
                        free(estacoes[i].leituras);
                    }
                }
                if (estacoes != NULL) {
                    free(estacoes);
                }
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
