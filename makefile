all: shell.o
	gcc shell.o
run:
	./a.out
clean:
	rm -f ./a.out shell.o
shell.o: shell.h
	gcc -c shell.c
