#include "estadias.h"
#include "clientes.h"
#include "quartos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *InicializarSistemaEstadias() {
    FILE *f;

    if ((f = fopen("estadias.dat", "r+b")) == NULL) {
        printf("Arquivo de estadias não existia... criando arquivo!\n");

        if ((f = fopen("estadias.dat", "w+b")) == NULL) {
            printf("Erro na criação do arquivo de estadias!\n");
            exit(1);
        }
    }

    return f;
}



int VerificarDispobilidadeQuarto(FILE *f, int numero_quarto, char *data_entrada, char *data_saida) {
    Estadia estadia;
    fseek(f, 0, SEEK_SET);
    fread(&estadia, sizeof(Estadia), 1, f);

    while (!feof(f)) {
        if (estadia.num_quarto == numero_quarto) {
            if (strcmp(estadia.data_saida, data_entrada) > 0 && strcmp(estadia.data_entrada, data_saida) < 0) {
                return 0; 
            }
        }
        fread(&estadia, sizeof(Estadia), 1, f);
    }
    return 1; 
}



void CadastrarEstadia(FILE *f, FILE *f_clientes, FILE *f_quartos) {
    Estadia estadia;
    Cliente cliente;
    Quarto quarto;
    int codigo_cliente, num_hospedes;
    char data_entrada[11], data_saida[11];
    int num_quarto;
    int disponivel, quantidade_diarias;
    char hora_chegada[6], hora_saida[6];

    printf("Digite o código do cliente: ");
    scanf("%d", &codigo_cliente);

    int pos_cliente = LocalizarCliente(f_clientes, codigo_cliente);
    if (pos_cliente == -1) {
        printf("Cliente com código %d não encontrado!\n", codigo_cliente);
        return;
    }

    fseek(f_clientes, sizeof(Cliente) * pos_cliente, SEEK_SET);
    fread(&cliente, sizeof(Cliente), 1, f_clientes);

    if (cliente.excluido == 1) {
        printf("Cliente com código %d está marcado como excluído!\n", codigo_cliente);
        return;
    }

    printf("Digite a data de entrada (formato dd/mm/aaaa): ");
    scanf("%s", data_entrada);

    printf("Digite a data de saída (formato dd/mm/aaaa): ");
    scanf("%s", data_saida);

    printf("Digite a hora de chegada (formato HH:MM): ");
    scanf("%s", hora_chegada);

    printf("Digite a hora de saída (formato HH:MM): ");
    scanf("%s", hora_saida);

    disponivel = 0;
    while (!disponivel) {
        printf("Digite o número de hóspedes: ");
        scanf("%d", &num_hospedes);

        fseek(f_quartos, 0, SEEK_SET);
        fread(&quarto, sizeof(Quarto), 1, f_quartos);
        while (!feof(f_quartos)) {
            if (strcmp(quarto.status, "desocupado") == 0 && quarto.quantidade_hospedes >= num_hospedes) {
                if (VerificarDispobilidadeQuarto(f, quarto.numero, data_entrada, data_saida)) {
                    disponivel = 1;
                    num_quarto = quarto.numero;

                    strcpy(quarto.status, "ocupado");
                    fseek(f_quartos, sizeof(Quarto) * LocalizarQuarto(f_quartos, num_quarto), SEEK_SET);
                    fwrite(&quarto, sizeof(Quarto), 1, f_quartos);
                    fflush(f_quartos);

                    break;
                }
            }
            fread(&quarto, sizeof(Quarto), 1, f_quartos);
        }

        if (!disponivel) {
            printf("Nenhum quarto disponível para %d hóspede(s) encontrado no período de %s a %s.\n", num_hospedes, data_entrada, data_saida);
        }
    }

    quantidade_diarias = CalcularQuantDiarias(data_entrada, hora_chegada, data_saida, hora_saida);

    estadia.codigo_estadia = GeradorCodEstadia(f);
    strcpy(estadia.data_entrada, data_entrada);
    strcpy(estadia.data_saida, data_saida);
    strcpy(estadia.hora_saida, hora_saida);
    estadia.quantidade_diarias = quantidade_diarias;
    estadia.cod_cliente = codigo_cliente;
    estadia.num_quarto = num_quarto;
    fseek(f, 0, SEEK_END);
    fwrite(&estadia, sizeof(Estadia), 1, f);
    fflush(f);
    printf("Estadia cadastrada com sucesso!\n");
    printf("Número do quarto utilizado no cadastro: %d\n", num_quarto);
}


void BaixaEstadia(FILE *f, FILE *f_quartos, FILE *f_clientes, int codigo_estadia) {
  Estadia estadia;
  Quarto quarto;
  Cliente cliente;
  int encontrou = 0;

  fseek(f, 0, SEEK_SET);
  fread(&estadia, sizeof(Estadia), 1, f);

  while (!feof(f)) {
      if (estadia.codigo_estadia == codigo_estadia) {
          encontrou = 1;

          fseek(f_clientes, sizeof(Cliente) * LocalizarCliente(f_clientes, estadia.cod_cliente), SEEK_SET);
          fread(&cliente, sizeof(Cliente), 1, f_clientes);
          fseek(f_quartos, sizeof(Quarto) * LocalizarQuarto(f_quartos, estadia.num_quarto), SEEK_SET);
          fread(&quarto, sizeof(Quarto), 1, f_quartos);

          float valor_total = estadia.quantidade_diarias * quarto.valor_diaria;
          strcpy(quarto.status, "desocupado");
          fseek(f_quartos, sizeof(Quarto) * LocalizarQuarto(f_quartos, estadia.num_quarto), SEEK_SET);
          fwrite(&quarto, sizeof(Quarto), 1, f_quartos);
          fflush(f_quartos);

          printf("Estadia do cliente: %s\n", cliente.nome_cliente);
          printf("Código da Estadia: %d\n", estadia.codigo_estadia);
          printf("Data de Entrada: %s\n", estadia.data_entrada);
          printf("Data de Saída: %s\n", estadia.data_saida);
          printf("Quantidade de Diárias: %d\n", estadia.quantidade_diarias);
          printf("Valor Total a ser pago: R$ %.2f\n", valor_total);
          break;
      }
      fread(&estadia, sizeof(Estadia), 1, f);
  }

  if (!encontrou) {
      printf("Estadia com código %d não encontrada.\n", codigo_estadia);
  }

    printf("-----------------------\n");
}



int  GeradorCodEstadia(FILE *f) {
  Estadia estadia;
  int max_cod = 0;
  fseek(f, 0, SEEK_SET);
  fread(&estadia, sizeof(Estadia), 1, f);
  while (!feof(f)) {
    if (estadia.codigo_estadia > max_cod) {
      max_cod = estadia.codigo_estadia;
    }
    fread(&estadia, sizeof(Estadia), 1, f);
  }
  return max_cod + 1;
}



int CalcularQuantDiarias(char *data_entrada, char *hora_chegada, char *data_saida, char *hora_saida) {
    int dia_entrada, mes_entrada, ano_entrada;
    int dia_saida, mes_saida, ano_saida;
    int hora_entrada, min_entrada, hora_saida_val, min_saida;
    sscanf(data_entrada, "%d/%d/%d", &dia_entrada, &mes_entrada, &ano_entrada);
    sscanf(data_saida, "%d/%d/%d", &dia_saida, &mes_saida, &ano_saida);
    sscanf(hora_chegada, "%d:%d", &hora_entrada, &min_entrada);
    sscanf(hora_saida, "%d:%d", &hora_saida_val, &min_saida);

    int dias_totais = ((ano_saida - ano_entrada) * 365 + (mes_saida - mes_entrada) * 30 + (dia_saida - dia_entrada));
    int horas_totais = (hora_saida_val - hora_entrada) * 60 + (min_saida - min_entrada);

    if (horas_totais < 0) {
        horas_totais += 24 * 60; // Corrigir para o dia seguinte
        dias_totais--; // Considerar como um dia a menos
    }

    if (hora_entrada < 14) {
        dias_totais--; // Menos um dia se a entrada for depois das 14h
    }

    if (hora_saida_val >= 12) {
        dias_totais++; // Mais um dia se a saída for às 12h ou depois
    }

    return dias_totais;
}





void ImprimirEstadias(FILE *f, FILE *f_clientes, FILE *f_quartos) {
    Estadia estadia;
    Cliente cliente;
    Quarto quarto;
    fseek(f, 0, SEEK_SET);

    while (fread(&estadia, sizeof(Estadia), 1, f) == 1) {
        fseek(f_clientes, sizeof(Cliente) * LocalizarCliente(f_clientes, estadia.cod_cliente), SEEK_SET);
        fseek(f_quartos, sizeof(Quarto) * LocalizarQuarto(f_quartos, estadia.num_quarto), SEEK_SET);
        fread(&quarto, sizeof(Quarto), 1, f_quartos);

        printf("Código de Estadia: %d\n", estadia.codigo_estadia);
        printf("Data de Entrada: %s\n", estadia.data_entrada);
        printf("Data de Saída: %s\n", estadia.data_saida);
        printf("Quantidade de Diárias: %d\n", estadia.quantidade_diarias);
        printf("Código do Cliente: %d\n", estadia.cod_cliente);
        printf("Nome do Cliente: %s\n", cliente.nome_cliente);
        printf("Número do Quarto: %d\n", estadia.num_quarto);
        printf("Status do Quarto: %s\n", quarto.status);
        printf("-----------------------\n");
    }
    while (getchar() != '\n'); 
    getchar(); 
    while (getchar() != '\n'); 
}




void MostrarEstadiasCliente(FILE *f_estadias, FILE *f_clientes,char *nome_or_codigo) {
  Cliente cliente;
  int codigo_cliente;


  if (sscanf(nome_or_codigo, "%d", &codigo_cliente) == 1) {
    PesquisarClientePorCodigo(f_clientes, codigo_cliente);
  } else {
    PesquisarClientePorNome(f_clientes, nome_or_codigo);
  }

  Estadia estadia;
  int encontrou_estadia = 0;

  fseek(f_estadias, 0, SEEK_SET);
  fread(&estadia, sizeof(estadia), 1, f_estadias);
  while (!feof(f_estadias)) {
    if (estadia.cod_cliente == codigo_cliente && !encontrou_estadia) {
      encontrou_estadia = 1;
      printf("\nEstadias do Cliente:\n");
    }
    if (estadia.cod_cliente == codigo_cliente) {
      printf("Código de Estadia: %d\n", estadia.codigo_estadia);
      printf("Data de Entrada: %s\n", estadia.data_entrada);
      printf("Data de Saída: %s\n", estadia.data_saida);
      printf("Quantidade de Diárias: %d\n", estadia.quantidade_diarias);
      printf("Número do Quarto: %d\n", estadia.num_quarto);
      printf("-----------------------\n");
    }
    fread(&estadia, sizeof(estadia), 1, f_estadias);
  }

  if (!encontrou_estadia) {
    printf("Não foram encontradas estadias para o cliente encontrado.\n");
  }
}



void PesquisarEstadiaPorCodigo(FILE *f, int codigo_estadia) {
    Estadia estadia;
    int posicao = -1;

    fseek(f, 0, SEEK_SET);
    while (fread(&estadia, sizeof(Estadia), 1, f) == 1) {
        if (estadia.codigo_estadia == codigo_estadia) {
            posicao = ftell(f) / sizeof(Estadia) - 1;
            break;
        }
    }

    if (posicao != -1) {
        fseek(f, sizeof(Estadia) * posicao, SEEK_SET);
        fread(&estadia, sizeof(Estadia), 1, f);
        printf("Código de Estadia: %d\n", estadia.codigo_estadia);
        printf("Data de Entrada: %s\n", estadia.data_entrada);
        printf("Data de Saída: %s\n", estadia.data_saida);
        printf("Quantidade de Diárias: %d\n", estadia.quantidade_diarias);
        printf("Código do Cliente: %d\n", estadia.cod_cliente);
        printf("Número do Quarto: %d\n", estadia.num_quarto);
    } else {
        printf("Estadia com código %d não encontrada!\n", codigo_estadia);
    }

    printf("-----------------------\n");
    getchar(); 
}



