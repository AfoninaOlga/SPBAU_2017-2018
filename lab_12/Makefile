CXX = g++
CXXFLAGS = -Iinclude -std=c++11 -Wall -Wextra

all: main

main: bin/main.o
	mkdir -p bin
	$(CXX) -g  bin/main.o -o main $(CXXFLAGS)

bin/main.o: src/main.cpp include/my_vector.h include/test_my_vector.h
	mkdir -p bin
	$(CXX) -g -c src/main.cpp -o bin/main.o $(CXXFLAGS)

clean:
	rm -rf bin main
