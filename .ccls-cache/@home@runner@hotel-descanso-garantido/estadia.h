#ifndef ESTADIA_H
#define ESTADIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "quarto.h"
#include "cliente.h"

#define MAX_ESTADIAS 100

typedef struct {
    int codigo;
    char data_entrada[11]; // formato "dd/mm/aaaa"
    char data_saida[11];   // formato "dd/mm/aaaa"
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

#endif // ESTADIA_H
