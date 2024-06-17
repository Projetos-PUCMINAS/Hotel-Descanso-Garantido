#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FUNCIONARIOS 100

typedef struct {
int cod_funcionario;
char nome_funcionario[100];
char telefone_funcionario[15];
char cargo[50];
double salario;
} Funcionario;

extern Funcionario funcionarios[MAX_FUNCIONARIOS];
extern int qtd_funcionaros;

void CarregarFuncionarios();
void SalvarFuncionarios();
void CadastrarFuncionario();
void BuscarFuncionarioCodigo(char* termo_busca);
void MostrarTodosFuncionarios();

#endif // FUNCIONARIO_H