CFLAGS = -Wall -Werror

all: bin pose_db

bin:
	mkdir -p bin

pose_db: bin/main.o bin/clist.o
	gcc $(CFLAGS) -o pose_db -fno-builtin bin/main.o bin/clist.o

bin/main.o: src/main.c include/clist.h
	gcc $(CFLAGS) -c -I "include" -fno-builtin -o bin/main.o src/main.c

bin/clist.o: src/clist.c include/clist.h
	gcc $(CFLAGS) -c -I "include" -fno-builtin -o bin/clist.o src/clist.c

clean:
	rm -rf bin pose_db
