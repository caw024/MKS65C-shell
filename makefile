all: shell.o main.o
	gcc shell.o main.o
run:
	./a.out
clean:
	rm -f ./a.out shell.o main.o
shell.o: shell.h shell.c
	gcc -c shell.c
main.o: main.c shell.c shell.h
	gcc -c main.c 
