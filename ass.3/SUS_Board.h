// SUS_Board.h
#ifndef SUS_BOARD_H
#define SUS_BOARD_H

#include <array>

class SUS_Board {
private:
    std::array<std::array<char, 3>, 3> grid;

    static bool inRange(int r, int c);

public:
    SUS_Board();

    void reset();
    void display() const;
    bool place(int r, int c, char letter);
    bool isFull() const;

    int countSUSAtCell(int r, int c) const;
    int totalSUS() const;

    static bool validLetter(char ch);
};

void playSUS();

#endif
