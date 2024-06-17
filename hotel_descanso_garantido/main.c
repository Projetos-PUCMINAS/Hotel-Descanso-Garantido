#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "funcionarios.h"
#include "quartos.h"
#include "estadias.h"

int main() {
    FILE *f_clientes;
    FILE *f_funcionarios;
    FILE *f_quartos;
    FILE *f_estadias;
    char op;

    // Inicializa o sistema de clientes
    f_clientes = inicializa_sistema();

    // Inicializa o sistema de funcionários
    f_funcionarios = inicializa_sistema_func();

    // Inicializa o sistema de quartos
    f_quartos = inicializa_sistema_quartos();

    // Inicializa o sistema de estadias
    f_estadias = inicializa_sistema_estadias();

    do {
        printf("\nEscolha:\n");
        printf("1 - Menu de Clientes\n");
        printf("2 - Menu de Funcionários\n");
        printf("3 - Menu de Quartos\n");
        printf("4 - Menu de Estadias\n");
        printf("5 - Sair do sistema\n");
        op = getchar();
        getchar(); // Consume newline left by getchar
        switch (op) {
            case '1':
                // Menu de Clientes
            do {
                printf("\nMenu Clientes:\n");
                printf("a - Cadastrar cliente\n");
                printf("b - Alterar cliente\n");
                printf("c - Excluir cliente\n");
                printf("d - Listar todos os clientes\n");
                printf("e - Pesquisar cliente por nome\n");
                printf("f - Pesquisar cliente por código\n");
                printf("g - Voltar ao menu anterior\n");
                op = getchar();
                getchar(); // Consume newline left by getchar
                switch (op) {
                    case 'a':
                        cadastra_cliente(f_clientes);
                        break;
                    case 'b':
                        altera_cliente(f_clientes);
                        break;
                    case 'c':
                        exclui_cliente(f_clientes);
                        break;
                    case 'd':
                        imprime_clientes(f_clientes, f_estadias);
                        system("pause");
                        break;
                    case 'e': {
                        int cod_cliente;
                        printf("Digite o código do cliente para pesquisar: ");
                        scanf("%d", &cod_cliente);
                        getchar(); // Consume newline left by scanf

                        pesquisa_cliente_por_codigo(f_clientes, cod_cliente);
                        system("pause");
                        break;
                    }
                    case 'f': {
                        char nome[50];
                        printf("Digite o nome do cliente para pesquisar: ");
                        fgets(nome, sizeof(nome), stdin);
                        nome[strcspn(nome, "\n")] = '\0'; // Remove newline if present

                        pesquisa_cliente_por_nome(f_clientes, nome);
                        system("pause");
                        while (getchar() != '\n'); // Limpa o buffer de entrada
                        break;
                    }
                }
            } while (op != 'g');
            break;
            case '2':
                // Menu de Funcionários
                do {
                    printf("\nMenu Funcionários:\n");
                    printf("a - Cadastrar funcionário\n");
                    printf("b - Alterar funcionário\n");
                    printf("c - Excluir funcionário\n");
                    printf("d - Listar todos os funcionários\n");
                    printf("e - Pesquisar funcionário por código\n");
                    printf("f - Pesquisar funcionário por nome\n");
                    printf("g - Voltar ao menu anterior\n");
                    op = getchar();
                    getchar(); // Consume newline left by getchar
                    switch (op) {
                        case 'a':
                            cadastra_funcionario(f_funcionarios);
                            break;
                        case 'b':
                            altera_funcionario(f_funcionarios);
                            break;
                        case 'c':
                            exclui_funcionario(f_funcionarios);
                            break;
                        case 'd':
                            imprime_funcionarios(f_funcionarios);
                            system("pause");
                            break;
                        case 'e': {
                            int cod;
                            printf("Digite o código do funcionário: ");
                            scanf("%d", &cod);
                            getchar(); // Consume newline left by scanf
                            pesquisa_funcionario_por_codigo(f_funcionarios, cod);
                            system("pause");
                            break;
                        }
                        case 'f': {
                            char nome[50];
                            printf("Digite o nome do funcionário: ");
                            fgets(nome, sizeof(nome), stdin);
                            nome[strcspn(nome, "\n")] = '\0'; // Remove newline if present

                            pesquisa_funcionario_por_nome(f_funcionarios, nome);
                            system("pause");
                            while (getchar() != '\n'); // Limpa o buffer de entrada
                            break;
                        }
                    }
                } while (op != 'g');
                break;
            case '3':
                // Menu de Quartos
                do {
                    printf("\nMenu Quartos:\n");
                    printf("a - Cadastrar quarto\n");
                    printf("b - Alterar quarto\n");
                    printf("c - Excluir quarto\n");
                    printf("d - Listar todos os quartos\n");
                    printf("e - Voltar ao menu anterior\n");
                    op = getchar();
                    getchar(); // Consume newline left by getchar
                    switch (op) {
                        case 'a':
                            cadastra_quarto(f_quartos);
                            break;
                        case 'b':
                            altera_quarto(f_quartos);
                            break;
                        case 'c':
                            exclui_quarto(f_quartos);
                            break;
                        case 'd':
                            imprime_quartos(f_quartos);
                            system("pause");
                            break;
                    }
                } while (op != 'e');
                break;
            case '4':
                // Menu de Estadias
                do {
                    printf("\nMenu Estadias:\n");
                    printf("a - Cadastrar estadia\n");
                    printf("b - Listar todas as estadias\n");
                    printf("c - Baixa de estadia\n");
                    printf("d - Voltar ao menu anterior\n");
                    op = getchar();
                    getchar(); // Consume newline left by getchar
                    switch (op) {
                        case 'a':
                            cadastra_estadia(f_estadias, f_clientes, f_quartos);
                            break;
                        case 'b':
                            imprime_estadias(f_estadias);
                            system("pause");
                            break;
                        case 'c':
                            {
                                int codigo_estadia;
                                printf("Digite o código da estadia para realizar a baixa: ");
                                scanf("%d", &codigo_estadia);
                                getchar(); // Consume newline left by scanf

                                baixa_estadia(f_estadias, f_quartos, f_clientes, codigo_estadia);
                                system("pause");
                                break;
                            }
                    }
                } while (op != 'd');
                break;
            case '5':
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (op != '5');

    // Fecha os arquivos
    fclose(f_clientes);
    fclose(f_funcionarios);
    fclose(f_quartos);
    fclose(f_estadias);

    return 0;
}
