#include "quarto.h"
#include <stdio.h>
#include <string.h>

Quarto quartos[MAX_QUARTOS];
int quarto_count = 0;

void carregar_quartos() {
		FILE *file = fopen("quartos.dat", "rb");
		if (file != NULL) {
				fread(&quarto_count, sizeof(int), 1, file);
				fread(quartos, sizeof(Quarto), quarto_count, file);
				fclose(file);
		}
}

void salvar_quartos() {
		FILE *file = fopen("quartos.dat", "wb");
		if (file != NULL) {
				fwrite(&quarto_count, sizeof(int), 1, file);
				fwrite(quartos, sizeof(Quarto), quarto_count, file);
				fclose(file);
		}
}

void cadastrar_quarto() {
		if (quarto_count >= MAX_QUARTOS) {
				printf("Erro: Número máximo de quartos atingido.\n");
				return;
		}

		Quarto novo_quarto;
		novo_quarto.numero = rand() % 1000 + 1; // Gerar número de quarto automaticamente
		printf("Digite a quantidade de hóspedes: ");
		scanf("%d", &novo_quarto.quantidade_hospedes);
		printf("Digite o valor da diária: ");
		scanf("%lf", &novo_quarto.valor_diaria);
		strcpy(novo_quarto.status, "desocupado");

		quartos[quarto_count++] = novo_quarto;
		salvar_quartos();
		printf("Quarto cadastrado com sucesso! Número: %d\n", novo_quarto.numero);
}
