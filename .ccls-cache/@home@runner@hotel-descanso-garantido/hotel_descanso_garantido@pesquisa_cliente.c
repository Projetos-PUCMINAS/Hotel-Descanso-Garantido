#include "pesquisa_cliente.h"
#include "cliente.h"
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

void pesquisar_cliente(const char *entrada) {
		if (is_number(entrada)) {
				int codigo = atoi(entrada);
				for (int i = 0; i < cliente_count; i++) {
						if (clientes[i].codigo == codigo) {
								printf("Cliente encontrado:\n");
								printf("Código: %d\n", clientes[i].codigo);
								printf("Nome: %s\n", clientes[i].nome);
								return;
						}
				}
				printf("Cliente com código %d não encontrado.\n", codigo);
		} else {
				for (int i = 0; i < cliente_count; i++) {
						if (strcmp(clientes[i].nome, entrada) == 0) {
								printf("Cliente encontrado:\n");
								printf("Código: %d\n", clientes[i].codigo);
								printf("Nome: %s\n", clientes[i].nome);
								printf("CPF: %s\n", clientes[i].cpf);
								return;
						}
				}
				printf("Cliente com nome %s não encontrado.\n", entrada);
		}
}
