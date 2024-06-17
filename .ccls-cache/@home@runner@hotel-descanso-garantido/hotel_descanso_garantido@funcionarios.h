#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

#include <stdio.h>

typedef struct TFuncionario {
    int cod_funcionario;
    char nome_funcionario[50];
    char telefone_funcionario[15];
    char cargo[30];
    float salario;
    int excluido; 
} Funcionario;


FILE* InicializarSistemaFuncionarios();
int LocalizarFuncionario(FILE *f, int cod_funcionario);
int GeradorCodFuncionario(FILE *f);
void CadastrarFuncionario(FILE *f);
void AlterarFuncionario(FILE *f);
void ExcluirFuncionario(FILE *f);
void ImprimirFuncionarios(FILE *f);
void PesquisarFuncionarioPorNome(FILE *f, char *nome); 
void PesquisarFuncionarioPorCodigo(FILE *f, int cod_funcionario); 
/*void limpa_buffer();*/

#endif // FUNCIONARIOS_H
