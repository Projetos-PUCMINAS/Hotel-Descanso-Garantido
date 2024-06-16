#include "quarto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "util.h"

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
		bool numero_unico;
		do {
				numero_unico = true;
				novo_quarto.numero = rand() % 1000 + 1;
				for (int i = 0; i < quarto_count; i++) {
						if (quartos[i].numero == novo_quarto.numero) {
								numero_unico = false;
								break;
						}
				}
		} while (!numero_unico);

		limpar_buffer();
		printf("Digite a quantidade de hóspedes: ");
		scanf("%d", &novo_quarto.quantidade_hospedes);
		limpar_buffer(); 

		printf("Digite o valor da diária: ");
		scanf("%lf", &novo_quarto.valor_diaria);
		limpar_buffer(); 

		strcpy(novo_quarto.status, "desocupado");

		quartos[quarto_count++] = novo_quarto;
		salvar_quartos();
		printf("Quarto cadastrado com sucesso! Número: %d, Status: %s\n", novo_quarto.numero, novo_quarto.status);
}

void alterar_status_quarto(int numero, const char* novo_status) {
		for (int i = 0; i < quarto_count; i++) {
				if (quartos[i].numero == numero) {
						strcpy(quartos[i].status, novo_status);
						salvar_quartos();
						printf("Status do quarto %d alterado para %s.\n", numero, novo_status);
						return;
				}
		}
		printf("Erro: Quarto com número %d não encontrado.\n", numero);
}


void mostrar_todos_quartos() {
		if (quarto_count == 0) {
				printf("Nenhum quarto cadastrado.\n");
				return;
		}

		printf("Lista de Quartos:\n");
		for (int i = 0; i < quarto_count; i++) {
				printf("Número: %d\n", quartos[i].numero);
				printf("Quantidade de Hóspedes: %d\n", quartos[i].quantidade_hospedes);
				printf("Valor da Diária: R$%.2f\n", quartos[i].valor_diaria);
				printf("Status: %s\n", quartos[i].status);
				printf("------------------------\n");
		}
}

