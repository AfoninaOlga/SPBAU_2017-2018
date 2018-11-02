#pragma once
#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

enum status {
    in_progress,
    O_wins,
    X_wins,
    draw
};

class  Board {
public:
    Board();
    void move(int x, int y, char sign);
    bool canMove(int x, int y);
    status isWin();
    char getCell(int x, int y);
private:
    char _board[10][10];
    status _gameStatus;
    int _emptyCells;
    int row_len(int x, int y, int dx, int dy);
};

#endif
