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
		int pontos_fidelidade;
} Cliente;

extern Cliente clientes[MAX_CLIENTES];
extern int cliente_count;

void carregar_clientes();
void salvar_clientes();
void cadastrar_cliente();
void buscar_cliente_por_codigo(char* termo_busca);
int calcular_pontos_fidelidade(int codigo_cliente);
void mostrar_todos_clientes();

#endif // CLIENTE_H
