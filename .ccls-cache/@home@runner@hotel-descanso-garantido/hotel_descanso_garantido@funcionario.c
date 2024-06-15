#include "funcionario.h"
#include "util.h"

Funcionario funcionarios[MAX_FUNCIONARIOS];
int funcionario_count = 0;

void carregar_funcionarios() {
		FILE *file = fopen("funcionarios.dat", "rb");
		if (file != NULL) {
				fread(&funcionario_count, sizeof(int), 1, file);
				fread(funcionarios, sizeof(Funcionario), funcionario_count, file);
				fclose(file);
		}
}

void salvar_funcionarios() {
		FILE *file = fopen("funcionarios.dat", "wb");
		if (file != NULL) {
				fwrite(&funcionario_count, sizeof(int), 1, file);
				fwrite(funcionarios, sizeof(Funcionario), funcionario_count, file);
				fclose(file);
		}
}

void cadastrar_funcionario() {
		if (funcionario_count >= MAX_FUNCIONARIOS) {
				printf("Limite de funcionários atingido!\n");
				return;
		}

		Funcionario novo_funcionario;

		limpar_buffer();
		printf("Digite o nome do funcionário: ");
		fgets(novo_funcionario.nome, sizeof(novo_funcionario.nome), stdin);
		novo_funcionario.nome[strcspn(novo_funcionario.nome, "\n")] = '\0'; 
	// Remove o '\n' se presente

		printf("Digite o telefone do funcionário: ");
		fgets(novo_funcionario.telefone, sizeof(novo_funcionario.telefone), stdin);
		novo_funcionario.telefone[strcspn(novo_funcionario.telefone, "\n")] = '\0';
	limpar_buffer();// Remove o '\n' se presente

		printf("Digite o cargo do funcionário: ");
		fgets(novo_funcionario.cargo, sizeof(novo_funcionario.cargo), stdin);
		novo_funcionario.cargo[strcspn(novo_funcionario.cargo, "\n")] = '\0';
	limpar_buffer();// Remove o '\n' se presente

		printf("Digite o salário do funcionário: ");
		scanf("%lf", &novo_funcionario.salario);
		limpar_buffer(); // Limpa o buffer de entrada

		// Gerar um código único
		bool codigo_unico;
		do {
				codigo_unico = true;
				novo_funcionario.codigo = rand() % 1000 + 1;
				for (int i = 0; i < funcionario_count; i++) {
						if (funcionarios[i].codigo == novo_funcionario.codigo) {
								codigo_unico = false;
								break;
						}
				}
		} while (!codigo_unico);

		funcionarios[funcionario_count++] = novo_funcionario;
		salvar_funcionarios();
		printf("Funcionário cadastrado com sucesso! Código: %d\n", novo_funcionario.codigo);
}

void buscar_funcionario_por_codigo(char* termo_busca) {
		int codigo_busca;
		sscanf(termo_busca, "%d", &codigo_busca);

		bool encontrado = false;
		for (int i = 0; i < funcionario_count; i++) {
				if (funcionarios[i].codigo == codigo_busca || strstr(funcionarios[i].nome, termo_busca) != NULL) {
						printf("Código: %d\n", funcionarios[i].codigo);
						printf("Nome: %s\n", funcionarios[i].nome);
						printf("Cargo: %s\n", funcionarios[i].cargo);
						printf("Telefone: %s\n", funcionarios[i].telefone);
						printf("Salário: R$%.2f\n", funcionarios[i].salario);
						encontrado = true;
				}
		}

		if (!encontrado) {
				printf("Funcionário não encontrado.\n");
		}
}
