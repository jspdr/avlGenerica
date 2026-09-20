# Estoque e Biblioteca - AVL Genérica

## Sobre
Trabalho ministrado na disciplina de Estrutura de Dados I na **Linguagem C** envolvendo os seguintes assuntos:
- Alocação dinâmica;
- Estrutura de AVL e Fila;
- Tipo genérico de dados;
- Uso de funções callback;
- Busca em Profundidade(DFS) e Busca em Largura(BFS).

## Pré-requisitos
- Sistema Operacional: Qualquer distribuição do Linux, de preferência que seja baseada no Ubuntu;
- GCC - GNU Compiler Collection

## Implementação 
### Sistema 1: Estoque
**1.1 - Descrição Geral:** esta aplicação tem por objetivo gerenciar o estoque de um estabelecimento comercial, utilizando obrigatoriamente a biblioteca genérica da Árvore AVL (AVL.h). A chave de busca e indexação da estrutura será o código de barras do produto, representado por um número inteiro de até 8 dígitos.

**1.2 - Estrutura de dados do Produto:**
- Código de Barras: Número inteiro (até 8 dígitos) ? Chave Primária.
- Nome do Produto: Cadeia de caracteres (string) com até 100 caracteres.
- Fabricante: Cadeia de caracteres (string) com até 100 caracteres.
- Data de Fabricação: Estrutura contendo dia, mês e ano.
- Data de Validade: Estrutura contendo dia, mês e ano.
- Quantidade em Estoque: Número inteiro não negativo.

**1.3 - Operações do Menu:** o sistema deve apresentar um menu que ofereça as seguintes funcionalidades:
1. Cadastrar Produto: Solicita o código de barras do produto.
- Se o código já existir na árvore, exibe a mensagem “Produto já cadastrado” seguida
de todos os dados do registro encontrado.
- Se o código não existir, solicita os demais dados do produto e realiza a inserção na
Árvore AVL.
2. Consultar Produto: Solicita o código de barras do produto.
- Se encontrado, exibe em tela todos os dados detalhados do produto.
- Se não encontrado, exibe a mensagem “Produto não encontrado”.
3. Remover Produto: Solicita o código de barras do produto.
- Se encontrado, exibe os dados do produto e solicita uma confirmação do usuário (Sim/Não). Se confirmado, remove o nó da Árvore AVL e executa o rebalanceamento, se necessário.
- Se não encontrado, exibe a mensagem “Erro: Produto inexistente”.
4. Exibir Estrutura da Árvore: Imprime visualmente a estrutura hierárquica da Árvore
AVL em modo texto. A exibição deve permitir a clara identificação dos nós, de seus
respectivos níveis (alturas) e de seus fatores de balanceamento.
5. Encerrar Sistema: Finaliza a execução do programa, garantindo a liberação correta
de toda a memória dinamicamente alocada.

### Sistema 2: Biblioteca
**1.1 - Descrição Geral:** esta aplicação tem por objetivo gerenciar o acervo e o histórico de empréstimos de livros de uma biblioteca, utilizando obrigatoriamente a biblioteca genérica da Árvore AVL (AVL.h). A estrutura será indexada por uma chave composta (Nome do Livro, Autor e Edição), que
deve seguir estritamente os seguintes critérios hierárquicos de ordenação e desempate:
1. Critério Principal: Nome do Livro (ordem alfabética, insensível a maiúsculas/minúsculas).
2. Primeiro Desempate: Nome do Autor (ordem alfabética, insensível a maiúsculas/minúsculas).
3. Segundo Desempate: Número da Edição (ordem numérica crescente).

**1.2 - Estrutura de dados do Livro:**
- Nome do Livro: Cadeia de caracteres (string) com até 200 caracteres.
- Nomes dos Autores: Cadeia de caracteres (string) com até 200 caracteres.
- Edição: Número inteiro positivo.
- Editora: Cadeia de caracteres (string) com até 50 caracteres.
- Ano de Lançamento: Número inteiro.
- Status: Indicador booleano ou enumerado (Disponível ou Emprestado).
- Histórico de Empréstimos: Ponteiro para uma lista encadeada (ou estrutura dinâmica equivalente) onde cada nó registra um empréstimo contendo: data de empréstimo, data de devolução e nome do locatário.

**1.3 - Operações do Menu:** o sistema deve apresentar um menu que ofereça as seguintes funcionalidades:
1. Cadastrar Livro: Solicita o nome do livro, o nome dos autores e a edição.
- Se a combinação exata desses três campos não existir na árvore, o sistema solicita os dados complementares (editora e ano de lançamento), define o status como Disponível, inicializa o histórico vazio e insere o registro na Árvore AVL.
- Se a combinação exata já existir, o sistema exibe um aviso informando que o exemplar já está cadastrado.
2. Consultar Livro: Solicita o nome do livro e o nome dos autores.
- O sistema deve buscar e listar em tela todos os exemplares que correspondam aos termos digitados, exibidos obrigatoriamente em ordem crescente de edição.
- Para cada exemplar encontrado, devem ser exibidos todos os seus dados técnicos e o status atual (Disponível ou Emprestado), omitindo-se o histórico detalhado de empréstimos.
- Se nenhum registro for encontrado, exibe uma mensagem de erro.
3. Remover Livro: Solicita o nome do livro e o nome dos autores.
- O sistema localiza e exibe todos os exemplares correspondentes encontrados na árvore, ordenados por edição.
- O usuário deve selecionar, por meio do número da edição, qual exemplar deseja remover.
- Após a seleção, o sistema solicita uma confirmação (Sim/Não). Se confirmado, remove o nó correspondente da Árvore AVL, executando o rebalanceamento da estrutura e liberando a memória associada (inclusive o histórico de empréstimos do nó).
- Se o livro não for localizado, exibe uma mensagem de erro.
4. Realizar Empréstimo: Solicita o nome do livro e o nome dos autores.
- O sistema exibe todos os exemplares correspondentes ordenados por edição.
- O usuário escolhe o exemplar desejado através do número da edição. Se o exemplar selecionado estiver com o status Emprestado, a operação é abortada com uma mensagem de alerta.
- Se estiver Disponível, o sistema solicita o nome do locatário e a data de retirada. Esses dados são inseridos no histórico do livro, e o status do exemplar é alterado para Emprestado.
5. Encerrar Sistema: Finaliza a execução do programa, garantindo a liberação de toda a
memória dinamicamente alocada para a árvore, seus nós, registros de livros e respectivas
listas de históricos.


## Organização dos Arquivos
O trabalho a ser entregue deve conter os seguintes arquivos:
- **AVL.h** e **AVL.c**: implementação estritamente genérica da Árvore AVL e suas opera-
ções de balanceamento.
- **estoque.h** e **estoque.c**: Implementação do Sistema 1 (Estoque) contendo
a função main correspondente.
- biblioteca.c e biblioteca.h: Implementação do Sistema 2 (Gerenciamento de Biblioteca) contendo a função main correspondente.
- **Makefile**: Arquivo responsável por limpar, compilar e executar o projeto.

## Instrução para execução
Como o **makefile** está implementado, siga os seguintes passos: 

1. Abra o terminal;
2. Navegue até a pasta **avlGenerica**;
3. Digite **make** para compilar;
4. Digite **make run_estoque** para executar o sistema de estoque ou digite **make run_biblioteca** para executar o sistema da biblioteca 
    
