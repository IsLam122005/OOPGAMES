#ifndef PYRAMID_X_O_H
#define PYRAMID_X_O_H

#include "BoardGame_Classes.h"

template <typename T>
class Pyramid_Board : public Board<T> {
public:
        Pyramid_Board();

        bool update_board(Move<T>* move) override;
    bool is_win(Player<T>* p) override;
    bool is_draw(Player<T>* p) override;
    bool game_is_over(Player<T>* p) override;
    bool is_lose(Player<T>* p);
};

#include "Pyramid_X_O.cpp"

#endif 