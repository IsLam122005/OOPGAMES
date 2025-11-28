#ifndef NUMERICAL_TIC_TAC_TOE_H
#define NUMERICAL_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class NumericalBoard : public Board<T> {
protected:
    std::vector<T> used_numbers; 

public:
    NumericalBoard();
    bool update_board(Move<T>* move) override;
    bool is_win(Player<T>* player) override;
    bool is_lose(Player<T>* player) override;
    bool is_draw(Player<T>* player) override;
    bool game_is_over(Player<T>* player) override;

    bool is_number_used(T num);
};

template <typename T>
class NumericalUI : public UI<T> {
public:
    NumericalUI();
    Move<T>* get_move(Player<T>* player) override;
    Player<T>* create_player(std::string& name, T symbol, PlayerType type) override;
};

#endif // NUMERICAL_TIC_TAC_TOE_H