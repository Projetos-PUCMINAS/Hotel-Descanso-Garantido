#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#define MAX_FUNCIONARIOS 100

typedef struct {
		int codigo;
		char nome[100];
		char cpf[12];
		char cargo[50];
} Funcionario;

extern Funcionario funcionarios[MAX_FUNCIONARIOS];
extern int funcionario_count;

void carregar_funcionarios();
void salvar_funcionarios();
void cadastrar_funcionario();

#endif
