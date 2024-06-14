#include "pesquisa_funcionario.h"
#include "funcionario.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool is_number(const char *str) {
		for (int i = 0; str[i] != '\0'; i++) {
				if (!isdigit(str[i])) {
						return false;
				}
		}
		return true;
}

void pesquisar_funcionario(const char *entrada) {
		if (is_number(entrada)) {
				int codigo = atoi(entrada);
				for (int i = 0; i < funcionario_count; i++) {
						if (funcionario[i].codigo == codigo) {
								printf("Funcionário encontrado:\n");
								printf("Código: %d\n", funcionarios[i].codigo);
								printf("Nome: %s\n", funcionarios[i].nome);
								printf("CPF: %s\n", funcionarios[i].cpf);
								printf("Cargo: %s\n", funcionarios[i].cargo);
								return;
						}
				}
				printf("Funcionário com código %d não encontrado.\n", codigo);
		} else {
				for (int i = 0; i < funcionario_count; i++) {
						if (strcmp(funcionarios[i].nome, entrada) == 0) {
								printf("Funcionário encontrado:\n");
								printf("Código: %d\n", funcionarios[i].codigo);
								printf("Nome: %s\n", funcionarios[i].nome);
								printf("CPF: %s\n", funcionarios[i].cpf);
								printf("Cargo: %s\n", funcionarios[i].cargo);
								return;
						}
				}
				printf("Funcionário com nome %s não encontrado.\n", entrada);
		}
}
