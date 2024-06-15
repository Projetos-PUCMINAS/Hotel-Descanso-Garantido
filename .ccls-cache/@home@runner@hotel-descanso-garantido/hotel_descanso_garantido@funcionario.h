#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FUNCIONARIOS 100

typedef struct {
		int codigo;
		char nome[100];
		char telefone[15];
		char cargo[50];
		double salario;
} Funcionario;

extern Funcionario funcionarios[MAX_FUNCIONARIOS];
extern int funcionario_count;

void carregar_funcionarios();
void salvar_funcionarios();
void cadastrar_funcionario();
void buscar_funcionario_por_codigo(char* termo_busca);

#endif // FUNCIONARIO_H
