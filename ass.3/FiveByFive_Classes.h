#ifndef FIVEBYFIVE_CLASSES_H
#define FIVEBYFIVE_CLASSES_H

#include "BoardGame_Classes.h"
#include <map>
#include <iostream>
using namespace std;

class FiveByFive_Board : public Board<char> {
private:
    char blank_symbol = '.';
    int count_triplets(char symbol);

public:
    FiveByFive_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; };
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

// إضافة الـ UI هنا
class FiveByFive_UI : public UI<char> {
public:
    FiveByFive_UI() : UI("Welcome to 5x5 Tic-Tac-Toe!", 3) {}

    Move<char>* get_move(Player<char>* player) override {
        int r, c;
        cout << player->get_name() << " (" << player->get_symbol() << "), enter row (0-4) and col (0-4): ";
        cin >> r >> c;
        return new Move<char>(r, c, player->get_symbol());
    }

    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        return new Player<char>(name, symbol, type);
    }
};

#endif