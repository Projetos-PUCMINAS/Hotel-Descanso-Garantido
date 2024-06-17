#include "funcionario.h"
#include "util.h"

Funcionario funcionarios[MAX_FUNCIONARIOS];
int qtd_funcionaros = 0;

void CarregarFuncionarios() {
  FILE *file = fopen("funcionarios.dat", "rb");
  if (file != NULL) {
    fread(&qtd_funcionaros, sizeof(int), 1, file);
    fread(funcionarios, sizeof(Funcionario), qtd_funcionaros, file);
    fclose(file);
  }
}

void SalvarFuncionarios() {
  FILE *file = fopen("funcionarios.dat", "wb");
  if (file != NULL) {
    fwrite(&qtd_funcionaros, sizeof(int), 1, file);
    fwrite(funcionarios, sizeof(Funcionario), qtd_funcionaros, file);
    fclose(file);
  }
}

void CadastrarFuncionario() {
  if (qtd_funcionaros >= MAX_FUNCIONARIOS) {
    printf("Limite de funcionários atingido!\n");
    return;
  }

  Funcionario novo_funcionario;

  limpar_buffer();
  printf("Digite o nome do funcionário: ");
  fgets(novo_funcionario.nome_funcionario, sizeof(novo_funcionario.nome_funcionario), stdin);
  novo_funcionario.nome_funcionario[strcspn(novo_funcionario.nome_funcionario, "\n")] = '\0';

  limpar_buffer();
  printf("Digite o telefone do funcionário (DD numero): ");
  fgets(novo_funcionario.telefone_funcionario, sizeof(novo_funcionario.telefone_funcionario), stdin);
  novo_funcionario.telefone_funcionario[strcspn(novo_funcionario.telefone_funcionario, "\n")] = '\0';

  limpar_buffer();
  printf("Digite o cargo do funcionário: ");
  fgets(novo_funcionario.cargo, sizeof(novo_funcionario.cargo), stdin);
  novo_funcionario.cargo[strcspn(novo_funcionario.cargo, "\n")] = '\0';

  limpar_buffer();
  printf("Digite o salário do funcionário: ");
  while (scanf("%lf", &novo_funcionario.salario) != 1 || novo_funcionario.salario <= 0) {
      printf("Erro: Salário inválido. Digite novamente: ");
      limpar_buffer(); 
  }

  if (strlen(novo_funcionario.nome_funcionario) == 0 || strlen(novo_funcionario.telefone_funcionario) == 0 || strlen(novo_funcionario.cargo) == 0) {
      printf("Erro: Todos os campos devem ser preenchidos.\n");
      return;
  }
  
  bool codigo_unico;
  do {
    codigo_unico = true;
    novo_funcionario.cod_funcionario = rand() % 1000 + 1;
    for (int i = 0; i < qtd_funcionaros; i++) {
      if (funcionarios[i].cod_funcionario == novo_funcionario.cod_funcionario) {
        codigo_unico = false;
        break;
      }
    }
  } while (!codigo_unico);

  funcionarios[qtd_funcionaros++] = novo_funcionario;
  SalvarFuncionarios();
  printf("Funcionário cadastrado com sucesso! Código: %d\n",
  novo_funcionario.cod_funcionario);
}

void BuscarFuncionarioCodigo(char *termo_busca) {
  int codigo_busca;
  sscanf(termo_busca, "%d", &codigo_busca);

  bool encontrado = false;
  for (int i = 0; i < qtd_funcionaros; i++) {
    if (funcionarios[i].cod_funcionario == codigo_busca ||
        strstr(funcionarios[i].nome_funcionario, termo_busca) != NULL) {
      printf("Código: %d\n", funcionarios[i].cod_funcionario);
      printf("Nome: %s\n", funcionarios[i].nome_funcionario);
      printf("Cargo: %s\n", funcionarios[i].cargo);
      printf("Telefone: %s\n", funcionarios[i].telefone_funcionario);
      printf("Salário: R$%.2f\n", funcionarios[i].salario);
      encontrado = true;
    }
  }

  if (!encontrado) {
    printf("Funcionário não encontrado.\n");
  }
}


void MostrarTodosFuncionarios() {
    if (qtd_funcionaros == 0) {
        printf("Nenhum funcionário cadastrado.\n");
        return;
    }

    printf("Lista de Funcionários:\n");
    for (int i = 0; i < qtd_funcionaros; i++) {
        printf("Código: %d\n", funcionarios[i].cod_funcionario);
        printf("Nome: %s\n", funcionarios[i].nome_funcionario);
        printf("Cargo: %s\n", funcionarios[i].cargo);
        printf("Telefone: %s\n", funcionarios[i].telefone_funcionario);
        printf("Salário: R$%.2f\n", funcionarios[i].salario);
        printf("------------------------\n");
    }
}