// clientes.h

#ifndef CLIENTES_H
#define CLIENTES_H

#include <stdio.h>

typedef struct {
		int cod_cliente;
		char nome_cliente[50];
		char endereco[100];
		char telefone_cliente[15];
		int pontos_fidelidade;
		int excluido;
} Cliente;

FILE* InicializarSistemaClientes();
int LocalizarCliente(FILE *f, int cod_cliente);
int GeradorCodCliente(FILE *f);
void CadastrarCliente(FILE *f);
void AlterarCliente(FILE *f);
void ExcluirCliente(FILE *f);
void ImprimirClientes(FILE *f, FILE *f_estadias);
void PesquisarClientePorNome(FILE *f, char *nome);
void PesquisarClientePorCodigo(FILE *f, int cod_cliente);

#endif // CLIENTES_H
