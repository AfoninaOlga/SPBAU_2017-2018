#include "boardtest.h"

void BoardTest::testGetCell1() {
    Board b;
    DO_CHECK(b.getCell(0, 0) == '.');
}

void BoardTest::testGetCell2() {
    Board b;
    b.move(9, 5, 'X');
    DO_CHECK(b.getCell(9, 5) == 'X');
}

void BoardTest::testGetCell3() {
    Board b;
    b.move(4, 2, 'O');
    DO_CHECK(b.getCell(4, 2) == 'O');
}

void BoardTest::testMove1() {
    Board b;
    b.move(4, 2, 'X');
    DO_CHECK(b.getCell(4, 2) == 'X');
}

void BoardTest::testMove2() {
    Board b;
    b.move(4, 2, 'O');
    DO_CHECK(b.getCell(4, 2) == 'O');
}

void BoardTest::testMove3() {
    Board b;
    b.move(0, 0, 'O');
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (i || j) DO_CHECK(b.getCell(i, j) == '.');
}

void BoardTest::testCanMove1() {
    Board b;
    b.move(0, 0, 'X');
    DO_CHECK(!b.canMove(0, 0));
}

void BoardTest::testCanMove2() {
    Board b;
    b.move(4, 2, 'O');
    DO_CHECK(b.canMove(0, 0));
}

void BoardTest::testCanMove3() {
    Board b;
    DO_CHECK(!b.canMove(9, 10));
}

void BoardTest::testIsWin1() {
    Board b;
    b.move(0, 0, 'O');
    b.move(0, 1, 'O');
    b.move(0, 2, 'O');
    b.move(0, 3, 'O');
    b.move(0, 5, 'O');
    DO_CHECK(b.isWin() == in_progress);
}

void BoardTest::testIsWin2() {
    Board b;
    b.move(0, 0, 'X');
    b.move(1, 1, 'X');
    b.move(2, 2, 'X');
    b.move(3, 3, 'X');
    b.move(4, 4, 'X');
    DO_CHECK(b.isWin() == X_wins);
}

void BoardTest::testIsWin3() {
    Board b;
    b.move(0, 0, 'O');
    b.move(0, 1, 'O');
    b.move(0, 2, 'O');
    b.move(0, 3, 'O');
    b.move(0, 4, 'O');
    DO_CHECK(b.isWin() == O_wins);
}

void BoardTest::testIsWin4() {
	Board b;
	char s[] = {'X', 'O'};
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			b.move(i, j, s[(i / 2 + j) % 2]);
	DO_CHECK(b.isWin() == draw);
}


void BoardTest::runAllTests() {
    testGetCell1();
    testGetCell2();
    testGetCell3();
	
    testMove1();
    testMove2();
    testMove3();
	
    testCanMove1();
    testCanMove2();
    testCanMove3();

    testIsWin1();
    testIsWin2();
    testIsWin3();
    testIsWin4();
}

