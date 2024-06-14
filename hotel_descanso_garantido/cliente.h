#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CLIENTES 100

typedef struct {
		int codigo;
		char nome[50];
		char endereco[100];
		char telefone[15];
} Cliente;

extern Cliente clientes[MAX_CLIENTES];
extern int cliente_count;

void carregar_clientes();
void salvar_clientes();
void cadastrar_cliente();

#endif // CLIENTE_H
