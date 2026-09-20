#include <stdio.h>
#include <stdlib.h>

#include "AVL.h"

No *criaNo(void *valor) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) {
        exit(1);
    }

    novo->esquerda = NULL;
    novo->dado = valor;
    novo->fb = 0;
    novo->direita = NULL;

    return novo;
}

Fila *criaNoFila(No *no) {
    Fila *novo = (Fila *) malloc(sizeof(Fila));
    if (novo == NULL) {
        exit(1);
    }

    novo->noArvore = no;
    novo->prox = NULL;

    return novo;
}

Fila *insereNoFila(Fila *fila, No *valor) {
    Fila *novo = criaNoFila(valor);
    
    if (fila == NULL) {
        return novo;
    }

    Fila *aux = fila;

    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    aux->prox = novo;

    return fila;
}

Fila *removeNoFila(Fila *fila, No **noTopo) {

    if (fila == NULL) {
        return fila;
    }

    Fila *aux = fila;
    *noTopo = fila->noArvore;

    fila = fila->prox;

    free(aux);
    aux = NULL;

    return fila;
}

No *rotacionaDireita(No *A) { 
    No *B = A->esquerda;

    if (B->fb >= 0) {
        A->esquerda = B->direita;
        B->direita = A;

        A->fb = 0;
        B->fb = 0;

        return B;
    } else {
        No *C = B->direita;
        
        B->direita = C->esquerda;
        C->esquerda = B;
        
        A->esquerda = C->direita;
        C->direita = A;
        
        if (C->fb == 1) {
            B->fb = 0;
            A->fb = -1;

        } else if (C->fb == -1) {
            A->fb = 0;
            B->fb = 1;
        } else {
            A->fb = 0;
            B->fb = 0;
        }

        C->fb = 0;
        return C;
    }
}

No *rotacionaEsquerda(No *A) {
    No *B = A->direita;
    
    if (B->fb <= 0) {
        A->direita = B->esquerda;
        B->esquerda = A;

        A->fb = 0;
        B->fb = 0;

        return B;
    } else {
        No *C = B->esquerda;

        B->esquerda = C->direita;
        C->direita = B;

        A->direita = C->esquerda;
        C->esquerda = A;

        if (C->fb == 1) {
            A->fb = 0;
            B->fb = -1;
        } else if (C->fb == -1) {
            B->fb = 0;
            A->fb = 1;
        } else {
            A->fb = 0;
            B->fb = 0;
        }
        C->fb = 0;

        return C;
    }
}

No *buscaNoAVL(No *raiz, void *valor, int (*comparaDado) (void *, void *)) {
    if (raiz == NULL) {
        return raiz;
    }
    
    if (comparaDado(raiz->dado, valor) == 0) {
        return raiz;
    } else if (comparaDado(raiz->dado, valor) < 0) {
        return buscaNoAVL(raiz->esquerda, valor, comparaDado);
    } else {
        return buscaNoAVL(raiz->direita, valor, comparaDado);
    }
}

No *insereNoAVL(No *raiz, void *valor, int (*comparaDado) (void *, void *), void (*imprimeAlerta) (void *) ,int *altura) {
    if (raiz == NULL) {
        No *novo = criaNo(valor);
        *altura = 0;
        return novo;
    }

    if (comparaDado(raiz->dado, valor) == 0) {
        imprimeAlerta(valor);
        *altura = 1;
        return raiz;
    } else if (comparaDado(raiz->dado, valor) < 0) {
        raiz->esquerda =  insereNoAVL(raiz->esquerda, valor, comparaDado, imprimeAlerta, altura);
        
        if (*altura == 0) {
            switch (raiz->fb) {
                case 1:
                    raiz = rotacionaDireita(raiz);
                    *altura = 1;
                    break;
                case 0:
                    raiz->fb = 1;
                    *altura = 0;
                    break;
                case -1:
                    raiz->fb = 0;
                    *altura = 1;
                    break;
            }
        }
    } else {
        raiz->direita = insereNoAVL(raiz->direita, valor, comparaDado, imprimeAlerta, altura);
        
        if (*altura == 0) {
            switch (raiz->fb) {
                case 1:
                    raiz->fb = 0;
                    *altura = 1;
                    break;
                case 0:
                    raiz->fb = -1;
                    *altura = 0;
                    break;
                case -1:
                    raiz = rotacionaEsquerda(raiz);
                    *altura = 1;
                    break;
            }
        }
    }
    return raiz;
}

No *buscaSucessor(No *raiz) {
    raiz = raiz->direita;

    while (raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
    }

    return raiz;
}

No *removeNoAVL(No *raiz, void *valor, int (*comparaDado) (void *, void *), void (*liberaDado) (void *), int *altura) {
    if (raiz == NULL) {
        *altura = 1;
        return raiz;
    }
    
    if (comparaDado(raiz->dado, valor) < 0) {
        raiz->esquerda =  removeNoAVL(raiz->esquerda, valor, comparaDado, liberaDado, altura);

        if (*altura == 0) {
            switch (raiz->fb) {
                case 1:
                    raiz->fb = 0;
                    *altura = 1;
                    break;
                case 0:
                    raiz->fb = -1;
                    *altura = 0;
                    break;
                case -1:
                    raiz = rotacionaDireita(raiz);
                    *altura = 1;
                    break;
            }
        }
    } else if (comparaDado(raiz->dado, valor) > 0) {
        raiz->direita = removeNoAVL(raiz->direita, valor, comparaDado, liberaDado, altura);

        if (*altura == 0) {
            switch (raiz->fb) {
                case -1:
                    raiz->fb = 0;
                    *altura = 1;
                    break;
                case 0:
                    raiz->fb = 1;
                    *altura = 0;
                    break;
                case 1:
                    raiz = rotacionaEsquerda(raiz);
                    *altura = 1;
                    break;
            }
        }
    } else {
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            *altura = 0;
            liberaDado(raiz->dado);
            free(raiz);
            raiz = NULL;
            
            return raiz;
            
        } else if (raiz->esquerda == NULL) {
            *altura = 0;
            No *auxiliar = raiz->direita;
            
            liberaDado(raiz->dado);
            free(raiz);
            raiz = NULL;
            
            return auxiliar;
        } else if (raiz->direita == NULL) {
            *altura = 0;
            No *auxiliar = raiz->esquerda;
            
            liberaDado(raiz->dado);
            free(raiz);
            raiz = NULL;

            return auxiliar;
        } else {
            No *sucessor = NULL;
            sucessor = buscaSucessor(raiz);

            raiz->direita = removeNoAVL(raiz->direita, sucessor->dado, comparaDado, liberaDado, altura);
        }

        if (*altura == 0) {
            switch (raiz->fb) {
                case -1:
                    raiz->fb = 0;
                    *altura = 1;
                    break;
                case 0:
                    raiz->fb = 1;
                    *altura = 0;
                    break;
                case 1:
                    raiz = rotacionaDireita(raiz);
                    *altura = 1;
                    break;
            }
        }
    }
    return raiz;
}

void imprimePreOrdem(No *raiz, void (*imprimeDado) (void *)) {
    if (raiz == NULL) {
        return;
    }

    imprimeDado(raiz->dado);
    imprimePreOrdem(raiz->esquerda, imprimeDado);
    imprimePreOrdem(raiz->direita, imprimeDado);
}

void imprimeEmOrdem(No *raiz, void (*imprimeDado) (void *)) {
    if (raiz == NULL) {
        return;
    }

    imprimeEmOrdem(raiz->esquerda, imprimeDado);
    imprimeDado(raiz->dado);
    imprimeEmOrdem(raiz->direita, imprimeDado);
}

void imprimeFiltrado(No *raiz, void *valor, void (*imprimeDado) (void *), int (*comparaDado) (void *, void *)) {
    if (raiz == NULL) {
        return;
    }

    imprimeFiltrado(raiz->esquerda, valor, imprimeDado, comparaDado);
    if (comparaDado(raiz->dado, valor) == 0) {
        imprimeDado(raiz->dado);
    }
    imprimeFiltrado(raiz->direita, valor, imprimeDado, comparaDado);

}


void imprimePosOrdem(No *raiz, void (*imprimeDado) (void *)) {
    if (raiz == NULL) {
        return;
    }

    imprimePosOrdem(raiz->esquerda, imprimeDado);
    imprimePosOrdem(raiz->direita, imprimeDado);
    imprimeDado(raiz->dado);
}

void imprimePorNiveis(No *raiz, void (*imprimeDado) (void *)) {
    if(raiz == NULL) {
        printf("\nA arvore esta vazia!\n\n");
        return;
    }

    Fila *filaAux = NULL;
    filaAux = insereNoFila(filaAux, raiz);

    No *atual = NULL;
    int tamAtual = 1, tamProx = 0, nivel = 1;
    

    while (filaAux != NULL) {
        filaAux = removeNoFila(filaAux, &atual);
        tamAtual--;
        
        imprimeDado(atual->dado);
        printf(" Fator de balanceamento: %d |", atual->fb);
        
        

        if (atual->esquerda != NULL) {
            tamProx++;
            filaAux = insereNoFila(filaAux, atual->esquerda);
        }

        if (atual->direita != NULL) {
            tamProx++;
            filaAux = insereNoFila(filaAux, atual->direita);
        }


        if (tamAtual == 0) {
            printf(" Nível: %d\n", nivel);
            nivel++;

            tamAtual = tamProx;

            tamProx = 0;
        }
    }
}

void liberaAVL(No *raiz, void (*liberaDado) (void *)) {
    if (raiz == NULL) {
        return;
    }

    liberaAVL(raiz->esquerda, liberaDado);
    liberaAVL(raiz->direita, liberaDado);
    
    liberaDado(raiz->dado);
    free(raiz);
    raiz = NULL;
}