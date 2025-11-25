#ifndef DIAMONDXO_H
#define DIAMONDXO_H

#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>
using namespace std;

/**
 * @brief Diamond-shaped XO Board (5x5 diamond)
 */
class DiamondBoard : public Board<char> {
    vector<vector<bool>> mask; // valid diamond cells

public:
    DiamondBoard();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_lose(Player<char>* p) override { return false; }
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;

private:
    bool inside_diamond(int r, int c);
    bool has_k_in_row(char sym, int k);
};

/**
 * @brief Simple UI for Diamond XO
 */
class DiamondUI : public UI<char> {
public:
    DiamondUI() : UI("Welcome to Diamond Tic-Tac-Toe!", 2) {}

    Move<char>* get_move(Player<char>* p) override {
        int r, c;
        cout << p->get_name() << " (" << p->get_symbol() << "), enter row and col: ";
        cin >> r >> c;
        return new Move<char>(r, c, p->get_symbol());
    }

    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        return new Player<char>(name, symbol, type);
    }
};

#endif
