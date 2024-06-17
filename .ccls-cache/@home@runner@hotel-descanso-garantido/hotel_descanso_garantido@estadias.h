#ifndef ESTADIAS_H_INCLUDED
#define ESTADIAS_H_INCLUDED

#include <stdio.h>

typedef struct {
    int codigo_estadia;
    char data_entrada[11];
    char data_saida[11];
    int quantidade_diarias;
    int cod_cliente;
    int num_quarto;
} Estadia;

FILE* inicializa_sistema_estadias();
void cadastra_estadia(FILE *f, FILE *f_clientes, FILE *f_quartos);
int gera_cod_estadia(FILE *f);
int calcula_quantidade_diarias(char *data_entrada, char *data_saida);
void imprime_estadias(FILE *f);
void baixa_estadia(FILE *f, FILE *f_quartos, int codigo_estadia);
void mostra_estadias_cliente(FILE *f_estadias, FILE *f_clientes, char *nome_or_codigo);
int calcula_pontos_fidelidade_cliente(FILE *f_estadias, FILE *f_clientes, int cod_cliente);

#endif // ESTADIAS_H_INCLUDED
