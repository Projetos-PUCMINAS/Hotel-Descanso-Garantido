#ifndef ESTADIA_H
#define ESTADIA_H

#define MAX_ESTADIAS 100

typedef struct {
    int cod_estadia;
    char data_entrada[11]; 
    char data_saida[11]; 
    int qtd_diarias;
    int codigo_cliente;
    int codigo_quarto; 
} Estadia;

extern Estadia estadias[MAX_ESTADIAS];
extern int qtd_estadias;

void CarregarEstadias();
void SalvarEstadias();
void CadastrarEstadia();
void DarBaixaEstadia();
void MostrarEstadiasCliente(int codigo_cliente);
void MostrarNumeroQuarto(int codigo_estadia); 
void MostrarTodasEstadias();

#endif // ESTADIA_H
