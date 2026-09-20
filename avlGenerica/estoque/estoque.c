#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

    return tmpProduto->codigoBarra - tmpEstoque->codigoBarra;
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

void imprimeProdutoParcial(void *valor) {
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