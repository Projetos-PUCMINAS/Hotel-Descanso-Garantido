#include "estadia.h"
#include "quarto.h"
#include "cliente.h"
#include <time.h>

// Array to store stays
Estadia estadias[MAX_ESTADIAS];
int estadia_count = 0;

void carregar_estadias() {
		FILE *file = fopen("estadias.dat", "rb");
		if (file != NULL) {
				fread(&estadia_count, sizeof(int), 1, file);
				fread(estadias, sizeof(Estadia), estadia_count, file);
				fclose(file);
		}
}

void salvar_estadias() {
		FILE *file = fopen("estadias.dat", "wb");
		if (file != NULL) {
				fwrite(&estadia_count, sizeof(int), 1, file);
				fwrite(estadias, sizeof(Estadia), estadia_count, file);
				fclose(file);
		}
}

int calcular_diarias(const char* data_entrada, const char* data_saida) {
		struct tm tm_entrada, tm_saida;
		time_t t_entrada, t_saida;

		memset(&tm_entrada, 0, sizeof(struct tm));
		memset(&tm_saida, 0, sizeof(struct tm));

		strptime(data_entrada, "%Y-%m-%d", &tm_entrada);
		strptime(data_saida, "%Y-%m-%d", &tm_saida);

		t_entrada = mktime(&tm_entrada);
		t_saida = mktime(&tm_saida);

		double seconds = difftime(t_saida, t_entrada);
		return (int)(seconds / (60 * 60 * 24));
}

void cadastrar_estadia() {
		int codigo_cliente, quantidade_hospedes, numero_quarto = -1;
		char data_entrada[11], data_saida[11];

		printf("Digite o código do cliente: ");
		scanf("%d", &codigo_cliente);

		bool cliente_existe = false;
		for (int i = 0; i < cliente_count; i++) {
				if (clientes[i].codigo == codigo_cliente) {
						cliente_existe = true;
						break;
				}
		}

		if (!cliente_existe) {
				printf("Erro: Cliente não encontrado.\n");
				return;
		}

		printf("Digite a quantidade de hóspedes: ");
		scanf("%d", &quantidade_hospedes);

		printf("Digite a data de entrada (YYYY-MM-DD): ");
		scanf("%s", data_entrada);

		printf("Digite a data de saída (YYYY-MM-DD): ");
		scanf("%s", data_saida);

		// Find available room
		for (int i = 0; i < quarto_count; i++) {
				if (quartos[i].quantidade_hospedes >= quantidade_hospedes && strcmp(quartos[i].status, "desocupado") == 0) {
						numero_quarto = quartos[i].numero;
						break;
				}
		}

		if (numero_quarto == -1) {
				printf("Erro: Não há quartos disponíveis para a quantidade de hóspedes.\n");
				return;
		}

		Estadia nova_estadia;
		nova_estadia.codigo = rand() % 1000 + 1;
		nova_estadia.codigo_cliente = codigo_cliente;
		nova_estadia.numero_quarto = numero_quarto;
		strcpy(nova_estadia.data_entrada, data_entrada);
		strcpy(nova_estadia.data_saida, data_saida);
		nova_estadia.quantidade_diarias = calcular_diarias(data_entrada, data_saida);

		estadias[estadia_count++] = nova_estadia;

		// Mark room as occupied
		for (int i = 0; i < quarto_count; i++) {
				if (quartos[i].numero == numero_quarto) {
						strcpy(quartos[i].status, "ocupado");
						salvar_quartos();
						break;
				}
		}

		salvar_estadias();
		printf("Estadia cadastrada com sucesso! Código: %d\n", nova_estadia.codigo);
}
