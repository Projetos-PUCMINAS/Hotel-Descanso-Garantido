#include "estadias.h"
#include "clientes.h"
#include "quartos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cadastra_estadia(FILE *f, FILE *f_clientes, FILE *f_quartos) {
  Estadia estadia;
  Cliente cliente;
  Quarto quarto;
  int codigo_cliente, num_hospedes;
  char data_entrada[11], data_saida[11];
  int num_quarto;
  int disponivel, quantidade_diarias;

  // Solicitar dados da estadia
  printf("Digite o código do cliente: ");
  scanf("%d", &codigo_cliente);

  // Verificar se o cliente existe
  int pos_cliente = localiza_cliente(f_clientes, codigo_cliente);
  if (pos_cliente == -1) {
    printf("Cliente com código %d não encontrado!\n", codigo_cliente);
    return;
  }

  // Ler dados do cliente
  fseek(f_clientes, sizeof(Cliente) * pos_cliente, SEEK_SET);
  fread(&cliente, sizeof(Cliente), 1, f_clientes);

  // Verificar se o cliente já foi excluído
  if (cliente.excluido == 1) {
    printf("Cliente com código %d está marcado como excluído!\n",
           codigo_cliente);
    return;
  }

  // Verificar se o cliente já possui uma estadia em aberto
  // (não implementado neste exemplo)

  // Solicitar e verificar dados do quarto e datas
  printf("Digite o número de hóspedes: ");
  scanf("%d", &num_hospedes);

  printf("Digite a data de entrada (formato dd/mm/aaaa): ");
  scanf("%s", data_entrada);

  printf("Digite a data de saída (formato dd/mm/aaaa): ");
  scanf("%s", data_saida);

  // Encontrar quarto disponível para o período e número de hóspedes
  disponivel = 0;
  while (!disponivel) {
    printf("Digite o número do quarto desejado: ");
    scanf("%d", &num_quarto);

    disponivel = verifica_disponibilidade_quarto(f_quartos, num_quarto,
                                                 data_entrada, data_saida);

    if (!disponivel) {
      printf("Quarto não disponível para o período especificado ou não "
             "encontrado!\n");
    }
  }

  // Calcular quantidade de diárias
  quantidade_diarias = calcula_quantidade_diarias(data_entrada, data_saida);

  // Preencher os dados da estadia
  estadia.codigo_estadia = gera_cod_estadia(f);
  strcpy(estadia.data_entrada, data_entrada);
  strcpy(estadia.data_saida, data_saida);
  estadia.quantidade_diarias = quantidade_diarias;
  estadia.cod_cliente = codigo_cliente;
  estadia.num_quarto = num_quarto;

  // Gravar estadia no arquivo
  fseek(f, 0, SEEK_END);
  fwrite(&estadia, sizeof(Estadia), 1, f);
  fflush(f);

  printf("Estadia cadastrada com sucesso!\n");
}

void baixa_estadia(FILE *f, FILE *f_quartos, FILE *f_clientes, int codigo_estadia)
 {
  Estadia estadia;
  Quarto quarto;
  Cliente cliente;
  int encontrou = 0;

  // Buscar a estadia pelo código
  fseek(f, 0, SEEK_SET);
  fread(&estadia, sizeof(Estadia), 1, f);

  while (!feof(f)) {
    if (estadia.codigo_estadia == codigo_estadia) {
      encontrou = 1;

      // Ler dados do cliente
      fseek(f_clientes,
            sizeof(Cliente) * localiza_cliente(f_clientes, estadia.cod_cliente),
            SEEK_SET);
      fread(&cliente, sizeof(Cliente), 1, f_clientes);

      // Ler dados do quarto
      fseek(f_quartos, (estadia.num_quarto - 1) * sizeof(Quarto), SEEK_SET);
      fread(&quarto, sizeof(Quarto), 1, f_quartos);

      // Calcular o valor total a ser pago
      float valor_total = estadia.quantidade_diarias * quarto.valor_diaria;

      // Atualizar o status do quarto para desocupado
      strcpy(quarto.status, "desocupado");
      fseek(f_quartos, (estadia.num_quarto - 1) * sizeof(Quarto), SEEK_SET);
      fwrite(&quarto, sizeof(Quarto), 1, f_quartos);

      // Imprimir informações da estadia e valor total
      printf("Estadia do cliente: %s\n", cliente.nome_cliente);
      printf("Código da Estadia: %d\n", estadia.codigo_estadia);
      printf("Data de Entrada: %s\n", estadia.data_entrada);
      printf("Data de Saída: %s\n", estadia.data_saida);
      printf("Quantidade de Diárias: %d\n", estadia.quantidade_diarias);
      printf("Valor Total a ser pago: R$ %.2f\n", valor_total);

      // Marcar a estadia como concluída (remover ou marcar como concluída no
      // arquivo) Neste exemplo, o código está omitido, pois depende da
      // implementação específica do arquivo de estadias

      break;
    }
    fread(&estadia, sizeof(Estadia), 1, f);
  }

  if (!encontrou) {
    printf("Estadia com código %d não encontrada.\n", codigo_estadia);
  }
}

int gera_cod_estadia(FILE *f) {
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

int calcula_quantidade_diarias(char *data_entrada, char *data_saida) {
  // Implementação simples para calcular quantidade de diárias
  // Considera que as datas estão no formato dd/mm/aaaa
  int dia_entrada, mes_entrada, ano_entrada;
  int dia_saida, mes_saida, ano_saida;
  sscanf(data_entrada, "%d/%d/%d", &dia_entrada, &mes_entrada, &ano_entrada);
  sscanf(data_saida, "%d/%d/%d", &dia_saida, &mes_saida, &ano_saida);

  // Simplificação: considera apenas o número de dias entre as datas
  // Não considera leap years, etc.
  return ((ano_saida - ano_entrada) * 365 + (mes_saida - mes_entrada) * 30 +
          (dia_saida - dia_entrada));
}
void imprime_estadias(FILE *f) {
  Estadia estadia;
  fseek(f, 0, SEEK_SET);
  fread(&estadia, sizeof(Estadia), 1, f);
  while (!feof(f)) {
    printf("Código de Estadia: %d\n", estadia.codigo_estadia);
    printf("Data de Entrada: %s\n", estadia.data_entrada);
    printf("Data de Saída: %s\n", estadia.data_saida);
    printf("Quantidade de Diárias: %d\n", estadia.quantidade_diarias);
    printf("Código do Cliente: %d\n", estadia.cod_cliente);
    printf("Número do Quarto: %d\n", estadia.num_quarto);
    printf("\n");
    fread(&estadia, sizeof(Estadia), 1, f);
  }
}

void mostra_estadias_cliente(FILE *f_estadias, FILE *f_clientes,
                             char *nome_or_codigo) {
  Cliente cliente;
  int codigo_cliente;

  // Verificar se o nome_or_codigo é um número (código de cliente) ou um nome
  if (sscanf(nome_or_codigo, "%d", &codigo_cliente) == 1) {
    // Se foi possível ler um número, pesquisar pelo código do cliente
    pesquisa_cliente_por_codigo(f_clientes, codigo_cliente);
  } else {
    // Caso contrário, pesquisar pelo nome do cliente
    pesquisa_cliente_por_nome(f_clientes, nome_or_codigo);
  }

  // Agora buscar e mostrar todas as estadias relacionadas ao cliente encontrado
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

int calcula_pontos_fidelidade_cliente(FILE *f_estadias, FILE *f_clientes,
                                      int cod_cliente) {
  int pontos_fidelidade = 0;

  // Calcular pontos de fidelidade utilizando a função de clientes
  pontos_fidelidade = calcula_pontos_fidelidade(f_estadias, cod_cliente);

  return pontos_fidelidade;
}