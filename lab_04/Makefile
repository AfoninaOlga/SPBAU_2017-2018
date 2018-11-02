CFLAGS = -Wall -Werror -g

all: bin ms_cli

bin:
	mkdir -p bin

ms_cli: bin/ms_cli.o bin/mergesort.o
	gcc $(CFLAGS) -o ms_cli -fno-builtin bin/ms_cli.o bin/mergesort.o

bin/ms_cli.o: src/ms_cli.c include/mergesort.h
	gcc $(CFLAGS) -c -I "include" -fno-builtin -o bin/ms_cli.o src/ms_cli.c

bin/mergesort.o: src/mergesort.c include/mergesort.h
	gcc $(CFLAGS) -c -I "include" -fno-builtin -o bin/mergesort.o src/mergesort.c

clean:
	rm -rf bin ms_cli
