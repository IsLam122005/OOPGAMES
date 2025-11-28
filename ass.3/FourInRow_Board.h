// FourInARow.h
#ifndef FOURINAROW_H
#define FOURINAROW_H

#include "BoardGame_Classes.h"

/*
FourInARow:
- Board is 6 rows x 7 columns.
- FourInARow_Move uses Move<char> (column in y).
- The class implements engine virtuals and a static play() to run interactively.
*/

class FourInARow_Move : public Move<char> {
public:
    FourInARow_Move(int col = -1, char s = 'X') : Move<char>(-1, col, s) {}
    virtual ~FourInARow_Move() = default;
};

class FourInARow_Board : public Board<char> {
public:
    FourInARow_Board();
    virtual ~FourInARow_Board() = default;

    virtual bool update_board(Move<char>* move) override;
    virtual bool is_win(Player<char>* player) override;
    virtual bool is_lose(Player<char>* player) override;
    virtual bool is_draw(Player<char>* player) override;
    virtual bool game_is_over(Player<char>* player) override;

    // interactive play entry
    static void play();

private:
    int lastRow;
    int lastCol;
    char lastMark;

    bool inRange(int r, int c) const;
    bool checkDirection(int r, int c, int dr, int dc, char m) const;
    bool checkWinAt(int r, int c, char m) const;
    bool boardFull() const;
};

#endif
