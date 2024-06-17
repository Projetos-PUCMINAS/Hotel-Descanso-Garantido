#ifndef QUARTOS_H_INCLUDED
#define QUARTOS_H_INCLUDED

#include <stdio.h>

typedef struct TQuarto {
		int numero;
		int quantidade_hospedes;
		float valor_diaria;
		char status[11]; // "desocupado" ou "ocupado"
} Quarto;

FILE* inicializa_sistema_quartos();
void cadastra_quarto(FILE *f);
void altera_quarto(FILE *f);
void exclui_quarto(FILE *f);
void imprime_quartos(FILE *f);
int localiza_quarto(FILE *f, int numero);
int gera_num_quarto(FILE *f);
int verifica_disponibilidade_quarto(FILE *f, int numero_quarto, char *data_entrada, char *data_saida);
#endif // QUARTOS_H_INCLUDED
