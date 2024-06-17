#include "quarto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "util.h"

Quarto quartos[MAX_QUARTOS];
int qtd_quartos = 0;

void CarregarQuartos() {
		FILE *file = fopen("quartos.dat", "rb");
		if (file != NULL) {
				fread(&qtd_quartos, sizeof(int), 1, file);
				fread(quartos, sizeof(Quarto), qtd_quartos, file);
				fclose(file);
		}
}

void SalvarQuartos() {
		FILE *file = fopen("quartos.dat", "wb");
		if (file != NULL) {
				fwrite(&qtd_quartos, sizeof(int), 1, file);
				fwrite(quartos, sizeof(Quarto), qtd_quartos, file);
				fclose(file);
		}
}

void CadastrarQuarto() {
		if (qtd_quartos >= MAX_QUARTOS) {
				printf("Erro: Número máximo de quartos atingido.\n");
				return;
		}

		Quarto novo_quarto;
		bool numero_unico;
		do {
				numero_unico = true;
				novo_quarto.cod_quarto = rand() % 1000 + 1;
				for (int i = 0; i < qtd_quartos; i++) {
						if (quartos[i].cod_quarto == novo_quarto.cod_quarto) {
								numero_unico = false;
								break;
						}
				}
		} while (!numero_unico);

	
	limpar_buffer();
	printf("Digite a quantidade de hóspedes: ");
	while (scanf("%d", &novo_quarto.qtd_hospedes) != 1 || novo_quarto.qtd_hospedes <= 0) {
			printf("Erro: Quantidade de hóspedes inválida. Digite novamente: ");
			limpar_buffer(); 
	}

	limpar_buffer();
	printf("Digite o valor da diária: ");
	while (scanf("%lf", &novo_quarto.v_diaria) != 1 || novo_quarto.v_diaria <= 0) {
			printf("Erro: Valor da diária inválido. Digite novamente: ");
			limpar_buffer(); 
	}

		strcpy(novo_quarto.status, "desocupado");

		quartos[qtd_quartos++] = novo_quarto;
			SalvarQuartos();
		printf("Quarto cadastrado com sucesso! Número: %d, Status: %s\n", novo_quarto.cod_quarto, novo_quarto.status);
}

void AlterarStatusQuarto(int num, const char* novo_status) {
		for (int i = 0; i < qtd_quartos; i++) {
				if (quartos[i].cod_quarto == num) {
						strcpy(quartos[i].status, novo_status);
						SalvarQuartos();
						printf("Status do quarto %d alterado para %s.\n", num, novo_status);
						return;
				}
		}
		printf("Erro: Quarto com número %d não encontrado.\n", num);
}


void MostrarTodosQuartos() {
		if (qtd_quartos == 0) {
				printf("Nenhum quarto cadastrado.\n");
				return;
		}

		printf("Lista de Quartos:\n");
		for (int i = 0; i < qtd_quartos; i++) {
				printf("Número: %d\n", quartos[i].cod_quarto);
				printf("Quantidade de Hóspedes: %d\n", quartos[i].qtd_hospedes);
				printf("Valor da Diária: R$%.2f\n", quartos[i].v_diaria);
				printf("Status: %s\n", quartos[i].status);
				printf("------------------------\n");
		}
}

