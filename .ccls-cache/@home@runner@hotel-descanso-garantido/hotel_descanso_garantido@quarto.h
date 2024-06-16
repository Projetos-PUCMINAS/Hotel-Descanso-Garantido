#ifndef QUARTO_H
#define QUARTO_H

#define MAX_QUARTOS 100

typedef struct {
		int numero;
		int quantidade_hospedes;
		double valor_diaria;
		char status[20]; 
} Quarto;

extern Quarto quartos[MAX_QUARTOS];
extern int quarto_count;

void carregar_quartos();
void salvar_quartos();
void cadastrar_quarto();
void alterar_status_quarto(int numero, const char* novo_status);
void mostrar_todos_quartos();

#endif // QUARTO_H
