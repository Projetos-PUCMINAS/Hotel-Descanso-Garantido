#include "cliente.h"
#include "estadia.h" 
#include "util.h" 

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
		if (cliente_count >= MAX_CLIENTES) {
				printf("Erro: Número máximo de clientes atingido.\n");
				return;
		}

		Cliente novo_cliente;

		limpar_buffer(); 
		printf("Digite o nome do cliente: ");
		fgets(novo_cliente.nome, sizeof(novo_cliente.nome), stdin);
		novo_cliente.nome[strcspn(novo_cliente.nome, "\n")] = '\0'; 

		limpar_buffer();
		printf("Digite o endereço do cliente (Cidade-estado,Bairro,Rua-nº): ");
		fgets(novo_cliente.endereco, sizeof(novo_cliente.endereco), stdin);
		novo_cliente.endereco[strcspn(novo_cliente.endereco, "\n")] = '\0'; 

		limpar_buffer();
		printf("Digite o telefone do cliente (DD numero): ");
		fgets(novo_cliente.telefone, sizeof(novo_cliente.telefone), stdin);
		novo_cliente.telefone[strcspn(novo_cliente.telefone, "\n")] = '\0'; 


		bool codigo_unico;
		do {
				codigo_unico = true;
				novo_cliente.codigo = rand() % 1000 + 1;
				for (int i = 0; i < cliente_count; i++) {
						if (clientes[i].codigo == novo_cliente.codigo) {
								codigo_unico = false;
								break;
						}
				}
		} while (!codigo_unico);

		novo_cliente.pontos_fidelidade = 0;

		clientes[cliente_count] = novo_cliente;
		cliente_count++;
		salvar_clientes();
		printf("Cliente cadastrado com sucesso! Código: %d\n", novo_cliente.codigo);
}

void buscar_cliente_por_codigo(char* termo_busca) {
		int codigo_busca;
		bool encontrado = false;

	
		if (sscanf(termo_busca, "%d", &codigo_busca) == 1) {
				for (int i = 0; i < cliente_count; i++) {
						if (clientes[i].codigo == codigo_busca) {
								printf("Código: %d\n", clientes[i].codigo);
								printf("Nome: %s\n", clientes[i].nome);
								printf("Endereço: %s\n", clientes[i].endereco);
								printf("Telefone: %s\n", clientes[i].telefone);
								printf("Pontos de Fidelidade: %d\n", clientes[i].pontos_fidelidade);
								encontrado = true;
								break;
						}
				}
		}

		if (!encontrado) {
				printf("Cliente não encontrado.\n");
		}
}

int calcular_pontos_fidelidade(int codigo_cliente) {
		int pontos = 0;
		carregar_estadias();
		for (int i = 0; i < estadia_count; i++) {
				if (estadias[i].codigo_cliente == codigo_cliente) {
						pontos += estadias[i].quantidade_diarias * 10;
				}
		}

		return pontos;
}



void mostrar_todos_clientes() {
		if (cliente_count == 0) {
				printf("Nenhum cliente cadastrado.\n");
				return;
		}

		printf("Lista de Clientes:\n");
		for (int i = 0; i < cliente_count; i++) {
				printf("\nCliente %d:\n", i + 1);
				printf("Código: %d\n", clientes[i].codigo);
				printf("Nome: %s\n", clientes[i].nome);
				printf("Endereço: %s\n", clientes[i].endereco);
				printf("Telefone: %s\n", clientes[i].telefone);
				printf("Pontos de Fidelidade: %d\n", clientes[i].pontos_fidelidade);
		}
}
