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
                CadastrarCliente();
                break;
            case 2:
                CadastrarFuncionario();
                break;
            case 3:
                CadastrarQuarto();
                break;
            case 4:
                CadastrarEstadia();
                break;
            case 5:
                DarBaixaEstadia();
                break;
            case 6: {
                char termo_busca[50];
                printf("Digite o nome ou código do cliente: ");
                scanf(" %[^\n]", termo_busca);
                BuscarClienteCodigo(termo_busca);
                break;
            }
            case 7: {
                char termo_busca[50];
                printf("Digite o nome ou código do funcionário: ");
                scanf(" %[^\n]", termo_busca);
                BuscarFuncionarioCodigo(termo_busca);
                break;
            }
            case 8: {
                int codigo_cliente;
                printf("Digite o código do cliente: ");
                scanf("%d", &codigo_cliente);
                MostrarEstadiasCliente(codigo_cliente);
                break;
            }
            case 9:
                MostrarTodosClientes();
                break;
            case 10:
                MostrarTodosFuncionarios();
                break;
            case 11:
                MostrarTodosQuartos();
                break;
            case 12:
                MostrarTodasEstadias();
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
    CarregarClientes();
    CarregarFuncionarios();
    CarregarQuartos();
    CarregarEstadias();
    menu();
    SalvarClientes();     
    SalvarFuncionarios(); 
    SalvarQuartos();      
    SalvarEstadias();     
    return 0;
}
