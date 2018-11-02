CXXFLAGS = -Iinclude -std=c++03 -pedantic -Wall -Wextra
CXX = g++
all: main
main: bin/main.o
	mkdir -p bin
	$(CXX) -g  bin/main.o -o main $(CXXFLAGS)
bin/main.o: src/main.cpp include/my_array.h
	mkdir -p bin
	$(CXX) -g -c src/main.cpp -o bin/main.o $(CXXFLAGS)
clean:
	rm -rf bin main
