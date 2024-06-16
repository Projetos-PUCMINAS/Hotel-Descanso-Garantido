#include "cliente.h"
#include "estadia.h"
#include "funcionario.h"
#include "quarto.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
        printf("9. Mostrar todos os clientes\n");
        printf("10. Mostrar todos os funcionários\n");
        printf("11. Mostrar todos os quartos\n");
        printf("12. Mostrar todas as estadias\n");
        printf("13. Sair\n");
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
                buscar_cliente_por_codigo(termo_busca);
                break;
            }
            case 7: {
                char termo_busca[50];
                printf("Digite o nome ou código do funcionário: ");
                scanf(" %[^\n]", termo_busca);
                buscar_funcionario_por_codigo(termo_busca);
                break;
            }
            case 8: {
                int codigo_cliente;
                printf("Digite o código do cliente: ");
                scanf("%d", &codigo_cliente);
                mostrar_estadias_cliente(codigo_cliente);
                break;
            }
            case 9:
                mostrar_todos_clientes();
                break;
            case 10:
                mostrar_todos_funcionarios();
                break;
            case 11:
                mostrar_todos_quartos();
                break;
            case 12:
                mostrar_todas_estadias();
                break;
            case 13:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 13);
}

int main() {
    carregar_clientes();
    carregar_funcionarios();
    carregar_quartos();
    carregar_estadias();
    menu();
    salvar_clientes();     
    salvar_funcionarios(); 
    salvar_quartos();      
    salvar_estadias();     
    return 0;
}
