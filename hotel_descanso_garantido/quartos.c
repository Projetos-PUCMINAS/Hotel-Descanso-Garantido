#include "quartos.h"
#include <stdlib.h>
#include <string.h>

FILE* InicializarSistemaQuartos() {
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



int GeradorNumQuarto(FILE *f) {
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



int LocalizarQuarto(FILE *f, int numero) {
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



void CadastrarQuarto(FILE *f) {
		Quarto quarto;
		int num_quarto;
		int posicao;

		num_quarto = GeradorNumQuarto(f); 
		printf("Número do quarto gerado automaticamente: %d\n", num_quarto); 
		quarto.numero = num_quarto;
	
		printf("Digite a quantidade de hóspedes: ");
		scanf("%d", &quarto.quantidade_hospedes);

		printf("Digite o valor da diária: ");
		scanf("%f", &quarto.valor_diaria);

		strcpy(quarto.status, "desocupado");

		posicao = LocalizarQuarto(f, quarto.numero);
		if (posicao == -1) {
				fseek(f, 0, SEEK_END);
				fwrite(&quarto, sizeof(Quarto), 1, f);
				fflush(f);
				printf("Quarto cadastrado com sucesso!\n");
		} else {
				printf("Erro: Quarto com número %d já existe!\n", quarto.numero);
		}

		while (getchar() != '\n'); 
}



void AlterarQuarto(FILE *f) {
		int numero, posicao;
		Quarto quarto;

		printf("Digite o número do quarto para alterar: ");
		scanf("%d", &numero);

		posicao = LocalizarQuarto(f, numero);
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



void ExcluirQuarto(FILE *f) {
		int numero, posicao;
		Quarto quarto;

		printf("Digite o número do quarto para excluir: ");
		scanf("%d", &numero);

		posicao = LocalizarQuarto(f, numero);
		if (posicao != -1) {
				fseek(f, sizeof(Quarto) * posicao, SEEK_SET);
				fread(&quarto, sizeof(Quarto), 1, f);

				strcpy(quarto.status, "excluido");

				fseek(f, sizeof(Quarto) * posicao, SEEK_SET);
				fwrite(&quarto, sizeof(Quarto), 1, f);
				fflush(f);

				printf("Quarto excluído com sucesso!\n");
		} else {
				printf("Quarto com número %d não encontrado!\n", numero);
		}
}



void ImprimirQuartos(FILE *f) {
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
