#include <cstdlib>
#include <iostream>
#include <utility>
#include <cstring>
#include "board.h"

int dx[] = {0, 1, 1, 1};
int dy[] = {1, 0, -1, 1};

bool within_board(int x, int y) {
    return (x >= 0 && y >= 0 && x < 10 && y < 10);
}

Board::Board() {
    memset(_board, '.', 100 * sizeof(char));
    _gameStatus = in_progress;
    _emptyCells = 100;
}

void Board::move(int x, int y, char sign) {
    _board[x][y] = sign;
    _emptyCells--;
    if (!_emptyCells) _gameStatus = draw;
    for (int i = 0; i < 4; ++i)
        if (row_len(x, y, -dx[i], -dy[i]) + row_len(x, y, dx[i], dy[i]) > 5) {
            if (sign == 'O') _gameStatus = O_wins;
            else _gameStatus = X_wins;
            return;
        }
}

status Board::isWin() {
    return _gameStatus;
}

bool Board::canMove(int x, int y) {
    return within_board(x, y) && _board[x][y] == '.';
}

char Board::getCell(int x, int y) {
    return _board[x][y];
}

int Board::row_len(int x, int y, int dir_x, int dir_y) {
    int set_x = x;
    int set_y = y;
    int cnt = 0;
    while (within_board(x, y) && cnt < 5 && _board[x][y] == _board[set_x][set_y]) {
        x += dir_x;
        y += dir_y;
        ++cnt;
    }
    return cnt;
}

