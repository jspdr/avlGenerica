#ifndef ESTOQUE_H
#define ESTOQUE_H

typedef struct data {
    int dia;
    int mes;
    int ano;
} Data;
/**
 * @brief Estrutura de uma Data.
 * * Esta estrutura armazena três variáveis do tipo inteira, respectivamente
 * para dia, mês e ano.
 */

typedef struct produto {
    int codigoBarra; 
    char nomeProduto[100];
    char nomeFabricante[100];
    Data dataFabricacao;
    Data dataValidade;
    int quantEstoque;
} Produto;
/**
 * @brief Estrutura de um Produto.
 * * Esta estrutura armazena todas as informações necessária de um produto, desde
 * o seu código de barra até a sua quantidade presente no estoque.
 */

Produto *criaProduto();
/**
 * @brief Aloca um nó de forma dinâmica uma instância composta de seis informações.
 */

int comparaProduto(void *raiz, void *valor);
/**
 * @brief Assinatura da função callback "comparaDado" do pacote AVL, responsável por comparar se o valor é maior, menor ou igual.
 * @param raiz Ponteiro do tipo No, representa o ponteiro da árvore como um todo.  
 * @param valor Ponteiro do tipo void para um dado genérico.
 */

void imprimeExistencia(void *valor);
/**
 * @brief Assinatura da função callback "imprimeAlerta" do pacote AVL, responsável por imprimir uma mensagem de erro no
 * caso de valores iguais presentes na árvore AVL.
 * @param valor Ponteiro do tipo void para um dado genérico.
 */

void liberaProduto(void *valor);
/**
 * @brief Assinatura da função callback "liberaDado" do pacote AVL, responsável por liberar a memória alocada do tipo Produto.
 * @param valor Ponteiro do tipo void para um dado genérico.
 */

 void imprimeProdutoParcial(void *valor);
/**
 * @brief Assinatura da função callback "imprimeDado" do pacote AVL, responsável por imprimir apenas o código de barra,
 * uso exclusivo para a impressão por níveis.
 * @param valor Ponteiro do tipo void para um dado genérico.
 */

void imprimeProdutoCompleto(void *valor);
/**
 * @brief Assinatura da função callback "imprimeDado" do pacote AVL, responsável por imprimir o dado do tipo Produto.
 * @param valor Ponteiro do tipo void para um dado genérico.
 */

int verificaData(int dia, int mes, int ano);
/**
 * @brief Responsável pelo tratamento da entrada de datas.
 * @param dia Variável do tipo int na qual armazena o dia num intervalo de 1 à 31.
 * @param mes Variável do tipo int na qual armazena o mes num intervalo de 1 à 12.
 * @param ano Variável do tipo int na qual armazena o dia apenas em valores inteiros.
 */

int verificaEstoque(int quantidade);
/**
 * @brief Responsável pelo tratamento da entrada da quantidade de estoques.
 * @param quantidade Variável do tipo int na qual armazena apenas valores inteiros.
 */

void converteMinuscula(char *vetor, int tamanho);
/**
 * @brief Responsável pela conversão de cada caractere de uma string para minúscula.
 * @param vetor Ponteiro do tipo char para uma string.
 * @param tamanho Variável do tipo int na qual armazena o tamanho da string.
 */

#endif