#include "clientes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estadias.h"


FILE* InicializarSistemaClientes() {
		FILE *f;
		if ((f = fopen("clientes.dat", "r+b")) == NULL) {
				printf("Arquivo de clientes não existia... criando arquivo!\n");
				if ((f = fopen("clientes.dat", "w+b")) == NULL) {
						printf("Erro na criação do arquivo!\n");
						exit(1);
				}
		}
		return f;
}



int LocalizarCliente(FILE *f, int cod_cliente) {
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



int GeradorCodCliente(FILE *f) {
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



void CadastrarCliente(FILE *f) {
		Cliente c;
		int posicao;

		c.cod_cliente = GeradorCodCliente(f);
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

		posicao = LocalizarCliente(f, c.cod_cliente);
		if (posicao == -1) {
				fseek(f, 0, SEEK_END);
				fwrite(&c, sizeof(c), 1, f);
				fflush(f);
				printf("Cliente cadastrado com sucesso!\n");
		} else {
				printf("Erro: Cliente com código %d já existe!\n", c.cod_cliente);
		}

		while (getchar() != '\n'); 
}



void AlterarCliente(FILE *f) {
		int cod_cliente, posicao;
		Cliente c;
		printf("Digite o código do cliente para alterar: ");
		scanf("%d", &cod_cliente);
		getchar(); 

		posicao = LocalizarCliente(f, cod_cliente);
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



void ExcluirCliente(FILE *f) {
		int cod_cliente, posicao;
		Cliente c;
		printf("Digite o código do cliente para excluir: ");
		scanf("%d", &cod_cliente);
		getchar(); 

		posicao = LocalizarCliente(f, cod_cliente);
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

		while (getchar() != '\n'); 
}



int CalcularPontosFidelidade(FILE *f_estadias, int cod_cliente) {
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



void ImprimirClientes(FILE *f, FILE *f_estadias) {
		Cliente c;
		fseek(f, 0, SEEK_SET); 
		while (fread(&c, sizeof(c), 1, f) == 1) {
				if (!c.excluido) {
						printf("Código: %d\n", c.cod_cliente);
						printf("Nome: %s\n", c.nome_cliente);
						printf("Endereço: %s\n", c.endereco);
						printf("Telefone: %s\n", c.telefone_cliente);

						int pontos_fidelidade = CalcularPontosFidelidade(f_estadias, c.cod_cliente);
						printf("Pontos de fidelidade: %d\n", pontos_fidelidade);

						printf("-----------------------\n");
				}
		}
		while (getchar() != '\n'); 
		getchar(); 
		while (getchar() != '\n'); 
}



void PesquisarClientePorNome(FILE *f, char *nome) {
		Cliente c;
		int encontrou = 0;
		fseek(f, 0, SEEK_SET);
		while (fread(&c, sizeof(c), 1, f) == 1) {
				if (!c.excluido && strstr(c.nome_cliente, nome) != NULL) {
					printf("Código: %d\nNome: %s\nEndereço: %s\nTelefone: %s\nPontos de Fidelidade: %d\n", c.cod_cliente, c.nome_cliente, c.endereco, c.telefone_cliente,c.pontos_fidelidade);
						printf("-----------------------\n");
						encontrou = 1;
				}
		}
		if (!encontrou) {
				printf("Nenhum cliente encontrado com o nome '%s'.\n", nome);
		}
		while (getchar() != '\n');
	getchar();
	 while (getchar() != '\n'); 
	}



void PesquisarClientePorCodigo(FILE *f, int cod_cliente) {
		Cliente c;
		int posicao = LocalizarCliente(f, cod_cliente);
		if (posicao != -1) {
				fseek(f, sizeof(c) * posicao, SEEK_SET);
				fread(&c, sizeof(c), 1, f);
				if (!c.excluido) {
						printf("Código: %d\nNome: %s\nEndereço: %s\nTelefone: %s\nPontos de Fidelidade: %d\n", c.cod_cliente, c.nome_cliente, c.endereco, c.telefone_cliente,c.pontos_fidelidade);
				} else {
						printf("Cliente com código %d foi excluído logicamente.\n", cod_cliente);
				}
		} else {
				printf("Cliente com código %d não encontrado!\n", cod_cliente);
		}
	printf("-----------------------\n");
	getchar(); 
}
