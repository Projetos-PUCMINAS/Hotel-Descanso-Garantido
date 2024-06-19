#include "funcionarios.h"
#include <stdlib.h>
#include <string.h>
#include <locale.h>
/*Bem-vindo ao sistema do Hotel Descanso Garantido! Este projeto foi desenvolvido com dedicação por Gabriela, Luisa e Marcos, alunos do 1º período do curso de Engenharia de Software. Aproveite a sua estadia*/

FILE* InicializarSistemaFuncionarios() {
    FILE *f;
    setlocale(LC_ALL, "portuguese");

    if ((f = fopen("funcionarios.dat", "r+b")) == NULL) {
        printf("Arquivo de funcionairos não existia ... criando arquivo!\n");
        if ((f = fopen("funcionarios.dat", "w+b")) == NULL) {
            printf("Erro na criação do arquivo!\n");
            exit(1);
        }
    }
    return f;
}



int LocalizarFuncionario(FILE *f, int cod_funcionario) {
    int posicao = -1, achou = 0;
    Funcionario func;
    fseek(f, 0, SEEK_SET);
    fread(&func, sizeof(func), 1, f);
    while (!feof(f) && !achou) {
        posicao++;
        if (func.cod_funcionario == cod_funcionario && func.excluido == 0) {
            achou = 1;
        }
        fread(&func, sizeof(func), 1, f);
    }
    return achou ? posicao : -1;
}



int GeradorCodFuncionario(FILE *f) {
    Funcionario func;
    int max_cod = 0;
    fseek(f, 0, SEEK_SET);
    fread(&func, sizeof(func), 1, f);
    while (!feof(f)) {
        if (func.cod_funcionario > max_cod) {
            max_cod = func.cod_funcionario;
        }
        fread(&func, sizeof(func), 1, f);
    }
    return max_cod + 1;
}



void CadastrarFuncionario(FILE *f) {
    Funcionario func;
    int posicao;

    func.cod_funcionario = GeradorCodFuncionario(f);
    printf("Código gerado automaticamente: %d\n", func.cod_funcionario);
    printf("Digite o nome do funcionário: ");
    fflush(stdin);
    fgets(func.nome_funcionario, sizeof(func.nome_funcionario), stdin);
    func.nome_funcionario[strcspn(func.nome_funcionario, "\n")] = '\0'; 
    printf("Digite o telefone do funcionário: ");
    fflush(stdin);
    fgets(func.telefone_funcionario, sizeof(func.telefone_funcionario), stdin);
    func.telefone_funcionario[strcspn(func.telefone_funcionario, "\n")] = '\0'; 
    printf("Digite o cargo do funcionário: ");
    fflush(stdin);
    fgets(func.cargo, sizeof(func.cargo), stdin);
    func.cargo[strcspn(func.cargo, "\n")] = '\0'; 
    printf("Digite o salário do funcionário: ");
    scanf("%f", &func.salario);
    func.excluido = 0;

    posicao = LocalizarFuncionario(f, func.cod_funcionario);
    if (posicao == -1) {
        fseek(f, 0, SEEK_END);
        fwrite(&func, sizeof(func), 1, f);
        fflush(f);
        printf("Funcionário cadastrado com sucesso!\n");
    } else {
        printf("Erro: Funcionário com código %d já existe!\n", func.cod_funcionario);
    }
}



void AlterarFuncionario(FILE *f) {
    int cod_funcionario, posicao;
    Funcionario func;

    printf("Digite o código do funcionário para alterar: ");
    if (scanf("%d", &cod_funcionario) != 1) {
        printf("Entrada inválida.\n");
        return;
    }
    getchar(); 

    posicao = LocalizarFuncionario(f, cod_funcionario);
    if (posicao != -1) {
        fseek(f, sizeof(func) * posicao, SEEK_SET);
        fread(&func, sizeof(func), 1, f);

        printf("Código atual: %d\n", func.cod_funcionario);
        printf("Nome atual: %s\n", func.nome_funcionario);
        printf("Telefone atual: %s\n", func.telefone_funcionario);
        printf("Cargo atual: %s\n", func.cargo);
        printf("Salário atual: %.2f\n", func.salario);

        printf("Novo nome: ");
        if (fgets(func.nome_funcionario, sizeof(func.nome_funcionario), stdin)) {
            func.nome_funcionario[strcspn(func.nome_funcionario, "\n")] = '\0'; 
        }

        printf("Novo telefone: ");
        if (fgets(func.telefone_funcionario, sizeof(func.telefone_funcionario), stdin)) {
            func.telefone_funcionario[strcspn(func.telefone_funcionario, "\n")] = '\0'; 
        }

        printf("Novo cargo: ");
        if (fgets(func.cargo, sizeof(func.cargo), stdin)) {
            func.cargo[strcspn(func.cargo, "\n")] = '\0';
        }

        printf("Novo salário: ");
        if (scanf("%f", &func.salario) != 1) {
            printf("Entrada inválida.\n");
            return;
        }

        fseek(f, sizeof(func) * posicao, SEEK_SET);
        fwrite(&func, sizeof(func), 1, f);
        fflush(f);

        printf("Funcionário alterado com sucesso!\n");
    } else {
        printf("Funcionário com código %d não encontrado!\n", cod_funcionario);
    }
}



void ExcluirFuncionario(FILE *f) {
    int cod_funcionario, posicao;
    Funcionario func;
    printf("Digite o código do funcionário para excluir: ");
    scanf("%d", &cod_funcionario);
    getchar(); 
    posicao = LocalizarFuncionario(f, cod_funcionario);
    if (posicao != -1) {
        fseek(f, sizeof(func) * posicao, SEEK_SET);
        fread(&func, sizeof(func), 1, f);
        func.excluido = 1;
        fseek(f, sizeof(func) * posicao, SEEK_SET);
        fwrite(&func, sizeof(func), 1, f);
        fflush(f);
        printf("Funcionário com código %d foi excluído logicamente.\n", cod_funcionario);
    } else {
        printf("Funcionário com código %d não encontrado!\n", cod_funcionario);
    }
}



void ImprimirFuncionarios(FILE *f) {
    Funcionario func;
    fseek(f, 0, SEEK_SET);
    fread(&func, sizeof(func), 1, f);
    while (!feof(f)) {
        if (!func.excluido) {
            printf("Código: %d\nNome: %s\nTelefone: %s\nCargo: %s\nSalário: %.2f\n", func.cod_funcionario, func.nome_funcionario, func.telefone_funcionario, func.cargo, func.salario);
            printf("-----------------------\n");
        }
        fread(&func, sizeof(func), 1, f);
    }
}



void PesquisarFuncionarioPorNome(FILE *f, char *nome) {
    Funcionario func;
    int encontrou = 0;

    fseek(f, 0, SEEK_SET); 
    fread(&func, sizeof(func), 1, f); 

    while (!feof(f)) {
        if (!func.excluido && strstr(func.nome_funcionario, nome) != NULL) {
            printf("Código: %d\nNome: %s\nTelefone: %s\nCargo: %s\nSalário: %.2f\n", 
                   func.cod_funcionario, func.nome_funcionario, func.telefone_funcionario, func.cargo, func.salario);
            printf("-----------------------\n");
            encontrou = 1;
        }
        fread(&func, sizeof(func), 1, f); 
    }

    if (!encontrou) {
        printf("Nenhum funcionário encontrado com o nome '%s'.\n", nome);
    }
}



void PesquisarFuncionarioPorCodigo(FILE *f, int cod_funcionario) {
    Funcionario func;
    int posicao = LocalizarFuncionario(f, cod_funcionario);

    if (posicao != -1) {
        fseek(f, sizeof(func) * posicao, SEEK_SET);
        fread(&func, sizeof(func), 1, f);

        if (!func.excluido) {
            printf("Código: %d\nNome: %s\nTelefone: %s\nCargo: %s\nSalário: %.2f\n", 
                    func.cod_funcionario, func.nome_funcionario, 
                    func.telefone_funcionario, func.cargo, func.salario);
        } else {
            printf("Funcionário com código %d está excluído.\n", cod_funcionario);
        }
    } else {
        printf("Funcionário com código %d não encontrado!\n", cod_funcionario);
    }
    printf("-----------------------\n");
    while (getchar() != '\n'); 
    getchar(); 
}
