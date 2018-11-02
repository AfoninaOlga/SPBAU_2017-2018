#ifndef _NCURSESVIEW_H_
#define _NCURSESVIEW_H_

#include "board.h"

class CursesView {
public:
    CursesView(Board &b);
    ~CursesView();
    void showBoard();
    void doGameCycle();
private:
    bool getInput();
    Board &_board;
    int x;
    int y;
};

#endif
