#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CLIENTES 100

typedef struct {
		int cod_cliente;
		char nome_cliente[50];
		char endereco_cliente[100];
		char telefone_cliente[15];
		int pontos_fidelidade;
} Cliente;

extern Cliente clientes[MAX_CLIENTES];
extern int qtd_clientes;

void CarregarClientes(); 
void SalvarClientes();
void CadastrarCliente();
void BuscarClienteCodigo(char* termo_busca);
int calcular_pontos_fidelidade(int codigo_cliente);
void MostrarTodosClientes();

#endif // CLIENTE_H
