#pragma once
#include "board.h"

class View {
public:
	View(Board& board);
	void showBoard();
	void doGameCycle(bool silent = 0);
private:
	Board& board;
};

