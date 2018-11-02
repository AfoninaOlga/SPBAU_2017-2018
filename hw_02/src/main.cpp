#include "view.h"
#include "ncursesview.h"
#include <cstring>

int main(int argc, char** argv) {
    Board board;
    View viewBoard = View(board);
    CursesView cursesBoard = CursesView(board);
    bool silent = argc > 1 && !strcmp(argv[1], "silent");
    if (argc > 1 && !strcmp(argv[1], "curses"))
        cursesBoard.doGameCycle();
    else
        viewBoard.doGameCycle(silent);
    return 0;
}

