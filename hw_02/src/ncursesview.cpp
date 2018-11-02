#include "ncursesview.h"
#include <ncurses.h>

char play[2] = {'O', 'X'};

CursesView::CursesView(Board &b): _board(b) {
    x = 0;
    y = 0;
}

CursesView::~CursesView() {
    clear();
}

void CursesView::showBoard() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j)
            printw("%c ", _board.getCell(i, j));
        printw("\n");
    }
}

bool CursesView::getInput() {
    while (true) {
        move(x, y);
        switch(getch()) {
            case KEY_UP:
                if (x > 0)
                    --x;
                break;
            case KEY_DOWN:
                if (x < 9)
                    ++x;
                break;
            case KEY_LEFT:
                if (y > 1)
                   y -= 2;
                break;
            case KEY_RIGHT:
                if (y < 18)
                   y += 2;
                break;
            case 'x':
                return false;
            case ' ':
                if (_board.canMove(x, y / 2))
                     return true;
         }
    }
}

void CursesView::doGameCycle() {
    int cur = 0;
    initscr();
    noecho();
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    keypad(stdscr, true);
    showBoard();
    while (_board.isWin() == in_progress) {
        mvprintw(10, 0, "%c Move.\n", play[cur]);
        
        if (!getInput()) {
            endwin();
            return;
        }
        _board.move(x, y / 2, play[cur]);
        addch(play[cur] | COLOR_PAIR(cur + 1) | A_BOLD);
        cur = 1 - cur;
    }
    if (_board.isWin() == draw)
        mvprintw(10, 0, "Draw.\n");
    else if (_board.isWin() == O_wins)
        mvprintw(10, 0, "O wins!\n");
    else if (_board.isWin() == X_wins)
        mvprintw(10, 0, "X wins!\n");
    mvprintw(11, 0, "Press any key to quit.\n");
    getch();
    endwin();
}

