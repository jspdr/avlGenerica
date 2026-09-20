all: estoque biblioteca

estoque: estoque.o AVL.o AVL.o
	gcc -o estoque estoque.o AVL.o

estoque.o: estoque.c
	gcc -c estoque.c -Wall -Wextra -std=c99

biblioteca: biblioteca.o AVL.o o
	gcc -o biblioteca biblioteca.o AVL.o

biblioteca.o: biblioteca.c
	gcc -c biblioteca.c -Wall -Wextra -std=c99

AVL.o: AVL.c
	gcc -c AVL.c -Wall -Wextra -std=c99

run_estoque: estoque
	valgrind --leak-check=full ./estoque

run_bilbioteca: biblioteca
	valgrind --leak-check=full ./biblioteca

clean:
	rm -f *.o estoque biblioteca
