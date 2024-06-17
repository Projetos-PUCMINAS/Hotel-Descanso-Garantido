#ifndef QUARTOS_H_INCLUDED
#define QUARTOS_H_INCLUDED

#include <stdio.h>

typedef struct TQuarto {
		int numero;
		int quantidade_hospedes;
		float valor_diaria;
		char status[11]; 
} Quarto;

FILE* InicializarSistemaQuartos();
void CadastrarQuarto(FILE *f);
void AlterarQuarto(FILE *f);
void ExcluirQuarto(FILE *f);
void ImprimirQuartos(FILE *f);
int LocalizarQuarto(FILE *f, int numero);
int GeradorNumQuarto(FILE *f);
#endif // QUARTOS_H_INCLUDED
