#include "clientes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estadias.h"

// Função para inicializar o sistema de clientes
FILE* inicializa_sistema() {
		FILE *f;
		if ((f = fopen("clientes.dat", "r+b")) == NULL) {
				printf("Arquivo não existia... criando arquivo!\n");
				if ((f = fopen("clientes.dat", "w+b")) == NULL) {
						printf("Erro na criação do arquivo!\n");
						exit(1);
				}
		}
		return f;
}

// Função para localizar um cliente pelo código
int localiza_cliente(FILE *f, int cod_cliente) {
		int posicao = -1;
		Cliente c;
		fseek(f, 0, SEEK_SET);
		while (fread(&c, sizeof(c), 1, f) == 1) {
				posicao++;
				if (c.cod_cliente == cod_cliente && c.excluido == 0) {
						return posicao;
				}
		}
		return -1;
}

// Função para gerar um código único de cliente
int gera_cod_cliente(FILE *f) {
		Cliente c;
		int max_cod = 0;
		fseek(f, 0, SEEK_SET);
		while (fread(&c, sizeof(c), 1, f) == 1) {
				if (c.cod_cliente > max_cod) {
						max_cod = c.cod_cliente;
				}
		}
		return max_cod + 1;
}

// Função para cadastrar um cliente
void cadastra_cliente(FILE *f) {
		Cliente c;
		int posicao;

		c.cod_cliente = gera_cod_cliente(f);
		printf("Código gerado automaticamente: %d\n", c.cod_cliente);

		printf("Digite o nome do cliente: ");
		fflush(stdin);
		fgets(c.nome_cliente, sizeof(c.nome_cliente), stdin);
		c.nome_cliente[strcspn(c.nome_cliente, "\n")] = '\0'; 

		printf("Digite o endereço do cliente: ");
		fflush(stdin);
		fgets(c.endereco, sizeof(c.endereco), stdin);
		c.endereco[strcspn(c.endereco, "\n")] = '\0'; 

		printf("Digite o telefone do cliente: ");
		fflush(stdin);
		fgets(c.telefone_cliente, sizeof(c.telefone_cliente), stdin);
		c.telefone_cliente[strcspn(c.telefone_cliente, "\n")] = '\0'; 

		c.excluido = 0;

		posicao = localiza_cliente(f, c.cod_cliente);
		if (posicao == -1) {
				fseek(f, 0, SEEK_END);
				fwrite(&c, sizeof(c), 1, f);
				fflush(f);
				printf("Cliente cadastrado com sucesso!\n");
		} else {
				printf("Erro: Cliente com código %d já existe!\n", c.cod_cliente);
		}

		while (getchar() != '\n'); // Limpa o buffer de entrada
}

// Função para alterar um cliente
void altera_cliente(FILE *f) {
		int cod_cliente, posicao;
		Cliente c;
		printf("Digite o código do cliente para alterar: ");
		scanf("%d", &cod_cliente);
		getchar(); // Consume newline left by scanf

		posicao = localiza_cliente(f, cod_cliente);
		if (posicao != -1) {
				fseek(f, sizeof(c) * posicao, SEEK_SET);
				if (fread(&c, sizeof(c), 1, f) != 1) {
						printf("Erro ao ler o cliente!\n");
						return;
				}

				printf("Código atual: %d\nNome atual: %s\n", c.cod_cliente, c.nome_cliente);
				printf("Endereço atual: %s\nTelefone atual: %s\n", c.endereco, c.telefone_cliente);

				printf("Novo nome: ");
				fflush(stdin);
				fgets(c.nome_cliente, sizeof(c.nome_cliente), stdin);
				c.nome_cliente[strcspn(c.nome_cliente, "\n")] = '\0'; 

				printf("Novo endereço: ");
				fflush(stdin);
				fgets(c.endereco, sizeof(c.endereco), stdin);
				c.endereco[strcspn(c.endereco, "\n")] = '\0'; 

				printf("Novo telefone: ");
				fflush(stdin);
				fgets(c.telefone_cliente, sizeof(c.telefone_cliente), stdin);
				c.telefone_cliente[strcspn(c.telefone_cliente, "\n")] = '\0'; 

				fseek(f, sizeof(c) * posicao, SEEK_SET);
				fwrite(&c, sizeof(c), 1, f);
				fflush(f);
				printf("Cliente alterado com sucesso!\n");
		} else {
				printf("Cliente com código %d não encontrado!\n", cod_cliente);
		}

		while (getchar() != '\n'); // Limpa o buffer de entrada
}

// Função para excluir logicamente um cliente
void exclui_cliente(FILE *f) {
		int cod_cliente, posicao;
		Cliente c;
		printf("Digite o código do cliente para excluir: ");
		scanf("%d", &cod_cliente);
		getchar(); // Consume newline left by scanf

		posicao = localiza_cliente(f, cod_cliente);
		if (posicao != -1) {
				fseek(f, sizeof(c) * posicao, SEEK_SET);
				if (fread(&c, sizeof(c), 1, f) != 1) {
						printf("Erro ao ler o cliente!\n");
						return;
				}

				c.excluido = 1;
				fseek(f, sizeof(c) * posicao, SEEK_SET);
				fwrite(&c, sizeof(c), 1, f);
				fflush(f);
				printf("Cliente com código %d foi excluído logicamente.\n", cod_cliente);
		} else {
				printf("Cliente com código %d não encontrado!\n", cod_cliente);
		}

		while (getchar() != '\n'); // Limpa o buffer de entrada
}

int calcula_pontos_fidelidade(FILE *f_estadias, int cod_cliente) {
		Estadia estadia;
		int pontos_fidelidade = 0;

		fseek(f_estadias, 0, SEEK_SET);
		while (fread(&estadia, sizeof(estadia), 1, f_estadias) == 1) {
				if (estadia.cod_cliente == cod_cliente) {
						pontos_fidelidade += 10 * estadia.quantidade_diarias;
				}
		}

		return pontos_fidelidade;
}
// Função para imprimir todos os clientes
// Função para imprimir todos os clientes
void imprime_clientes(FILE *f, FILE *f_estadias) {
		Cliente c;
		fseek(f, 0, SEEK_SET); // Posiciona o ponteiro no início do arquivo
		while (fread(&c, sizeof(c), 1, f) == 1) {
				if (!c.excluido) {
						printf("Código: %d\n", c.cod_cliente);
						printf("Nome: %s\n", c.nome_cliente);
						printf("Endereço: %s\n", c.endereco);
						printf("Telefone: %s\n", c.telefone_cliente);

						// Calcula e imprime os pontos de fidelidade
						int pontos_fidelidade = calcula_pontos_fidelidade(f_estadias, c.cod_cliente);
						printf("Pontos de fidelidade: %d\n", pontos_fidelidade);

						printf("-----------------------\n");
				}
		}

		printf("Pressione Enter para continuar...");
		while (getchar() != '\n'); // Limpa o buffer de entrada
		getchar(); // Espera o usuário pressionar Enter
		while (getchar() != '\n'); // Limpa o buffer de entrada
}


// Função para pesquisar cliente pelo nome
void pesquisa_cliente_por_nome(FILE *f, char *nome) {
		Cliente c;
		int encontrou = 0;
		fseek(f, 0, SEEK_SET);
		while (fread(&c, sizeof(c), 1, f) == 1) {
				if (!c.excluido && strstr(c.nome_cliente, nome) != NULL) {
						printf("Código: %d\nNome: %s\nEndereço: %s\nTelefone: %s\n", c.cod_cliente, c.nome_cliente, c.endereco, c.telefone_cliente);
						printf("-----------------------\n");
						encontrou = 1;
				}
		}
		if (!encontrou) {
				printf("Nenhum cliente encontrado com o nome '%s'.\n", nome);
		}

		printf("Pressione Enter para continuar...");
		while (getchar() != '\n');
	getchar();
	 while (getchar() != '\n'); // Limpa o buffer de entrada
	}


// Função para pesquisar cliente pelo código
void pesquisa_cliente_por_codigo(FILE *f, int cod_cliente) {
		Cliente c;
		int posicao = localiza_cliente(f, cod_cliente);
		if (posicao != -1) {
				fseek(f, sizeof(c) * posicao, SEEK_SET);
				fread(&c, sizeof(c), 1, f);
				if (!c.excluido) {
						printf("Código: %d\nNome: %s\nEndereço: %s\nTelefone: %s\n", c.cod_cliente, c.nome_cliente, c.endereco, c.telefone_cliente);
				} else {
						printf("Cliente com código %d foi excluído logicamente.\n", cod_cliente);
				}
		} else {
				printf("Cliente com código %d não encontrado!\n", cod_cliente);
		}
	printf("Pressione Enter para continuar...");
	getchar(); 
}
