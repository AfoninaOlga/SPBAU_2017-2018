CXX = g++
CXXFLAGS = -Iinclude -std=c++14 -Wall -Wextra

all: main

main: bin/smoke_test.o
	mkdir -p bin
	$(CXX) -g  bin/smoke_test.o -o main $(CXXFLAGS)

bin/smoke_test.o: src/smoke_test.cpp include/linq.h
	mkdir -p bin
	$(CXX) -g -c src/smoke_test.cpp -o bin/smoke_test.o $(CXXFLAGS)

clean:
	rm -rf bin main
