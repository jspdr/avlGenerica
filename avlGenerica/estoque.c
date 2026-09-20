#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#include "AVL.h"
#include "estoque.h"

Produto *criaProduto() {
    Produto *novo = (Produto *) calloc(1, sizeof(Produto));
    if (novo == NULL) {
        exit(1);
    }
    return novo;
}

int comparaProduto(void *raiz, void *valor) {
    Produto *tmpEstoque = (Produto *) raiz;
    Produto *tmpProduto = (Produto *) valor;

    return tmpEstoque->codigoBarra - tmpProduto->codigoBarra;
}

void imprimeExistencia(void *valor) {
    Produto *tmpProduto = (Produto *) valor;
    printf("O produto com código \"%d\" já esta cadastrado!\n", tmpProduto->codigoBarra);
    return;
}

void liberaProduto(void *valor) {
    Produto *tmpProduto = (Produto *) valor;
    free(tmpProduto);
    tmpProduto = NULL;
    return;
}

void imprimeProduto(void *valor) {
    Produto *tmpProduto = (Produto *) valor;
    printf("Código de Barra: %d |", tmpProduto->codigoBarra);
    return;
}

void imprimeProdutoCompleto(void *valor) {
    Produto *tmpProduto = (Produto *) valor;
    printf("\nCódigo do Produto: %d\n", tmpProduto->codigoBarra);
    printf("Nome do Produto: %s", tmpProduto->nomeProduto);
    printf("Nome do fabricante: %s", tmpProduto->nomeFabricante);
    printf("Quantidade no Estoque: %d\n", tmpProduto->quantEstoque);
    printf("Data de Fabricação: %02d/%02d/%04d\n", tmpProduto->dataFabricacao.dia, tmpProduto->dataFabricacao.mes, tmpProduto->dataFabricacao.ano);
    printf("Data de Validade: %02d/%02d/%04d\n", tmpProduto->dataValidade.dia, tmpProduto->dataValidade.mes, tmpProduto->dataValidade.ano);

    return;
}

int verificaData(int dia, int mes, int ano) {
    if (dia < 0 || dia > 31) {
        return 1;
    } else if (mes < 0 || mes > 12) {
        return 1;
    } else if (ano < 0) {
        return 1;
    } else {
        return 0;
    }
} 

int verificaEstoque(int quantidade) {
    if (quantidade < 0) {
        return 1;
    }
    return 0;
}

void converteMinuscula(char *vetor, int tamanho) {
    vetor[strcspn(vetor, "\n")] = '\0';
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = tolower(vetor[i]);
    }
}

int main () {
    setlocale(LC_ALL, "Portuguese");

    No *estoque = NULL, *buscaProduto = NULL;
    Produto *atual = NULL;

    int opcao = 0, altura = 0;
    

    do {
        buscaProduto = NULL;
        atual = NULL;

        printf("\nMenu -\n\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Consultar produto\n");
        printf("3 - Remover produto\n");
        printf("4 - Exibir estrutura da árvore AVL\n");
        printf("5 - Encerrar sistema\n");
        printf("\nEscolha uma das opções acima: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                atual = criaProduto();

                printf("\nDigite o código de barras do produto que deseja cadastrar: ");
                scanf("%d", &atual->codigoBarra);  

                buscaProduto = buscaNoAVL(estoque, atual, comparaProduto);

                if (buscaProduto != NULL) {
                    imprimeProdutoCompleto(buscaProduto->dado);
                    printf("\nJá existe um produto com este código de barra! Apagando todo o cadastro e abrindo o menu novamente...\n\n");
                    liberaProduto(atual);
                    break;
                }

                getchar();
                printf("\nDigite o nome do produto: ");
                fgets(atual->nomeProduto, 100, stdin);   

                printf("\nDigite o nome do fabricante: ");
                fgets(atual->nomeFabricante, 100, stdin);  

                printf("\nDigite a data de fabricação(dd/mm/yyyy): ");
                scanf("%d/%d/%d", &atual->dataFabricacao.dia, &atual->dataFabricacao.mes, &atual->dataFabricacao.ano);
                if (verificaData(atual->dataFabricacao.dia, atual->dataFabricacao.mes, atual->dataFabricacao.ano) == 1) {
                    printf("Data inválida!\nApagando todo o cadastro e abrindo o menu novamente...\n\n");
                    liberaProduto(atual);
                    break;
                } 

                printf("\nDigite a data de validade(dd/mm/yyyy): ");
                scanf("%d/%d/%d", &atual->dataValidade.dia, &atual->dataValidade.mes, &atual->dataValidade.ano);
                if (verificaData(atual->dataValidade.dia, atual->dataValidade.mes, atual->dataValidade.ano) == 1) {
                    printf("Data inválida!\nApagando todo o cadastro e abrindo o menu novamente...\n\n");
                    liberaProduto(atual);
                    break;
                } 

                printf("\nDigite a quantidade de produtos: ");
                scanf("%d", &atual->quantEstoque);

                if(verificaEstoque(atual->quantEstoque) == 1) {
                    printf("Valor inserido inválido!\nApagando todo o cadastro e abrindo o menu novamente...\n\n");
                    liberaProduto(atual);
                    break;
                }  

                estoque = insereNoAVL(estoque, atual, comparaProduto, imprimeExistencia, &altura);
                break;
            case 2:
                atual = criaProduto();

                printf("\nDigite o código de barras do produto que deseja BUSCAR: ");
                scanf("%d", &atual->codigoBarra);  

                buscaProduto = buscaNoAVL(estoque, atual, comparaProduto);

                if (buscaProduto == NULL) {
                    printf("\nProduto NÃO foi encontrado!\nAbrindo o menu novamente...\n\n");
                    
                } else {
                    imprimeProdutoCompleto(buscaProduto->dado);
                }

                liberaProduto(atual);
                break;
            case 3:
                atual = criaProduto();

                printf("\nDigite o código de barras do produto que deseja REMOVER: ");
                scanf("%d", &atual->codigoBarra);  

                buscaProduto = buscaNoAVL(estoque, atual, comparaProduto);

                if (buscaProduto == NULL) {
                    printf("\nERRO: produto inexistente!\nAbrindo o menu novamente...\n\n");
                    break;
                } else {
                    char confirma[4] = {};
                    
                    imprimeProdutoCompleto(buscaProduto->dado);

                    printf("\nTem certeza que desaja remover o produto acima(Sim/Não)?:");
                    getchar();
                    fgets(confirma, 4, stdin);
                    converteMinuscula(confirma, 4);

                    if(strcmp(confirma, "sim") == 0) {
                        estoque = removeNoAVL(estoque, atual, comparaProduto, liberaProduto, &altura);
                        printf("Produto removido com sucesso!\nVoltando ao menu...\n\n");
                    } else {
                        printf("\nVoltando ao menu..\n\n");
                    }

                    liberaProduto(atual);
                    break;
                }
            case 4:
                imprimePorNiveis(estoque, imprimeProduto);
                break;
            case 5:
                printf("\nFinalizando o programa...\n");
                liberaAVL(estoque, liberaProduto);
                break;
            default:
                printf("\nERRO: opção indisponível! Abrindo o menu novamente...\n\n");
                break;
            }
    } while(opcao != 5);

    return 0;
}