target.out: target.o
	gcc -o target.out target.o

target.o: target.c
	gcc -c -o target.o target.c
