#include "funcionario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Funcionario funcionarios[MAX_FUNCIONARIOS];
int funcionario_count = 0;

void carregar_funcionarios() {
		FILE *file = fopen("funcionarios.dat", "rb");
		if (file != NULL) {
				fread(&funcionario_count, sizeof(int), 1, file);
				fread(funcionarios, sizeof(Funcionario), funcionario_count, file);
				fclose(file);
		}
}

void salvar_funcionarios() {
		FILE *file = fopen("funcionarios.dat", "wb");
		if (file != NULL) {
				fwrite(&funcionario_count, sizeof(int), 1, file);
				fwrite(funcionarios, sizeof(Funcionario), funcionario_count, file);
				fclose(file);
		}
}

void cadastrar_funcionario() {
		Funcionario novo_funcionario;
		novo_funcionario.codigo = funcionario_count + 1;
		printf("Digite o nome do funcionário: ");
		scanf("%s", novo_funcionario.nome);
		printf("Digite o CPF do funcionário: ");
		scanf("%s", novo_funcionario.cpf);
		printf("Digite o cargo do funcionário: ");
		scanf("%s", novo_funcionario.cargo);

		funcionarios[funcionario_count++] = novo_funcionario;
		salvar_funcionarios();
		printf("Funcionário cadastrado com sucesso!\n");
}
