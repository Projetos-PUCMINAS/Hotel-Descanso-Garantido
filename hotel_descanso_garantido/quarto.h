#ifndef QUARTO_H
#define QUARTO_H

#define MAX_QUARTOS 100

typedef struct {
		int cod_quarto;
		int qtd_hospedes;
		double v_diaria;
		char status[20]; 
} Quarto;

extern Quarto quartos[MAX_QUARTOS];
extern int qtd_quartos;

void CarregarQuartos();
void SalvarQuartos();
void CadastrarQuarto();
void AlterarStatusQuarto(int num, const char* novo_status);
void MostrarTodosQuartos();

#endif // QUARTO_H
