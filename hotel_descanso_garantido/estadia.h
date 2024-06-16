#ifndef ESTADIA_H
#define ESTADIA_H

#define MAX_ESTADIAS 100

typedef struct {
    int codigo;
    char data_entrada[11]; 
    char data_saida[11]; 
    int quantidade_diarias;
    int codigo_cliente;
    int numero_quarto; 
} Estadia;

extern Estadia estadias[MAX_ESTADIAS];
extern int estadia_count;

void carregar_estadias();
void salvar_estadias();
void cadastrar_estadia();
void dar_baixa_estadia();
void mostrar_estadias_cliente(int codigo_cliente);
void mostrar_numero_quarto(int codigo_estadia); 
void mostrar_todas_estadias();

#endif // ESTADIA_H
