#ifndef FIVEBYFIVE_CLASSES_H
#define FIVEBYFIVE_CLASSES_H

#include "BoardGame_Classes.h"
#include <map>
#include <iostream>
using namespace std;

/** @class FiveByFive_Board
 *  @brief 5x5 Tic-Tac-Toe board with triplet scoring.
 */
class FiveByFive_Board : public Board<char> {
private:
    char blank_symbol = '.';

    /** @brief Count symbol triplets on board. */
    int count_triplets(char symbol);

public:
    /** @brief Initializes empty 5x5 board. */
    FiveByFive_Board();

    /** @brief Apply move. */
    bool update_board(Move<char>* move) override;

    /** @brief Check win. */
    bool is_win(Player<char>* player) override;

    /** @brief No losing condition in this variant. */
    bool is_lose(Player<char>*) override { return false; }

    /** @brief Check draw state. */
    bool is_draw(Player<char>* player) override;

    /** @brief Check if game ended. */
    bool game_is_over(Player<char>* player) override;
};

/** @class FiveByFive_UI
 *  @brief Console UI for 5x5 Tic-Tac-Toe.
 */
class FiveByFive_UI : public UI<char> {
public:
    /** @brief Constructor sets game title. */
    FiveByFive_UI() : UI("Welcome to 5x5 Tic-Tac-Toe!", 3) {}

    /** @brief Take move input from player. */
    Move<char>* get_move(Player<char>* player) override {
        int r, c;
        cout << player->get_name() << " (" << player->get_symbol()
            << "), enter row (0-4) and col (0-4): ";
        cin >> r >> c;
        return new Move<char>(r, c, player->get_symbol());
    }

    /** @brief Create player object. */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        return new Player<char>(name, symbol, type);
    }
};

#endif
