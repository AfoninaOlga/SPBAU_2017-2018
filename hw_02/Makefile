CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11 -Iinclude -c
 
all: bin main

board_test: bin bin/board.o bin/test.o bin/boardtest.o bin/tests.o
	$(CXX) bin/board.o bin/test.o bin/boardtest.o bin/tests.o -o board_test
	
main: bin/main.o bin/board.o bin/view.o bin/ncursesview.o
	$(CXX) bin/main.o bin/board.o bin/view.o bin/ncursesview.o -lncurses -o main

bin/tests.o: test/boardtest.cpp include/boardtest.h test/test.cpp include/test.h test/tests.cpp
	$(CXX) $(CXXFLAGS) test/tests.cpp -o bin/tests.o
	
bin/test.o: test/test.cpp include/test.h
	$(CXX) $(CXXFLAGS) test/test.cpp -o bin/test.o
	
bin/boardtest.o: test/boardtest.cpp include/boardtest.h test/test.cpp include/test.h
	$(CXX) $(CXXFLAGS) test/boardtest.cpp -o bin/boardtest.o
	
bin/main.o: src/main.cpp include/board.h include/view.h
	$(CXX) $(CXXFLAGS) src/main.cpp -o bin/main.o

bin/board.o: src/board.cpp include/board.h
	$(CXX) $(CXXFLAGS)  src/board.cpp -o bin/board.o

bin/view.o: src/view.cpp include/board.h include/view.h
	$(CXX) $(CXXFLAGS)  src/view.cpp -o bin/view.o

bin/ncursesview.o:  src/ncursesview.cpp include/board.h include/ncursesview.h
	$(CXX) $(CXXFLAGS)  src/ncursesview.cpp -o bin/ncursesview.o

clean:
	rm -rf bin main board_test

bin:
	mkdir -p bin
