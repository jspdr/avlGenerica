all: estoque biblioteca

estoque: main_estoque.o estoque.o avl.o
	gcc -o executavelEstoque main_estoque.o estoque.o avl.o

main_estoque.o: estoque/main.c
	gcc -c estoque/main.c -o main_estoque.o

estoque.o: estoque/estoque.c
	gcc -c estoque/estoque.c -o estoque.o

biblioteca: main_biblioteca.o biblioteca.o avl.o
	gcc -o prog_biblioteca main_biblioteca.o biblioteca.o avl.o

main_biblioteca.o: biblioteca/main.c
	gcc -c biblioteca/main.c -o main_biblioteca.o

biblioteca.o: biblioteca/biblioteca.c
	gcc -c biblioteca/biblioteca.c -o biblioteca.o

avl.o: AVL.c
	gcc -c AVL.c -o avl.o

run_estoque: estoque
	valgrind --leak-check=full ./executavelEstoque

run_bilbioteca: biblioteca
	valgrind --leak-check=full ./executavelBiblioteca

clean:
	rm -f *.o prog_estoque prog_biblioteca
