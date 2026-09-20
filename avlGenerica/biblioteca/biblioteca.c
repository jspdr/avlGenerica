#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "biblioteca.h"

Pilha *criaNoPilha() {
    Pilha *novo = (Pilha *) calloc(1, sizeof(Pilha));
    if (novo == NULL) {
        exit(1);
    }

    return novo;
}

Pilha *insereNoPilha(Pilha *pilha, Data emprestimo, Data devolucao, char *locatario) {
    Pilha *novo = criaNoPilha();
    novo->dataEmprestimo= emprestimo;
    novo->dataDevolucao = devolucao;
    strcpy(novo->locatario, locatario);

    if (pilha == NULL) {
        return novo;
    }

    novo->proximo = pilha;
    
    return novo;
}

void liberaPilha(Pilha *pilha) {
    if (pilha == NULL) {
        return;
    }

    Pilha *auxiliar = pilha;

    while(pilha != NULL) {
        pilha = pilha->proximo;
        free(auxiliar);
        auxiliar = pilha;
    }
}

Livro *criaLivro() {
    Livro *novo = (Livro *) calloc(1, sizeof(Livro));
    if (novo == NULL) {
        exit(1);
    }

    return novo;
}

int comparaLivroCompleto(void *raiz, void *valor) {
    Livro *tmpEstoque = (Livro *) raiz;
    Livro *tmpLivro = (Livro *) valor;

    if (strcmp(tmpEstoque->nomeLivro, tmpLivro->nomeLivro) > 0) {
        return 1;
    } else if (strcmp(tmpEstoque->nomeLivro, tmpLivro->nomeLivro) < 0) {
        return -1;
    } else {
        if (strcmp(tmpEstoque->nomeAutor, tmpLivro->nomeAutor) > 0) {
            return 1;
        } else if (strcmp(tmpEstoque->nomeAutor, tmpLivro->nomeAutor) < 0) {
            return -1;
        } else {
            if (tmpLivro->edicao > tmpEstoque->edicao) {
                return 1;
            } else if(tmpLivro->edicao < tmpEstoque->edicao) {
                return -1;
            } else {
                return 0;
            }
        }      
    }
}

int comparaLivroParcial(void *raiz, void *valor) {
    Livro *tmpEstoque = (Livro *) raiz;
    Livro *tmpLivro = (Livro *) valor;

    if (strcmp(tmpEstoque->nomeLivro, tmpLivro->nomeLivro) > 0) {
        return 1;
    } else if (strcmp(tmpEstoque->nomeLivro, tmpLivro->nomeLivro) < 0) {
        return -1;
    } else {
        if (strcmp(tmpEstoque->nomeAutor, tmpLivro->nomeAutor) > 0) {
            return 1;
        } else if (strcmp(tmpEstoque->nomeAutor, tmpLivro->nomeAutor) < 0) {
            return -1;
        } else {
            return 0;
        }      
    }
}
void imprimeExistencia(void *valor) {
    Livro *tmpLivro = (Livro *) valor;
    printf("O exemplar \"%s\"  ja esta cadastrado!\n", tmpLivro->nomeAutor);
    return;
}

void liberaLivro(void *valor) {
    Livro *tmpLivro = (Livro *) valor;

    liberaPilha(tmpLivro->emprestimo);
    tmpLivro->emprestimo = NULL;
    free(tmpLivro);
    tmpLivro = NULL;
    return;
}

void imprimeLivroCompleto(void *valor) {
    Livro *tmpLivro = (Livro *) valor;
    printf("\nNome do Livro: %s | ", tmpLivro->nomeLivro);
    printf("Nome do Autor: %s | ", tmpLivro->nomeAutor);
    printf("Edicao: %d | ", tmpLivro->edicao);
    printf("Editora: %s | ", tmpLivro->editora);

    if (tmpLivro->status == 0) {
        printf("Status: Disponivel");
    } else {
        printf("Status: Indisponivel");
    }
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

void converteMinuscula(char *vetor, int tamanho) {
    vetor[strcspn(vetor, "\n")] = '\0';
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = tolower(vetor[i]);
    }
}
