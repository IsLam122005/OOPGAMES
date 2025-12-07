#ifndef DIAMONDXO_H
#define DIAMONDXO_H

#include "BoardGame_Classes.h"
#include <vector>
using namespace std;

/**
 * @brief Diamond-shaped 5x5 XO board with 13 playable cells.
 */
class DiamondBoard : public Board<char> {
    vector<vector<bool>> mask;  ///< diamond mask

public:
    /**
     * @brief Initializes board and mask.
     */
    DiamondBoard();

    /**
     * @brief Applies a move if valid.
     * @return true on success.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks win condition (needs both 3 and 4 in a row).
     */
    bool is_win(Player<char>* p) override;

    /**
     * @return Always false (no lose condition).
     */
    bool is_lose(Player<char>* p) override { return false; }

    /**
     * @brief Checks if all 13 cells are filled.
     */
    bool is_draw(Player<char>* p) override;

    /**
     * @brief Returns true if win or draw.
     */
    bool game_is_over(Player<char>* p) override;

private:
    /**
     * @brief Checks if (r,c) lies in the diamond.
     */
    bool inside_diamond(int r, int c);

    /**
     * @brief Checks if symbol has k in a row.
     */
    bool has_k_in_row(char sym, int k);
};

/**
 * @brief Text-based UI for Diamond XO.
 */
class DiamondUI : public UI<char> {
public:
    DiamondUI() : UI("Welcome to Diamond Tic-Tac-Toe!", 2) {}

    /**
     * @brief Reads user move.
     */
    Move<char>* get_move(Player<char>* p) override {
        int r, c;
        cout << p->get_name() << " (" << p->get_symbol() << "), enter row and col: ";
        cin >> r >> c;
        return new Move<char>(r, c, p->get_symbol());
    }

    /**
     * @brief Creates a player.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        return new Player<char>(name, symbol, type);
    }
};

#endif
