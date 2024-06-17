// clientes.h

#ifndef CLIENTES_H
#define CLIENTES_H

#include <stdio.h>

typedef struct {
		int cod_cliente;
		char nome_cliente[50];
		char endereco[100];
		char telefone_cliente[15];
		int excluido;
} Cliente;

FILE* inicializa_sistema();
int localiza_cliente(FILE *f, int cod_cliente);
int gera_cod_cliente(FILE *f);
void cadastra_cliente(FILE *f);
void altera_cliente(FILE *f);
void exclui_cliente(FILE *f);
void imprime_clientes(FILE *f, FILE *f_estadias);
void pesquisa_cliente_por_nome(FILE *f, char *nome);
void pesquisa_cliente_por_codigo(FILE *f, int cod_cliente);
int calcula_pontos_fidelidade(FILE *f_estadias, int cod_cliente);

#endif // CLIENTES_H
