#include "cliente.h"

// Array to store clients
Cliente clientes[MAX_CLIENTES];
int cliente_count = 0;

void carregar_clientes() {
		FILE *file = fopen("clientes.dat", "rb");
		if (file != NULL) {
				fread(&cliente_count, sizeof(int), 1, file);
				fread(clientes, sizeof(Cliente), cliente_count, file);
				fclose(file);
		}
}

void salvar_clientes() {
		FILE *file = fopen("clientes.dat", "wb");
		if (file != NULL) {
				fwrite(&cliente_count, sizeof(int), 1, file);
				fwrite(clientes, sizeof(Cliente), cliente_count, file);
				fclose(file);
		}
}

void cadastrar_cliente() {
		Cliente novo_cliente;
		printf("Digite o nome do cliente: ");
		scanf("%s", novo_cliente.nome);
		printf("Digite o endereço do cliente: ");
		scanf("%s", novo_cliente.endereco);
		printf("Digite o telefone do cliente: ");
		scanf("%s", novo_cliente.telefone);

		// Gerar um código único
		bool codigo_unico = false;
		while (!codigo_unico) {
				novo_cliente.codigo = rand() % 1000 + 1;
				codigo_unico = true;
				for (int i = 0; i < cliente_count; i++) {
						if (clientes[i].codigo == novo_cliente.codigo) {
								codigo_unico = false;
								break;
						}
				}
		}

		// Add new client to array
		clientes[cliente_count++] = novo_cliente;
		salvar_clientes();
		printf("Cliente cadastrado com sucesso! Código: %d\n", novo_cliente.codigo);
}
