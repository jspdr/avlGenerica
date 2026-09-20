#ifndef AVL_H
#define AVL_H

typedef struct no{
    struct no *esquerda;
    void *dado;
    int fb;
    struct no *direita;
} No;
/**
 * @brief Estrutura de um Nó.
 * * Esta estrutura armazena um ponteiro para um tipo de dado qualquer,
 * dois ponteiros do tipo No e uma variável do tipo inteira.
 */

typedef struct fila {
    No *noArvore;
    struct fila *prox;
} Fila;
/**
 * @brief Estrutura de uma Fila.
 * * Esta estrutura armazena um ponteiro do tipo No e um ponteiro do
 * tipo Fila.
 */

No *criaNo(void *valor);
/**
 * @brief Aloca um nó de forma dinâmica para uma árvore AVL composta de dados genéricos.
 * @param valor Ponteiro do tipo void para um dado genérico.
 */

Fila *criaNoFila(No *no); 
/**
 * @brief Aloca um nó de forma dinâmica para uma Fila composta de dados genéricos.
 * @param No Ponteiro do tipo No, representa um nó qualquer dentro da árvore AVL.
 */

Fila *insereNoFila(Fila *fila, No *valor);
/**
 * @brief Insere um nó na Fila.
 * @param fila Ponteiro do tipo No para a Fila como um todo.
 * @param valor Ponteiro do tipo void para um dado genérico.
 */


Fila *removeNoFila(Fila *fila, No **noTopo);
/**
 * @brief Remove um nó na Fila.
 * @param fila Ponteiro do tipo No para a Fila como um todo.
 * @param noTopo Ponteiro para ponteiro do tipo No, serve como auxiliar para não perder 
 * a referència do dado genérico em relação à árvore AVL.
 */

No *rotacionaDireita(No *A);
/**
 * @brief Realiza rotações e atualiza os fatores de balanceamentos, respectivamente para os 
 * casos LL(rotação simples) e LR(rotação dupla).
 * @param A Ponteiro do tipo No, representa o ponteiro "raiz" da árvore como um todo.
 * @param altura Ponteiro do tipo int, atua como uma bandeira(flag) para caso a altura mude ou não.
 */

No *rotacionaEsquerda(No *A);
/**
 * @brief Realiza rotações e atualiza os fatores de balanceamentos, respectivamente para os 
 * casos RR(rotação simples) e RL(rotação dupla).
 * @param A Ponteiro do tipo No, representa o ponteiro "raiz" da árvore como um todo.
 * @param altura Ponteiro do tipo int, atua como uma bandeira(flag) para caso a altura mude ou não.
 */

 No *buscaNoAVL(No *raiz, void *valor, int (*comparaDado) (void *, void *));
 /**
  * @brief Busca um dado genérico em toda a estrutura de árvore AVL.
  * @param raiz Ponteiro do tipo No, representa o ponteiro da árvore como um todo. 
  * @param valor Ponteiro do tipo void para um dado genérico.
  * @param comparaDado Ponteiro para a função "callback", responsável por comparar se o valor é maior, menor ou igual.
  */

No *insereNoAVL(No *raiz, void *valor, int (*comparaDado) (void *, void *), void (*imprimeAlerta) (void *) ,int *altura);
/**
 * @brief Insere um elemento na árvore AVL.
 * @param raiz Ponteiro do tipo No, representa o ponteiro da árvore como um todo. 
 * @param valor Ponteiro do tipo void para um dado genérico.
 * @param comparaDado Ponteiro para a função "callback", responsável por comparar se o valor é maior, menor ou igual.
 * @param imprimeAlerta Ponteiro para a função "callback", responsável por impimir uma mensagem de que o dado já existe na árvore.
 * conforme a hierarquia estabelecida pelo cliente.
 * @param altura Ponteiro do tipo int, atua como uma bandeira(flag) para caso a altura mude ou não.
 */

No *buscaSucessor(No *raiz);
/**
 * @brief Busca o sucessor da sub-ãrvore a direita da raiz.
 * @param raiz Ponteiro do tipo No, representa o ponteiro da árvore como um todo.  
 */

No *removeNoAVL(No *raiz, void *valor, int (*comparaDado) (void *, void *), void (*liberaDado) (void *), int *altura);
/**
 * @brief Remove um elemento na árvore AVL.
 * @param raiz Ponteiro do tipo No, representa o ponteiro da árvore como um todo. 
 * @param valor Ponteiro do tipo void para um dado genérico.
 * @param comparaDado Ponteiro para a função "callback", responsável por comparar se o valor é maior, menor ou igual.
 * conforme a hierarquia estabelecida pelo cliente.
 * @param imprimeAlerta Ponteiro para a função "callback", responsável por impimir uma mensagem de que o dado não existe na árvore.
 * @param liberaDado Ponteiro para a função "callback", responsável por liberar o TAD 
 * criado pelo cliente. 
 * @param altura Ponteiro do tipo int, atua como uma bandeira(flag) para caso a altura mude ou não.
 */

void imprimePreOrdem(No *raiz, void (*imprimeDado) (void *));
/**
 * @brief Imprime a árvore na respectiva ordem: SAE -> raiz -> SAD
 * @param raiz Ponteiro do tipo No, representa o ponteiro da árvore como um todo. 
 * @param imprimeDado Ponteiro para a função "callback", responsável por imprimir
 * o tipo de dado criado pelo cliente.
 */

void imprimeEmOrdem(No *raiz, void (*imprimeDado) (void *));
/**
 * @brief Imprime a árvore na respectiva ordem: raiz -> SAE -> SAD
 * @param raiz Ponteiro do tipo No, representa o ponteiro da árvore como um todo. 
 * @param imprimeDado Ponteiro para a função "callback", responsável por imprimir
 * o tipo de dado criado pelo cliente.
 */

void imprimePosOrdem(No *raiz, void (*imprimeDado) (void *));
/**
 * @brief Imprime a árvore na respectiva ordem: SAE -> SAD -> raiz
 * @param raiz Ponteiro do tipo No, representa o ponteiro da árvore como um todo. 
 * @param imprimeDado Ponteiro para a função "callback", responsável por imprimir
 * o tipo de dado criado pelo cliente.
 */

void imprimePorNiveis(No *raiz, void (*imprimeDado) (void *));
/**
 * @brief Imprime a árvore conforme os seus respectivos níveis(Busca em Largura), utilizando 
 * Fila como uma estrutura auxiliar. 
 * @param raiz Ponteiro do tipo No, representa o ponteiro da árvore como um todo. 
 * @param imprimeDado Ponteiro para a função "callback", responsável por imprimir
 * o tipo de dado criado pelo cliente.
 */

void imprimeFiltrado(No *raiz, void *valor, void (*imprimeDado) (void *), int (*comparaDado) (void *, void *));
/**
 * @brief Imprime a árvore em ordem de acordo com um comparativo. 
 * @param raiz Ponteiro do tipo No, representa o ponteiro da árvore como um todo. 
 * @param imprimeDado Ponteiro para a função "callback", responsável por imprimir
 * o tipo de dado criado pelo cliente.
 * @param comparaDado Ponteiro para a função "callback", responsável por comparar se o valor é maior, menor ou igual.
 */

void liberaAVL(No *raiz, void (*liberaDado) (void *));
/**
 * @brief Libera todos os elementos presentes na árvore AVL.
 * @param raiz Ponteiro do tipo No, representa o ponteiro da árvore como um todo. 
 * @param liberaDado Ponteiro para a função "callback", responsável por liberar o TAD 
 * criado pelo cliente. 
 */

#endif