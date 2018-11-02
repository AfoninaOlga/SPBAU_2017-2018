CFLAGS = -Wall -Werror

all: bin main

bin:
	mkdir -p bin

main: bin/main.o bin/clist.o bin/position.o
	gcc $(CFLAGS) -o main -fno-builtin bin/main.o bin/clist.o bin/position.o

bin/main.o: src/main.c include/position.h
	gcc $(CFLAGS) -c -I "include" -fno-builtin -o bin/main.o src/main.c

bin/clist.o: src/clist.c include/clist.h
	gcc $(CFLAGS) -c -I "include" -fno-builtin -o bin/clist.o src/clist.c
	
bin/position.o: src/clist.c include/position.h
	gcc $(CFLAGS) -c -I "include" -fno-builtin -o bin/position.o src/position.c

clean:
	rm -rf bin main
