#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Tcliente
{
		int cod_cliente;
		char nome[50];
		char endereco[100];
		char telefone_cliente[15];
};
typedef struct Tcliente cliente;



void CarregarClientes(); 
void SalvarClientes();
void CadastrarCliente();
void BuscarClienteCodigo(char* termo_busca);
int calcular_pontos_fidelidade(int codigo_cliente);
void MostrarTodosClientes();

#endif // CLIENTE_H
