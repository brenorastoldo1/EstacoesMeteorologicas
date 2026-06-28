#include <stdio.h>
#include <stdlib.h>
#include "estacao.h"

void exibirMenu() {
    printf(COR_AZUL "\n=== Sistema de Monitoramento de Estacoes Meteorologicas ===\n" RESET);
    printf(COR_AMARELO "1 - Adicionar\n");
    printf("2 - Editar\n");
    printf("3 - Remover\n");
    printf("4 - Listar\n");
    printf("5 - Buscar por Operador\n");
    printf("6 - Detectar Anomalias\n");
    printf("7 - Salvar CSV\n");
    printf("8 - Carregar CSV\n");
    printf("0 - Sair\n" RESET);
    printf(COR_AZUL "=============================================================\n" RESET);
}

int lerOpcao() {
    int opcao;
    printf("Escolha uma opcao: ");
    if (scanf("%d", &opcao) != 1) {
        // Limpar o buffer em caso de entrada invalida
        while (getchar() != '\n');
        return -1;
    }
    // Consumir a quebra de linha deixada pelo scanf no sucesso
    while (getchar() != '\n');
    return opcao;
}

int main() {
    int opcao;
    struct Estacao *estacoes = NULL;
    int numEstacoes = 0;

    do {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        exibirMenu();
        opcao = lerOpcao();

        switch (opcao) {
            case 1:
                adicionarEstacao(&estacoes, &numEstacoes);
                pausarTela();
                break;
            case 2:
                editarEstacao(estacoes, numEstacoes);
                pausarTela();
                break;
            case 3:
                removerEstacao(&estacoes, &numEstacoes);
                pausarTela();
                break;
            case 4:
                listarEstacoes(estacoes, numEstacoes);
                pausarTela();
                break;
            case 5:
                buscarPorOperador(estacoes, numEstacoes);
                pausarTela();
                break;
            case 6:
                detectarAnomalias(estacoes, numEstacoes);
                pausarTela();
                break;
            case 7:
                salvarCSV(estacoes, numEstacoes);
                pausarTela();
                break;
            case 8:
                carregarCSV(&estacoes, &numEstacoes);
                pausarTela();
                break;
            case 0:
                printf(COR_VERDE "Saindo do sistema...\n" RESET);
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
                printf(COR_VERMELHO "Opcao invalida. Tente novamente.\n" RESET);
                pausarTela();
        }
    } while (opcao != 0);

    return 0;
}
