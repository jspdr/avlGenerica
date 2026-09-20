
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "AVL.h"
#include "biblioteca.h"

int main () {
    setlocale(LC_ALL, "Portuguese");
    No *biblioteca = NULL, *buscaLivro = NULL;
    Livro *atual = NULL;

    int opcao = 0, altura = 0;
    

    do {
        buscaLivro = NULL;
        atual = NULL;

        printf("\n\nMenu -\n\n");
        printf("1 - Cadastrar Livro\n");
        printf("2 - Consultar Livro\n");
        printf("3 - Remover Livro\n");
        printf("4 - Realizar Empréstimo\n");
        printf("5 - Encerrar sistema\n");
        printf("\nEscolha uma das opções acima: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                atual = criaLivro();

                getchar();
                printf("\nDigite o nome do livro que deseja cadastrar: ");
                fgets(atual->nomeLivro, 200, stdin);
                converteMinuscula(atual->nomeLivro, strlen(atual->nomeLivro));

                printf("\nDigite o nome do autor de \"%s\": ", atual->nomeLivro);
                fgets(atual->nomeAutor, 200, stdin);
                converteMinuscula(atual->nomeAutor, strlen(atual->nomeAutor));
                
                printf("\nDigite o número da edição de \"%s\": ", atual->nomeLivro);
                scanf("%d", &atual->edicao);

                buscaLivro = buscaNoAVL(biblioteca, atual, comparaLivroCompleto);

                if (buscaLivro != NULL) {
                    imprimeLivroCompleto(buscaLivro->dado);
                    printf("\n\nEste exemplar já está cadastrado! Apagando todo o cadastro e abrindo o menu novamente...\n");
                    break;
                }


                getchar();
                printf("\nDigite o nome da editora: ");
                fgets(atual->editora, 50, stdin);   
                converteMinuscula(atual->editora, strlen(atual->editora));

                printf("\nDigite o ano de lançamento: ");
                scanf("%d", &atual->anoLancamento);
                if (atual->anoLancamento < 0) {
                    printf("\nAno inválido! Apagando todo o cadastro e abrindo o menu novamente...\n"); 
                }
                
                biblioteca = insereNoAVL(biblioteca, atual, comparaLivroCompleto, imprimeExistencia, &altura);
                
                break;
            case 2:
                atual = criaLivro();
                
                getchar();
                printf("\nDigite o nome do livro que deseja consultar: ");
                fgets(atual->nomeLivro, 200, stdin);
                converteMinuscula(atual->nomeLivro, strlen(atual->nomeLivro));
                
                printf("\nDigite o nome do autor de \"%s\": ", atual->nomeLivro);
                fgets(atual->nomeAutor, 200, stdin);
                converteMinuscula(atual->nomeAutor, strlen(atual->nomeAutor));
                
                
                buscaLivro = buscaNoAVL(biblioteca, atual, comparaLivroParcial);
                
                if (buscaLivro == NULL) {
                    printf("\nERRO: livro não registrado! Abrindo o menu novamente...\n");
                    break;
                }
                
                printf("\n");
                imprimeFiltrado(biblioteca, atual, imprimeLivroCompleto, comparaLivroParcial);
                printf("\n"); 

                liberaLivro(atual);
                break;
            case 3:
                char confirmaRemocao[4] = {};
                atual = criaLivro();

                getchar();
                printf("\nDigite o nome do livro que deseja remover: ");
                fgets(atual->nomeLivro, 200, stdin);
                converteMinuscula(atual->nomeLivro, strlen(atual->nomeLivro));

                printf("\nDigite o nome do autor de \"%s\": ", atual->nomeLivro);
                fgets(atual->nomeAutor, 200, stdin);
                converteMinuscula(atual->nomeAutor, strlen(atual->nomeAutor));

                
                buscaLivro = buscaNoAVL(biblioteca, atual, comparaLivroParcial);

                if (buscaLivro == NULL) {
                    printf("\nERRO: livro não registrado! Abrindo o menu novamente...\n");
                    break;
                }

                imprimeFiltrado(biblioteca, atual, imprimeLivroCompleto, comparaLivroParcial);

                printf("\n\nDigite o número da edição de \"%s\" que deseja remover: ", atual->nomeLivro);
                scanf("%d", &atual->edicao);

                buscaLivro = NULL;

                buscaLivro = buscaNoAVL(biblioteca, atual, comparaLivroCompleto);

                if (buscaLivro == NULL) {
                    printf("\nERRO: edição não registrada! Abrindo o menu novamente...\n");
                    break;
                }

                printf("\nTem certeza que deseja remover a edição %d de \"%s\"?(Sim/Não): ", atual->edicao, atual->nomeLivro);
                getchar();
                fgets(confirmaRemocao, 4, stdin);
                converteMinuscula(confirmaRemocao, strlen(confirmaRemocao));

                if (strcmp(confirmaRemocao, "sim") == 0) {
                    biblioteca = removeNoAVL(biblioteca, atual, comparaLivroCompleto, liberaLivro, &altura);
                    printf("\nLivro removido com sucesso!\n");
                } else {
                     printf("\nAbrindo o menu novamente...\n");
                }

                liberaLivro(atual);
                break;
            case 4:
                atual = criaLivro();

                getchar();
                printf("\nDigite o nome do livro que deseja consultar: ");
                fgets(atual->nomeLivro, 200, stdin);
                converteMinuscula(atual->nomeLivro, strlen(atual->nomeLivro));

                printf("\nDigite o nome do autor de \"%s\": ", atual->nomeLivro);
                fgets(atual->nomeAutor, 200, stdin);
                converteMinuscula(atual->nomeAutor, strlen(atual->nomeAutor));

                
                buscaLivro = buscaNoAVL(biblioteca, atual, comparaLivroParcial);

                if (buscaLivro == NULL) {
                    printf("\nERRO: livro não registrado! Abrindo o menu novamente...\n");
                    break;
                }

                imprimeFiltrado(biblioteca, atual, imprimeLivroCompleto, comparaLivroParcial);

                printf("\n\nDigite o número da edição de \"%s\" que deseja adquirir: ", atual->nomeLivro);
                scanf("%d", &atual->edicao);

                buscaLivro = NULL;
                buscaLivro = buscaNoAVL(biblioteca, atual, comparaLivroCompleto);

                if (buscaLivro == NULL) {
                    printf("\nErro: Edição não encontrada! Abrindo o menu novamente...\n");
                    break;
                }

                Livro *livroTmp = (Livro *) buscaLivro->dado;
                
                if (livroTmp->status == 1) {
                    printf("\nO livro \"%s\" não está disponível! Abrindo o menu novamente...", livroTmp->nomeLivro);
                    break;  
                } 

                Data emprestimoAtual = {}, devolucaoAtual = {};
                char locatarioAtual[50] = {};

                getchar();
                printf("\nDigite o nome do locatário: ");
                fgets(locatarioAtual, 50, stdin);   
                converteMinuscula(atual->editora, strlen(atual->editora));

                printf("\nDigite a data do empréstimo(dd/mm/yyyy): ");
                scanf("%d/%d/%d", &emprestimoAtual.dia, &emprestimoAtual.mes, &emprestimoAtual.ano);
                if (verificaData(emprestimoAtual.dia, emprestimoAtual.mes, emprestimoAtual.ano) == 1) {
                    printf("\nData inválida!Apagando todo o cadastro e abrindo o menu novamente...\n\n");
                    liberaLivro(atual);
                    break;
                } 

                printf("\nDigite a data da devolução(dd/mm/yyyy): ");
                scanf("%d/%d/%d", &devolucaoAtual.dia, &devolucaoAtual.mes, &devolucaoAtual.ano);
                if (verificaData(devolucaoAtual.dia, devolucaoAtual.mes, devolucaoAtual.ano) == 1) {
                    printf("\nData inválida!Apagando todo o cadastro e abrindo o menu novamente...\n\n");
                    liberaLivro(atual);
                    break;
                }

                strcpy(atual->editora, livroTmp->editora);
                atual->anoLancamento = livroTmp->anoLancamento;

                biblioteca = removeNoAVL(biblioteca, atual, comparaLivroCompleto, liberaLivro, &altura);
                atual->status = 1;
                atual->emprestimo = insereNoPilha(atual->emprestimo, emprestimoAtual, devolucaoAtual, locatarioAtual);
                biblioteca = insereNoAVL(biblioteca, atual, comparaLivroCompleto, imprimeExistencia, &altura);

                imprimeLivroCompleto(atual);
                printf(" | Data de Empréstimo: %02d/%02d/%02d | Data de Devolução: %02d/%02d/%02d", emprestimoAtual.dia,  emprestimoAtual.mes,  emprestimoAtual.ano,  devolucaoAtual.dia, devolucaoAtual.mes, devolucaoAtual.ano);
                printf("\n\nEmpréstimo realizado com sucesso!\n");

                break;
            case 5:
                printf("\nFinalizando o programa...\n");
                liberaAVL(biblioteca, liberaLivro);
                break;
            default:
                printf("\nErro: opção indisponível! Abrindo o menu novamente...\n\n");
                break;
            }

    } while(opcao != 5);

    return 0;
}


