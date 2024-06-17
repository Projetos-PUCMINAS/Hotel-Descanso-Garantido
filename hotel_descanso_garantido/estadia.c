#include "estadia.h"
#include "cliente.h"
#include "quarto.h"
#include "util.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Estadia estadias[MAX_ESTADIAS];
int qtd_estadias = 0;

void CarregarEstadias() {
    FILE *file = fopen("estadias.dat", "rb");
    if (file != NULL) {
        fread(&qtd_estadias, sizeof(int), 1, file);
        fread(estadias, sizeof(Estadia), qtd_estadias, file);
        fclose(file);
    }
}

void SalvarEstadias() {
    FILE *file = fopen("estadias.dat", "wb");
    if (file != NULL) {
        fwrite(&qtd_estadias, sizeof(int), 1, file);
        fwrite(estadias, sizeof(Estadia), qtd_estadias, file);
        fclose(file);
    }
}
bool ValidarData(const char* data) {
    int dia, mes, ano;
    if (sscanf(data, "%2d/%2d/%4d", &dia, &mes, &ano) != 3) {
        return false; 
    }

    if (ano < 1900 || ano > 2100 || mes < 1 || mes > 12 || dia < 1) {
        return false; 
    }

    int dias_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (mes == 2) {
        bool bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
        if (bissexto) {
            dias_mes[1] = 29; 
        }
    }

    return dia <= dias_mes[mes - 1];
}

int CalcularDiarias(const char *data_entrada, const char *data_saida) {
    int dia_entrada, mes_entrada, ano_entrada;
    int dia_saida, mes_saida, ano_saida;

    sscanf(data_entrada, "%d/%d/%d", &dia_entrada, &mes_entrada, &ano_entrada);
    sscanf(data_saida, "%d/%d/%d", &dia_saida, &mes_saida, &ano_saida);

    int total_dias_entrada = dia_entrada + mes_entrada * 30 + ano_entrada * 365;
    int total_dias_saida = dia_saida + mes_saida * 30 + ano_saida * 365;

    return total_dias_saida - total_dias_entrada;
}

void CadastrarEstadia() {
    if (qtd_estadias >= MAX_ESTADIAS) {
        printf("Erro: Número máximo de estadias atingido.\n");
        return;
    }

    int codigo_cliente;
    limpar_buffer();
    printf("Digite o código do cliente: ");
    if (scanf("%d", &codigo_cliente) != 1) {
        printf("Erro: Código do cliente inválido.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer(); 

    bool cliente_encontrado = false;
    for (int i = 0; i < qtd_clientes; i++) {
        if (clientes[i].cod_cliente == codigo_cliente) {
            cliente_encontrado = true;
            break;
        }
    }

    if (!cliente_encontrado) {
        printf("Erro: Cliente não encontrado.\n");
        return;
    }

    Estadia nova_estadia;
    nova_estadia.cod_estadia = qtd_estadias + 1;
    nova_estadia.codigo_cliente = codigo_cliente;

    printf("Digite a data de entrada (dd/mm/aaaa): ");
    if (scanf("%10s", nova_estadia.data_entrada) != 1 || !ValidarData(nova_estadia.data_entrada)) {
        printf("Erro: Data de entrada inválida.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer(); 

    printf("Digite a data de saída (dd/mm/aaaa): ");
    if (scanf("%10s", nova_estadia.data_saida) != 1 || !ValidarData(nova_estadia.data_saida)) {
        printf("Erro: Data de saída inválida.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer(); 

    if (CalcularDiarias(nova_estadia.data_entrada, nova_estadia.data_saida) < 0) {
        printf("Erro: A data de saída não pode ser anterior à data de entrada.\n");
        return;
    }

    nova_estadia.qtd_diarias = CalcularDiarias(nova_estadia.data_entrada, nova_estadia.data_saida);

    int quantidade_hospedes;
    printf("Digite a quantidade de hóspedes: ");
    if (scanf("%d", &quantidade_hospedes) != 1 || quantidade_hospedes <= 0) {
        printf("Erro: Quantidade de hóspedes inválida.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer(); 

    bool quarto_encontrado = false;
    int indice_quarto = -1;
    for (int i = 0; i < qtd_quartos; i++) {
        if (quartos[i].qtd_hospedes >= quantidade_hospedes &&
            strcmp(quartos[i].status, "desocupado") == 0) {
            nova_estadia.codigo_quarto = quartos[i].cod_quarto;
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
    SalvarQuartos();

    estadias[qtd_estadias++] = nova_estadia;
    SalvarEstadias();

    printf("Estadia cadastrada com sucesso! Código: %d\n", nova_estadia.cod_estadia);
}



void DarBaixaEstadia() {
    int codigo_estadia;
    printf("Digite o código da estadia: ");
    scanf("%d", &codigo_estadia);
    limpar_buffer(); 

    int i;
    bool estadia_encontrada = false;
    for (i = 0; i < qtd_quartos; i++) {
        if (estadias[i].cod_estadia == codigo_estadia) {
            estadia_encontrada = true;
            break;
        }
    }

    if (!estadia_encontrada) {
        printf("Erro: Estadia não encontrada.\n");
        return;
    }


    int numero_quarto = estadias[i].codigo_quarto;
    int quantidade_diarias = estadias[i].qtd_diarias;
    double valor_diaria = 0;

    for (int j = 0; j < qtd_quartos; j++) {
        if (quartos[j].cod_quarto == numero_quarto) {
            valor_diaria = quartos[j].v_diaria;
            strcpy(quartos[j].status, "desocupado");
            SalvarQuartos();
            printf("Status do quarto %d alterado para desocupado.\n", quartos[j].cod_quarto);
            break;
        }
    }

    double valor_total = quantidade_diarias * valor_diaria;
    printf("Valor total a ser pago pelo cliente: R$%.2f\n", valor_total);


    for (int k = i; k < qtd_estadias - 1; k++) {
        estadias[k] = estadias[k + 1];
    }
    qtd_estadias--;
    SalvarEstadias();
}


void MostrarEstadiasCliente(int codigo_cliente) {
    bool encontrado = false;
    for (int i = 0; i < qtd_estadias; i++) {
        if (estadias[i].codigo_cliente == codigo_cliente) {
            printf("Código da Estadia: %d\n", estadias[i].cod_estadia);
            printf("Data de Entrada: %s\n", estadias[i].data_entrada);
            printf("Data de Saída: %s\n", estadias[i].data_saida);
            printf("Quantidade de Diárias: %d\n", estadias[i].qtd_diarias);
            printf("Número do Quarto: %d\n", estadias[i].codigo_quarto);
            encontrado = true;
        }
    }

    if (!encontrado) {
        printf("Não há estadias encontradas para o cliente com o código %d.\n", codigo_cliente);
    }
}

void MostrarNumeroQuarto(int codigo_estadia) {
    for (int i = 0; i < qtd_estadias; i++) {
        if (estadias[i].cod_estadia == codigo_estadia) {
            printf("Número do Quarto: %d\n", estadias[i].codigo_quarto);
            return;
        }
    }
    printf("Estadia não encontrada.\n");
}


void MostrarTodasEstadias() {
    if (qtd_estadias == 0) {
        printf("Nenhuma estadia cadastrada.\n");
        return;
    }

    printf("Lista de Estadias:\n");
    for (int i = 0; i < qtd_estadias; i++) {
        printf("Código da Estadia: %d\n", estadias[i].cod_estadia);
        printf("Data de Entrada: %s\n", estadias[i].data_entrada);
        printf("Data de Saída: %s\n", estadias[i].data_saida);
        printf("Quantidade de Diárias: %d\n", estadias[i].qtd_diarias);
        printf("Número do Quarto: %d\n", estadias[i].codigo_quarto);
        printf("------------------------\n");
    }
}