#include "estadia.h"
#include "cliente.h"
#include "quarto.h"
#include "util.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Estadia estadias[MAX_ESTADIAS];
int estadia_count = 0;

void carregar_estadias() {
    FILE *file = fopen("estadias.dat", "rb");
    if (file != NULL) {
        fread(&estadia_count, sizeof(int), 1, file);
        fread(estadias, sizeof(Estadia), estadia_count, file);
        fclose(file);
    }
}

void salvar_estadias() {
    FILE *file = fopen("estadias.dat", "wb");
    if (file != NULL) {
        fwrite(&estadia_count, sizeof(int), 1, file);
        fwrite(estadias, sizeof(Estadia), estadia_count, file);
        fclose(file);
    }
}

int calcular_diarias(const char *data_entrada, const char *data_saida) {
    int dia_entrada, mes_entrada, ano_entrada;
    int dia_saida, mes_saida, ano_saida;
    sscanf(data_entrada, "%d/%d/%d", &dia_entrada, &mes_entrada, &ano_entrada);
    sscanf(data_saida, "%d/%d/%d", &dia_saida, &mes_saida, &ano_saida);

    int total_dias_entrada = dia_entrada + mes_entrada * 30 + ano_entrada * 365;
    int total_dias_saida = dia_saida + mes_saida * 30 + ano_saida * 365;

    return total_dias_saida - total_dias_entrada;
}

void cadastrar_estadia() {
    if (estadia_count >= MAX_ESTADIAS) {
        printf("Erro: Número máximo de estadias atingido.\n");
        return;
    }

    int codigo_cliente;
    limpar_buffer();
    printf("Digite o código do cliente: ");
    scanf("%d", &codigo_cliente);
    limpar_buffer(); 

    bool cliente_encontrado = false;
    for (int i = 0; i < cliente_count; i++) {
        if (clientes[i].codigo == codigo_cliente) {
            cliente_encontrado = true;
            break;
        }
    }

    if (!cliente_encontrado) {
        printf("Erro: Cliente não encontrado.\n");
        return;
    }

    Estadia nova_estadia;
    nova_estadia.codigo = estadia_count + 1;
    nova_estadia.codigo_cliente = codigo_cliente;

    printf("Digite a data de entrada (dd/mm/aaaa): ");
    scanf("%s", nova_estadia.data_entrada);
    limpar_buffer(); 
    printf("Digite a data de saída (dd/mm/aaaa): ");
    scanf("%s", nova_estadia.data_saida);
    limpar_buffer(); 

    nova_estadia.quantidade_diarias = calcular_diarias(nova_estadia.data_entrada, nova_estadia.data_saida);

    int quantidade_hospedes;
    printf("Digite a quantidade de hóspedes: ");
    scanf("%d", &quantidade_hospedes);
    limpar_buffer(); 

    bool quarto_encontrado = false;
    int indice_quarto = -1;
    for (int i = 0; i < quarto_count; i++) {
        if (quartos[i].quantidade_hospedes >= quantidade_hospedes &&
            strcmp(quartos[i].status, "desocupado") == 0) {
            nova_estadia.numero_quarto = quartos[i].numero;
            indice_quarto = i; 
            quarto_encontrado = true;
            break;
        }
    }

    if (!quarto_encontrado) {
        printf("Erro: Não há quartos disponíveis para a quantidade de hóspedes desejada.\n");
        return;
    }

    strcpy(quartos[indice_quarto].status, "ocupado");
    salvar_quartos();

    estadias[estadia_count++] = nova_estadia;
    salvar_estadias();

    printf("Estadia cadastrada com sucesso! Código: %d\n", nova_estadia.codigo);
    mostrar_numero_quarto(nova_estadia.codigo);
}


void dar_baixa_estadia() {
    int codigo_estadia;
    printf("Digite o código da estadia: ");
    scanf("%d", &codigo_estadia);
    limpar_buffer(); 

    int i;
    bool estadia_encontrada = false;
    for (i = 0; i < estadia_count; i++) {
        if (estadias[i].codigo == codigo_estadia) {
            estadia_encontrada = true;
            break;
        }
    }

    if (!estadia_encontrada) {
        printf("Erro: Estadia não encontrada.\n");
        return;
    }


    int numero_quarto = estadias[i].numero_quarto;
    int quantidade_diarias = estadias[i].quantidade_diarias;
    double valor_diaria = 0;

    for (int j = 0; j < quarto_count; j++) {
        if (quartos[j].numero == numero_quarto) {
            valor_diaria = quartos[j].valor_diaria;
            strcpy(quartos[j].status, "desocupado");
            salvar_quartos();
            printf("Status do quarto %d alterado para desocupado.\n", quartos[j].numero);
            break;
        }
    }

    double valor_total = quantidade_diarias * valor_diaria;
    printf("Valor total a ser pago pelo cliente: R$%.2f\n", valor_total);


    for (int k = i; k < estadia_count - 1; k++) {
        estadias[k] = estadias[k + 1];
    }
    estadia_count--;
    salvar_estadias();
}


void mostrar_estadias_cliente(int codigo_cliente) {
    bool encontrado = false;
    for (int i = 0; i < estadia_count; i++) {
        if (estadias[i].codigo_cliente == codigo_cliente) {
            printf("Código da Estadia: %d\n", estadias[i].codigo);
            printf("Data de Entrada: %s\n", estadias[i].data_entrada);
            printf("Data de Saída: %s\n", estadias[i].data_saida);
            printf("Quantidade de Diárias: %d\n", estadias[i].quantidade_diarias);
            printf("Número do Quarto: %d\n", estadias[i].numero_quarto);
            encontrado = true;
        }
    }

    if (!encontrado) {
        printf("Não há estadias encontradas para o cliente com o código %d.\n", codigo_cliente);
    }
}

void mostrar_numero_quarto(int codigo_estadia) {
    for (int i = 0; i < estadia_count; i++) {
        if (estadias[i].codigo == codigo_estadia) {
            printf("Número do Quarto: %d\n", estadias[i].numero_quarto);
            return;
        }
    }
    printf("Estadia não encontrada.\n");
}


void mostrar_todas_estadias() {
    if (estadia_count == 0) {
        printf("Nenhuma estadia cadastrada.\n");
        return;
    }

    printf("Lista de Estadias:\n");
    for (int i = 0; i < estadia_count; i++) {
        printf("Código da Estadia: %d\n", estadias[i].codigo);
        printf("Data de Entrada: %s\n", estadias[i].data_entrada);
        printf("Data de Saída: %s\n", estadias[i].data_saida);
        printf("Quantidade de Diárias: %d\n", estadias[i].quantidade_diarias);
        printf("Número do Quarto: %d\n", estadias[i].numero_quarto);
        printf("------------------------\n");
    }
}