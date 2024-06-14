#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cliente.h"
#include "funcionario.h"
#include "quarto.h"
#include "estadia.h"
#include "checkout.h"  // Incluir o cabeçalho checkout.hcsds\v\scd

void menu() {
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Cadastrar funcionário\n");
        printf("3. Cadastrar quarto\n");
        printf("4. Cadastrar estadia\n");
        printf("5. Dar baixa em estadia\n");
        printf("6. Sair\n");
        printf("Digite a opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_cliente();
                break;
            case 2:
                cadastrar_funcionario();
                break;
            case 3:
                cadastrar_quarto();
                break;
            case 4:
                cadastrar_estadia();
                break;
            case 5:
                dar_baixa_estadia();
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 6);
}

int main() {
    carregar_clientes();
    carregar_funcionarios();
    carregar_quartos();
    carregar_estadias();
    menu();
    return 0;
}
