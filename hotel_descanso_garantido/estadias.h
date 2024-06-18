#ifndef ESTADIAS_H_INCLUDED
#define ESTADIAS_H_INCLUDED

#include <stdio.h>

typedef struct {
  int codigo_estadia;
  char data_entrada[11];
  char hora_chegada[6]; // HH:MM
  char data_saida[11];
  char hora_saida[6]; // HH:MM
  int quantidade_diarias;
  int cod_cliente;
  int num_quarto;
} Estadia;

FILE *InicializarSistemaEstadias();
int VerificarDispobilidadeQuarto(FILE *f, int numero_quarto, char *data_entrada, char *data_saida);
void CadastrarEstadia(FILE *f, FILE *f_clientes, FILE *f_quartos);
int GeradorCodEstadia(FILE *f);
int CalcularQuantDiarias(char *data_entrada, char *hora_chegada, char *data_saida, char *hora_saida);
void ImprimirEstadias(FILE *f, FILE *f_clientes, FILE *f_quartos);
void BaixaEstadia(FILE *f, FILE *f_quartos, FILE *f_clientes, int codigo_estadia);
void MostrarEstadiasCliente(FILE *f_estadias, FILE *f_clientes, char *nome_or_codigo);
void PesquisarEstadiaPorCodigo(FILE *f, int codigo_estadia);
#endif // ESTADIAS_H_INCLUDED
