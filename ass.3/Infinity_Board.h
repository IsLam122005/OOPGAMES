#ifndef INFINITY_BOARD_H
#define INFINITY_BOARD_H


#include <queue>
#include <utility>
#include "BoardGame_Classes.h" 
using namespace std;
class Infinity_Board : public Board<char> {
private:
    char blank_symbol = '.';
    queue<pair<int, int>> move_history;

public:
    Infinity_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};


#endif 
