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

    f_clientes = InicializarSistemaClientes();
    f_funcionarios = InicializarSistemaFuncionarios();
    f_quartos = InicializarSistemaQuartos();
    f_estadias = InicializarSistemaEstadias();

    do {
        printf("\nEscolha:\n");
        printf("1 - Menu de Clientes\n");
        printf("2 - Menu de Funcionários\n");
        printf("3 - Menu de Quartos\n");
        printf("4 - Menu de Estadias\n");
        printf("5 - Sair do sistema\n");
        op = getchar();
        getchar();
        switch (op) {
            case '1':
            do {
                printf("\nMenu Clientes:\n");
                printf("a - Cadastrar cliente\n");
                printf("b - Alterar cliente\n");
                printf("c - Excluir cliente\n");
                printf("d - Listar todos os clientes\n");
                printf("e - Pesquisar cliente por código\n");
                printf("f - Pesquisar cliente por nome\n");
                printf("g - Voltar ao menu anterior\n");
                op = getchar();
                getchar(); 
                switch (op) {
                    case 'a':
                        CadastrarCliente(f_clientes);
                        break;
                    case 'b':
                        AlterarCliente(f_clientes);
                        break;
                    case 'c':
                        ExcluirCliente(f_clientes);
                        break;
                    case 'd':
                        ImprimirClientes(f_clientes, f_estadias);
                        break;
                    case 'e': {
                        int cod_cliente;
                        printf("Digite o código do cliente para pesquisar: ");
                        scanf("%d", &cod_cliente);
                        getchar(); 

                        PesquisarClientePorCodigo(f_clientes, cod_cliente);
                        break;
                    }
                    case 'f': {
                        char nome[50];
                        printf("Digite o nome do cliente para pesquisar: ");
                        fgets(nome, sizeof(nome), stdin);
                        nome[strcspn(nome, "\n")] = '\0'; 
                        PesquisarClientePorNome(f_clientes, nome);
                        while (getchar() != '\n'); 
                        break;
                    }
                }
            } while (op != 'g');
            break;
            case '2':
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
                    getchar(); 
                    switch (op) {
                        case 'a':
                            CadastrarFuncionario(f_funcionarios);
                            break;
                        case 'b':
                            AlterarFuncionario(f_funcionarios);
                            break;
                        case 'c':
                            ExcluirFuncionario(f_funcionarios);
                            break;
                        case 'd':
                            ImprimirFuncionarios(f_funcionarios);
                            break;
                        case 'e': {
                            int cod;
                            printf("Digite o código do funcionário: ");
                            scanf("%d", &cod);
                            getchar(); 
                            PesquisarFuncionarioPorCodigo(f_funcionarios, cod);
                            break;
                        }
                        case 'f': {
                            char nome[50];
                            printf("Digite o nome do funcionário: ");
                            fgets(nome, sizeof(nome), stdin);
                            nome[strcspn(nome, "\n")] = '\0'; 
                            PesquisarFuncionarioPorNome(f_funcionarios, nome);
                            while (getchar() != '\n'); 
                            break;
                        }
                    }
                } while (op != 'g');
                break;
            case '3':
                do {
                    printf("\nMenu Quartos:\n");
                    printf("a - Cadastrar quarto\n");
                    printf("b - Alterar quarto\n");
                    printf("c - Excluir quarto\n");
                    printf("d - Listar todos os quartos\n");
                    printf("e - Voltar ao menu anterior\n");
                    op = getchar();
                    getchar(); 
                    switch (op) {
                        case 'a':
                            CadastrarQuarto(f_quartos);
                            break;
                        case 'b':
                            AlterarQuarto(f_quartos);
                            break;
                        case 'c':
                            ExcluirQuarto(f_quartos);
                            break;
                        case 'd':
                            ImprimirQuartos(f_quartos);
                            break;
                    }
                } while (op != 'e');
                break;
            case '4':
            do {
                printf("\nMenu Estadias:\n");
                printf("a - Cadastrar estadia\n");
                printf("b - Listar todas as estadias\n");
                printf("c - Baixa de estadia\n");
                printf("d - Pesquisar estadia por código\n");
                printf("e - Voltar ao menu anterior\n");
                op = getchar();
                getchar(); 
                switch (op) {
                    case 'a':
                        CadastrarEstadia(f_estadias, f_clientes, f_quartos);
                        break;
                    case 'b':
                        ImprimirEstadias(f_estadias, f_clientes, f_quartos);
                        break;
                    case 'c':
                        {
                            int codigo_estadia;
                            printf("Digite o código da estadia para realizar a baixa: ");
                            scanf("%d", &codigo_estadia);
                            getchar(); 
                            BaixaEstadia(f_estadias, f_quartos, f_clientes, codigo_estadia);
                            break;
                        }
                    case 'd':
                        {
                            int codigo_estadia;
                            printf("Digite o código da estadia para pesquisar: ");
                            scanf("%d", &codigo_estadia);
                            getchar(); 
                            PesquisarEstadiaPorCodigo(f_estadias, codigo_estadia);
                            break;
                        }
                }
            } while (op != 'e');
            break;

            case '5':
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (op != '5');


    fclose(f_clientes);
    fclose(f_funcionarios);
    fclose(f_quartos);
    fclose(f_estadias);

    return 0;
}