// SUS.h
#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"
#include <array>

/*
SUS: 3x3 game where players create "S-U-S" sequences.
This header declares:
- SUS_Move (inherits Move<char>)
- SUS_Board (inherits Board<char> and implements engine virtuals)
*/

class SUS_Move : public Move<char> {
public:
    SUS_Move(int r = -1, int c = -1, char s = 'S') : Move<char>(r, c, s) {}
    virtual ~SUS_Move() = default;
};

class SUS_Board : public Board<char> {
public:
    SUS_Board();
    virtual ~SUS_Board() = default;

    // engine-required overrides
    virtual bool update_board(Move<char>* move) override;
    virtual bool is_win(Player<char>* player) override;
    virtual bool is_lose(Player<char>* player) override;
    virtual bool is_draw(Player<char>* player) override;
    virtual bool game_is_over(Player<char>* player) override;

    // interactive play entry (shows ascii + accepts input)
    static void play();

private:
    int scoreS;
    int scoreU;

    static bool inRange(int r, int c);
    int countSUSAtCell(int r, int c) const;
};

#endif // SUS_H
