#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cliente.h"
#include "funcionario.h"
#include "quarto.h"
#include "estadia.h"

void menu() {
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Cadastrar funcionário\n");
        printf("3. Cadastrar quarto\n");
        printf("4. Cadastrar estadia\n");
        printf("5. Dar baixa em estadia\n");
        printf("6. Buscar cliente por código\n");
        printf("7. Buscar funcionário por código\n");
        printf("8. Mostrar estadias de um cliente\n");
        printf("9. Sair\n");
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
            case 6: {
                char termo_busca[50];
                printf("Digite o nome ou código do cliente: ");
                scanf(" %[^\n]", termo_busca);
                buscar_cliente_por_nome_ou_codigo(termo_busca);
                break;
            }
            case 7: {
                char termo_busca[50];
                printf("Digite o nome ou código do funcionário: ");
                scanf(" %[^\n]", termo_busca);
                buscar_funcionario_por_nome_ou_codigo(termo_busca);
                break;
            }
            case 8: {
                char termo_busca[50];
                printf("Digite o nome ou código do cliente: ");
                scanf(" %[^\n]", termo_busca);
                mostrar_estadias_cliente(termo_busca);
                break;
            }
            case 9:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 9);
}

int main() {
    carregar_clientes();
    carregar_funcionarios();
    carregar_quartos();
    carregar_estadias();
    menu();
    salvar_clientes(); // Salva os clientes ao sair do programa
    salvar_funcionarios(); // Salva os funcionários ao sair do programa
    salvar_quartos(); // Salva os quartos ao sair do programa
    salvar_estadias(); // Salva as estadias ao sair do programa
    return 0;
}
