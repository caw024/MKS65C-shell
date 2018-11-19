all: shell.o
	gcc shell.o
run:
	./a.out
clean:
	rm -rf ./a.out
shell.o:
	gcc -c shell.c
