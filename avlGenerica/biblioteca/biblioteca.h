#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H


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

typedef struct pilha {
    Data dataEmprestimo;
    Data dataDevolucao;
    char locatario[50];
    struct pilha *proximo;
} Pilha;
/**
 * @brief Estrutura de uma Pilha.
 * * Esta estrutura armazena as informações do locatário do livro, contendo seu nome,
 * a data de empréstimo e devolução e um ponteiro do tipo Pilha para o encadeamento.
 */

typedef struct livro {
    char nomeLivro[200];
    char nomeAutor[200];
    int edicao;
    char editora[50];
    int anoLancamento;
    int status;
    Pilha *emprestimo;
} Livro;
/**
 * @brief Estrutura de um Livro.
 * * Esta estrutura armazena todas as informações necessária de um livro, desde
 * o seu nome até uma Pilha referente ao histórico de empréstimo.
 */

Pilha *criaNoPilha();
/**
 * @brief Aloca um nó de forma dinâmica uma instância composta de setsete informações.
 */

Pilha *insereNoPilha(Pilha *pilha, Data emprestimo, Data devolucao, char *locatario);
/**
 * @brief Insere um nó na Pilha.
 * @param emprestimo Instância do tipo Data, contendo três valores inteiros para a data de empréstimo.
 * @param devolucao Instância do tipo Data, contendo três valores inteiros para a data de devolução.
 * @param pilha Ponteiro do tipo No para a Pilha como um todo.
 * @param valor Ponteiro do tipo void para um dado genérico.
 */

int comparaLivroCompleto(void *raiz, void *valor);
/**
 * @brief Assinatura da função callback "comparaDado" do pacote AVL, responsável por comparar se o valor é maior, menor ou igual.
 * Ela realiza a comparação com base nas três hierarquias: Nome do Livro -> Nome do Autor -> Edição.
 * @param raiz Ponteiro do tipo No, representa o ponteiro da árvore como um todo.  
 * @param valor Ponteiro do tipo void para um dado genérico.
 */

int comparaLivroParcial(void *raiz, void *valor);
/**
 * @brief Assinatura da função callback "comparaDado" do pacote AVL, responsável por comparar se o valor é maior, menor ou igual.
 * Ela realiza a comparação com base nas duas hierarquias: Nome do Livro -> Nome do Autor.
 * @param raiz Ponteiro do tipo No, representa o ponteiro da árvore como um todo.  
 * @param valor Ponteiro do tipo void para um dado genérico.
 */

void imprimeExistencia(void *valor);
/**
 * @brief Assinatura da função callback "imprimeAlerta" do pacote AVL, responsável por imprimir uma mensagem de erro no
 * caso de valores iguais presentes na árvore AVL.
 * @param valor Ponteiro do tipo void para um dado genérico.
 */

void liberaLivro(void *valor);
/**
 * @brief Assinatura da função callback "liberaDado" do pacote AVL, responsável por liberar a memória alocada do tipo Livro.
 * @param valor Ponteiro do tipo void para um dado genérico.
 */

void imprimeLivroCompleto(void *valor);
/**
 * @brief Assinatura da função callback "imprimeDado" do pacote AVL, responsável por imprimir o dado do tipo Livro.
 * @param valor Ponteiro do tipo void para um dado genérico.
 */

int verificaData(int dia, int mes, int ano);
/**
 * @brief Responsável pelo tratamento da entrada de datas.
 * @param dia Variável do tipo int na qual armazena o dia num intervalo de 1 à 31.
 * @param mes Variável do tipo int na qual armazena o mes num intervalo de 1 à 12.
 * @param ano Variável do tipo int na qual armazena o dia apenas em valores inteiros.
 */

void converteMinuscula(char *vetor, int tamanho);
/**
 * @brief Responsável pela conversão de cada caractere de uma string para minúscula.
 * @param vetor Ponteiro do tipo char para uma string.
 * @param tamanho Variável do tipo int na qual armazena o tamanho da string.
 */

#endif