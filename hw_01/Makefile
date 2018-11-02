CFLAGS = -std=c99 -Wall -Werror

all: bin main

bin:
	mkdir -p bin

main: bin/main.o bin/bmp.o
	gcc $(CFLAGS) -o main -fno-builtin bin/main.o bin/bmp.o

bin/main.o: src/main.c include/bmp.h
	gcc $(CFLAGS) -c -I "include" -fno-builtin -o bin/main.o src/main.c

bin/bmp.o: src/bmp.c include/bmp.h
	gcc $(CFLAGS) -c -I "include" -fno-builtin -o bin/bmp.o src/bmp.c

clean:
	rm -rf bin main
