#include "checkout.h"
#include "estadia.h"
#include "quarto.h"
#include "cliente.h"
#include <stdio.h>
#include <string.h>

void dar_baixa_estadia() {
		int codigo_estadia;
		printf("Digite o código da estadia: ");
		scanf("%d", &codigo_estadia);

		int i;
		bool estadia_encontrada = false;
		for (i = 0; i < estadia_count; i++) {
				if (estadias[i].codigo == codigo_estadia) {
						estadia_encontrada = true;
						break;
				}
		}

		if (!estadia_encontrada) {
				printf("Erro: Estadia não encontrada.\n");
				return;
		}

		// Calcula o valor total a ser pago
		int numero_quarto = estadias[i].numero_quarto;
		int quantidade_diarias = estadias[i].quantidade_diarias;
		double valor_diaria = 0;

		for (int j = 0; j < quarto_count; j++) {
				if (quartos[j].numero == numero_quarto) {
						valor_diaria = quartos[j].valor_diaria;
						strcpy(quartos[j].status, "desocupado");
						salvar_quartos();
						break;
				}
		}

		double valor_total = quantidade_diarias * valor_diaria;
		printf("Valor total a ser pago pelo cliente: R$%.2f\n", valor_total);

		// Remove a estadia
		for (int k = i; k < estadia_count - 1; k++) {
				estadias[k] = estadias[k + 1];
		}
		estadia_count--;
		salvar_estadias();
}
