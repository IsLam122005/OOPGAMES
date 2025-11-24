// FourInRow_Board.h
#ifndef FOURINROW_BOARD_H
#define FOURINROW_BOARD_H

#include <array>

class FourInRow_Board {
private:
    std::array<std::array<char,7>,6> grid;

    bool inRange(int r, int c) const;
    bool checkDirection(int r, int c, int dr, int dc, char m) const;

public:
    FourInRow_Board();

    void reset();
    void display() const;
    int drop(int col, char m);
    bool isFull() const;
    bool checkWin(int r, int c, char m) const;
};

void startFourInRow();

#endif
