#include <iostream>
#include "view.h"

using std::cin;
using std::cout;

char players[2] = {'O', 'X'};

View::View(Board& board): board(board) {
}

void View::showBoard() {
    cout << '\n';
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
            cout << board.getCell(i, j);
        cout << '\n';
    }
}

void View::doGameCycle(bool silent) {
    int cur = 0;
    while (board.isWin() == in_progress) {
        if (!silent) {
            showBoard();
        }
        cout << players[cur] << " move: ";
        int x, y;
        cin >> x >> y;
        while (!(x == -1 && y == -1) && !board.canMove(x, y)) {
            cout << "Bad move!\n";
            cout << players[cur] << " move: ";
            cin >> x >> y;
        }
        if (x == -1 && y == -1)
            break;
        board.move(x, y, players[cur]);
        cur = 1 - cur;
    }
    if (board.isWin() == O_wins) {
        showBoard();
        cout << "O wins!\n";
    }
    else if (board.isWin() == X_wins) {
        showBoard();
        cout << "X wins!\n";
    }
    else if (board.isWin() == draw) {
        showBoard();
        cout << "Draw.\n";
    }
}

