CXXFLAGS	= -Iinclude -std=c++11 -Wall -Wextra

all: empl_db

empl_db: bin/main.o bin/employees.o
	mkdir -p bin
	g++ -g  bin/main.o bin/employees.o -o empl_db $(CXXFLAGS)

bin/main.o: src/main.cpp include/employees.h
	mkdir -p bin
	g++ -g -c src/main.cpp -o bin/main.o $(CXXFLAGS)

bin/employees.o: src/employees.cpp include/employees.h
	mkdir -p bin
	g++ -g -c src/employees.cpp -o bin/employees.o $(CXXFLAGS)

clean:
	rm -r bin empl_db
