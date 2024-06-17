#include "quartos.h"
#include <stdlib.h>
#include <string.h>

FILE* inicializa_sistema_quartos() {
		FILE *f;
		f = fopen("quartos.dat", "r+b");
		if (f == NULL) {
				printf("Arquivo de quartos não existia... criando arquivo!\n");
				f = fopen("quartos.dat", "w+b");
				if (f == NULL) {
						printf("Erro na criação do arquivo de quartos!\n");
						exit(1);
				}
		}
		return f;
}

void cadastra_quarto(FILE *f) {
		Quarto quarto;
		int num_quarto;

		num_quarto = gera_num_quarto(f);

		quarto.numero = num_quarto;

		printf("Digite a quantidade de hóspedes: ");
		scanf("%d", &quarto.quantidade_hospedes);

		printf("Digite o valor da diária: ");
		scanf("%f", &quarto.valor_diaria);

		// Por padrão, ao cadastrar um quarto, ele está desocupado
		strcpy(quarto.status, "desocupado");

		fseek(f, 0, SEEK_END);
		fwrite(&quarto, sizeof(Quarto), 1, f);
		fflush(f);

		printf("Quarto cadastrado com sucesso!\n");
}

void altera_quarto(FILE *f) {
		int numero, posicao;
		Quarto quarto;

		printf("Digite o número do quarto para alterar: ");
		scanf("%d", &numero);

		posicao = localiza_quarto(f, numero);
		if (posicao != -1) {
				fseek(f, sizeof(Quarto) * posicao, SEEK_SET);
				fread(&quarto, sizeof(Quarto), 1, f);

				printf("Quantidade de hóspedes atual: %d\n", quarto.quantidade_hospedes);
				printf("Valor da diária atual: %.2f\n", quarto.valor_diaria);
				printf("Status atual do quarto: %s\n", quarto.status);

				printf("Nova quantidade de hóspedes: ");
				scanf("%d", &quarto.quantidade_hospedes);

				printf("Novo valor da diária: ");
				scanf("%f", &quarto.valor_diaria);

				printf("Novo status do quarto ('desocupado' ou 'ocupado'): ");
				scanf("%s", quarto.status);

				fseek(f, sizeof(Quarto) * posicao, SEEK_SET);
				fwrite(&quarto, sizeof(Quarto), 1, f);
				fflush(f);
				printf("Quarto alterado com sucesso!\n");
		} else {
				printf("Quarto com número %d não encontrado!\n", numero);
		}
}

void exclui_quarto(FILE *f) {
		int numero, posicao;
		Quarto quarto;

		printf("Digite o número do quarto para excluir: ");
		scanf("%d", &numero);

		posicao = localiza_quarto(f, numero);
		if (posicao != -1) {
				fseek(f, sizeof(Quarto) * posicao, SEEK_SET);
				fread(&quarto, sizeof(Quarto), 1, f);

				// Marcando o quarto como excluído (status = '-')
				strcpy(quarto.status, "excluido");

				fseek(f, sizeof(Quarto) * posicao, SEEK_SET);
				fwrite(&quarto, sizeof(Quarto), 1, f);
				fflush(f);

				printf("Quarto excluído com sucesso!\n");
		} else {
				printf("Quarto com número %d não encontrado!\n", numero);
		}
}

void imprime_quartos(FILE *f) {
		Quarto quarto;
		fseek(f, 0, SEEK_SET);
		fread(&quarto, sizeof(Quarto), 1, f);
		while (!feof(f)) {
				printf("Número do quarto: %d\n", quarto.numero);
				printf("Quantidade de hóspedes: %d\n", quarto.quantidade_hospedes);
				printf("Valor da diária: %.2f\n", quarto.valor_diaria);
				printf("Status do quarto: %s\n", quarto.status);
				printf("-----------------------\n");
				fread(&quarto, sizeof(Quarto), 1, f);
		}
}

int localiza_quarto(FILE *f, int numero) {
		int posicao = -1;
		Quarto quarto;
		fseek(f, 0, SEEK_SET);
		fread(&quarto, sizeof(Quarto), 1, f);
		while (!feof(f)) {
				posicao++;
				if (quarto.numero == numero && strcmp(quarto.status, "excluido") != 0) {
						return posicao;
				}
				fread(&quarto, sizeof(Quarto), 1, f);
		}
		return -1;
}

int gera_num_quarto(FILE *f) {
		Quarto quarto;
		int max_num = 0;
		fseek(f, 0, SEEK_SET);
		fread(&quarto, sizeof(Quarto), 1, f);
		while (!feof(f)) {
				if (quarto.numero > max_num) {
						max_num = quarto.numero;
				}
				fread(&quarto, sizeof(Quarto), 1, f);
		}
		return max_num + 1;
}

int verifica_disponibilidade_quarto(FILE *f, int numero_quarto, char *data_entrada, char *data_saida) {
		Quarto quarto;
		fseek(f, 0, SEEK_SET);
		fread(&quarto, sizeof(Quarto), 1, f);
		while (!feof(f)) {
				if (quarto.numero == numero_quarto && strcmp(quarto.status, "desocupado") == 0) {
						// Verificar se o quarto já está ocupado no período especificado
						// Aqui você pode implementar a lógica para verificar se há estadias para esse quarto no período
						// data_entrada e data_saida. Deixei como exemplo um retorno padrão para quando o quarto está desocupado.
						return 1; // Disponível
				}
				fread(&quarto, sizeof(Quarto), 1, f);
		}
		return 0; // Indisponível
}
