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

    do {
        exibirMenu();
        opcao = lerOpcao();

        switch (opcao) {
            case 1:
                printf("Em desenvolvimento...\n");
                break;
            case 2:
                printf("Em desenvolvimento...\n");
                break;
            case 3:
                printf("Em desenvolvimento...\n");
                break;
            case 4:
                printf("Em desenvolvimento...\n");
                break;
            case 5:
                printf("Em desenvolvimento...\n");
                break;
            case 6:
                printf("Em desenvolvimento...\n");
                break;
            case 7:
                printf("Em desenvolvimento...\n");
                break;
            case 8:
                printf("Em desenvolvimento...\n");
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
