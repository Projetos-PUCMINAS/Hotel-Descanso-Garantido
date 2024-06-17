#include "cliente.h"
#include "estadia.h" 
#include "util.h" 

Cliente clientes[MAX_CLIENTES];
int qtd_clientes = 0;

void CarregarClientes() {
		FILE *file = fopen("clientes.dat", "rb");
		if (file != NULL) {
				fread(&qtd_clientes, sizeof(int), 1, file);
				fread(clientes, sizeof(Cliente), qtd_clientes, file);
				fclose(file);
		}
}

void SalvarClientes() {
		FILE *file = fopen("clientes.dat", "wb");
		if (file != NULL) {
				fwrite(&qtd_clientes, sizeof(int), 1, file);
				fwrite(clientes, sizeof(Cliente), qtd_clientes, file);
				fclose(file);
		}
}

void CadastrarCliente() {
		if (qtd_clientes >= MAX_CLIENTES) {
				printf("Erro: Número máximo de clientes atingido.\n");
				return;
		}

		Cliente novo_cliente;

		limpar_buffer(); 
		printf("Digite o nome do cliente: ");
		fgets(novo_cliente.nome_cliente, sizeof(novo_cliente.nome_cliente), stdin);
		novo_cliente.nome_cliente[strcspn(novo_cliente.nome_cliente, "\n")] = '\0'; 

		limpar_buffer();
		printf("Digite o endereço do cliente (Cidade-estado,Bairro,Rua-nº): ");
		fgets(novo_cliente.endereco_cliente, sizeof(novo_cliente.endereco_cliente), stdin);
		novo_cliente.endereco_cliente[strcspn(novo_cliente.endereco_cliente, "\n")] = '\0'; 

		limpar_buffer();
		printf("Digite o telefone do cliente (DD numero): ");
		fgets(novo_cliente.telefone_cliente, sizeof(novo_cliente.telefone_cliente), stdin);
		novo_cliente.telefone_cliente[strcspn(novo_cliente.telefone_cliente, "\n")] = '\0'; 


		bool codigo_unico;
		do {
				codigo_unico = true;
				novo_cliente.cod_cliente = rand() % 1000 + 1;
				for (int i = 0; i < qtd_clientes; i++) {
						if (clientes[i].cod_cliente == novo_cliente.cod_cliente) {
								codigo_unico = false;
								break;
						}
				}
		} while (!codigo_unico);

		novo_cliente.pontos_fidelidade = 0;

		clientes[qtd_clientes] = novo_cliente;
	  qtd_clientes++;
		SalvarClientes();
		printf("Cliente cadastrado com sucesso! Código: %d\n", novo_cliente.cod_cliente);
}

void BuscarClienteCodigo(char* termo_busca) {
		int codigo_busca;
		bool encontrado = false;

	
		if (sscanf(termo_busca, "%d", &codigo_busca) == 1) {
				for (int i = 0; i < qtd_clientes; i++) {
						if (clientes[i].cod_cliente == codigo_busca) {
								printf("Código: %d\n", clientes[i].cod_cliente);
								printf("Nome: %s\n", clientes[i].nome_cliente);
								printf("Endereço: %s\n", clientes[i].endereco_cliente);
								printf("Telefone: %s\n", clientes[i].telefone_cliente);
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
		CarregarEstadias();
		for (int i = 0; i < qtd_estadias; i++) {
				if (estadias[i].codigo_cliente == codigo_cliente) {
						pontos += estadias[i].qtd_diarias * 10;
				}
		}

		return pontos;
}



void MostrarTodosClientes() {
		if (qtd_clientes == 0) {
				printf("Nenhum cliente cadastrado.\n");
				return;
		}

		printf("Lista de Clientes:\n");
		for (int i = 0; i < qtd_clientes; i++) {
				printf("\nCliente %d:\n", i + 1);
				printf("Código: %d\n", clientes[i].cod_cliente);
				printf("Nome: %s\n", clientes[i].nome_cliente);
				printf("Endereço: %s\n", clientes[i].endereco_cliente);
				printf("Telefone: %s\n", clientes[i].telefone_cliente);
				printf("Pontos de Fidelidade: %d\n", clientes[i].pontos_fidelidade);
		}
}
