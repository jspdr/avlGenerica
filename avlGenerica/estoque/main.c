#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#include "../AVL.h"
#include "estoque.h"

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
                    printf("\nData inválida! Apagando todo o cadastro e abrindo o menu novamente...\n\n");
                    liberaProduto(atual);
                    break;
                } 

                printf("\nDigite a data de validade(dd/mm/yyyy): ");
                scanf("%d/%d/%d", &atual->dataValidade.dia, &atual->dataValidade.mes, &atual->dataValidade.ano);
                if (verificaData(atual->dataValidade.dia, atual->dataValidade.mes, atual->dataValidade.ano) == 1) {
                    printf("\nData inválida! Apagando todo o cadastro e abrindo o menu novamente...\n\n");
                    liberaProduto(atual);
                    break;
                } 

                printf("\nDigite a quantidade de produtos: ");
                scanf("%d", &atual->quantEstoque);

                if(verificaEstoque(atual->quantEstoque) == 1) {
                    printf("\nValor inserido inválido! Apagando todo o cadastro e abrindo o menu novamente...\n\n");
                    liberaProduto(atual);
                    break;
                }  

                estoque = insereNoAVL(estoque, atual, comparaProduto, imprimeExistencia, &altura);
                printf("\n");
                
                break;
            case 2:
                atual = criaProduto();

                printf("\nDigite o código de barras do produto que deseja BUSCAR: ");
                scanf("%d", &atual->codigoBarra);  

                buscaProduto = buscaNoAVL(estoque, atual, comparaProduto);

                if (buscaProduto == NULL) {
                    printf("\nProduto NÃO foi encontrado! Abrindo o menu novamente...\n\n");
                    
                } else {
                    imprimeProdutoCompleto(buscaProduto->dado);
                    printf("\n");
                }

                liberaProduto(atual);
                break;
            case 3:
                atual = criaProduto();

                printf("\nDigite o código de barras do produto que deseja REMOVER: ");
                scanf("%d", &atual->codigoBarra);  

                buscaProduto = buscaNoAVL(estoque, atual, comparaProduto);

                if (buscaProduto == NULL) {
                    printf("\nERRO: produto inexistente! Abrindo o menu novamente...\n\n");
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
                        printf("\nProduto removido com sucesso! Voltando ao menu...\n\n");
                    } else {
                        printf("\nVoltando ao menu...\n\n");
                    }

                    liberaProduto(atual);
                    break;
                }
            case 4:
                imprimePorNiveis(estoque, imprimeProdutoParcial);
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