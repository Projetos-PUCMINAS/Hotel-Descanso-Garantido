#include "funcionarios.h"
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Função para inicializar o sistema de funcionários
FILE* inicializa_sistema_func() {
    FILE *f;
    setlocale(LC_ALL, "portuguese");

    if ((f = fopen("funcionarios.dat", "r+b")) == NULL) {
        printf("Arquivo não existia ... criando arquivo!\n");
        if ((f = fopen("funcionarios.dat", "w+b")) == NULL) {
            printf("Erro na criação do arquivo!\n");
            exit(1);
        }
        system("pause");
    }

    return f;
}

// Função para localizar um funcionário pelo código
int localiza_funcionario(FILE *f, int cod_funcionario) {
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

// Função para gerar um código único de funcionário
int gera_cod_funcionario(FILE *f) {
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

// Função para cadastrar um funcionário
void cadastra_funcionario(FILE *f) {
    Funcionario func;
    int posicao;

    func.cod_funcionario = gera_cod_funcionario(f);
    printf("Código gerado automaticamente: %d\n", func.cod_funcionario);
    printf("Digite o nome do funcionário: ");
    fflush(stdin);
    fgets(func.nome_funcionario, sizeof(func.nome_funcionario), stdin);
    func.nome_funcionario[strcspn(func.nome_funcionario, "\n")] = '\0'; // Remove newline
    printf("Digite o telefone do funcionário: ");
    fflush(stdin);
    fgets(func.telefone_funcionario, sizeof(func.telefone_funcionario), stdin);
    func.telefone_funcionario[strcspn(func.telefone_funcionario, "\n")] = '\0'; // Remove newline
    printf("Digite o cargo do funcionário: ");
    fflush(stdin);
    fgets(func.cargo, sizeof(func.cargo), stdin);
    func.cargo[strcspn(func.cargo, "\n")] = '\0'; // Remove newline
    printf("Digite o salário do funcionário: ");
    scanf("%f", &func.salario);
    func.excluido = 0;

    posicao = localiza_funcionario(f, func.cod_funcionario);
    if (posicao == -1) {
        fseek(f, 0, SEEK_END);
        fwrite(&func, sizeof(func), 1, f);
        fflush(f);
        printf("Funcionário cadastrado com sucesso!\n");
    } else {
        printf("Erro: Funcionário com código %d já existe!\n", func.cod_funcionario);
    }
}

// Função para alterar um funcionário
void altera_funcionario(FILE *f) {
    int cod_funcionario, posicao;
    Funcionario func;
    printf("Digite o código do funcionário para alterar: ");
    scanf("%d", &cod_funcionario);
    getchar(); // Consume newline left by scanf
    posicao = localiza_funcionario(f, cod_funcionario);
    if (posicao != -1) {
        fseek(f, sizeof(func) * posicao, SEEK_SET);
        fread(&func, sizeof(func), 1, f);
        printf("Código atual: %d\nNome atual: %s\n", func.cod_funcionario, func.nome_funcionario);
        printf("Telefone atual: %s\nCargo atual: %s\nSalário atual: %.2f\n", func.telefone_funcionario, func.cargo, func.salario);
        printf("Novo nome: ");
        fflush(stdin);
        fgets(func.nome_funcionario, sizeof(func.nome_funcionario), stdin);
        func.nome_funcionario[strcspn(func.nome_funcionario, "\n")] = '\0'; // Remove newline
        printf("Novo telefone: ");
        fflush(stdin);
        fgets(func.telefone_funcionario, sizeof(func.telefone_funcionario), stdin);
        func.telefone_funcionario[strcspn(func.telefone_funcionario, "\n")] = '\0'; // Remove newline
        printf("Novo cargo: ");
        fflush(stdin);
        fgets(func.cargo, sizeof(func.cargo), stdin);
        func.cargo[strcspn(func.cargo, "\n")] = '\0'; // Remove newline
        printf("Novo salário: ");
        scanf("%f", &func.salario);
        fseek(f, sizeof(func) * posicao, SEEK_SET);
        fwrite(&func, sizeof(func), 1, f);
        fflush(f);
    } else {
        printf("Funcionário com código %d não encontrado!\n", cod_funcionario);
    }
}

// Função para excluir logicamente um funcionário
void exclui_funcionario(FILE *f) {
    int cod_funcionario, posicao;
    Funcionario func;
    printf("Digite o código do funcionário para excluir: ");
    scanf("%d", &cod_funcionario);
    getchar(); // Consume newline left by scanf
    posicao = localiza_funcionario(f, cod_funcionario);
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

// Função para imprimir todos os funcionários
void imprime_funcionarios(FILE *f) {
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


// Função para pesquisar funcionário pelo nome
void pesquisa_funcionario_por_nome(FILE *f, char *nome) {
    Funcionario func;
    int encontrou = 0;

    fseek(f, 0, SEEK_SET); // Move para o início do arquivo
    fread(&func, sizeof(func), 1, f); // Lê o primeiro registro

    while (!feof(f)) {
        if (!func.excluido && strstr(func.nome_funcionario, nome) != NULL) {
            printf("Código: %d\nNome: %s\nTelefone: %s\nCargo: %s\nSalário: %.2f\n", 
                   func.cod_funcionario, func.nome_funcionario, func.telefone_funcionario, func.cargo, func.salario);
            printf("-----------------------\n");
            encontrou = 1;
        }
        fread(&func, sizeof(func), 1, f); // Lê o próximo registro
    }

    if (!encontrou) {
        printf("Nenhum funcionário encontrado com o nome '%s'.\n", nome);
    }
}



          // Função para pesquisar funcionário pelo código
          void pesquisa_funcionario_por_codigo(FILE *f, int cod_funcionario) {
          Funcionario func;
          int posicao = localiza_funcionario(f, cod_funcionario);
          if (posicao != -1) {
          fseek(f, sizeof(func) * posicao, SEEK_SET);
          fread(&func, sizeof(func), 1, f);
          if (!func.excluido) {
          printf("Código: %d\nNome: %s\nTelefone: %s\nCargo: %s\nSalário: %.2f\n", func.cod_funcionario, func.nome_funcionario, func.telefone_funcionario, func.cargo, func.salario);
          } else {
          printf("Funcionário com código %d está excluído.\n", cod_funcionario);
          }
          } else {
          printf("Funcionário com código %d não encontrado!\n", cod_funcionario);
          }
          }
