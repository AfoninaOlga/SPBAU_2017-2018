#pragma once
#include "test.h"
#include "board.h"
class BoardTest : public Test {
public:
	void testGetCell1();
	void testGetCell2();
	void testGetCell3();
	void testIsWin1();
	void testIsWin2();
	void testIsWin3();
	void testIsWin4();
	void testMove1();
	void testMove2();
	void testMove3();
	void testCanMove1();
	void testCanMove2();
	void testCanMove3();
	void runAllTests();
};

