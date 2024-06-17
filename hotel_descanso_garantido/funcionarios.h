#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

#include <stdio.h>

// Estrutura de Funcionario
typedef struct TFuncionario {
    int cod_funcionario;
    char nome_funcionario[50];
    char telefone_funcionario[15];
    char cargo[30];
    float salario;
    int excluido; // 0 - não excluído, 1 - excluído
} Funcionario;

// Funções para gerenciamento de funcionários
FILE* inicializa_sistema_func();
int localiza_funcionario(FILE *f, int cod_funcionario);
int gera_cod_funcionario(FILE *f);
void cadastra_funcionario(FILE *f);
void altera_funcionario(FILE *f);
void exclui_funcionario(FILE *f);
void imprime_funcionarios(FILE *f);
void pesquisa_funcionario_por_nome(FILE *f, char *nome); // Protótipo adicionado
void pesquisa_funcionario_por_codigo(FILE *f, int cod_funcionario); // Protótipo adicionado

#endif // FUNCIONARIOS_H
