#ifndef MISERE_XO_CLASSES_H
#define MISERE_XO_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @brief Misère Tic-Tac-Toe board (3x3).
 * In Misère XO: making 3 in a row means you LOSE.
 */
class Misere_XO_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Empty cell symbol

public:
    /**
     * @brief Initializes the 3x3 board.
     */
    Misere_XO_Board();

    /**
     * @brief Applies a move if valid.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief No win condition in Misère style.
     */
    bool is_win(Player<char>* player) { return false; }

    /**
     * @brief Checks if player loses (makes 3 in a row).
     */
    bool is_lose(Player<char>* player);

    /**
     * @brief Checks if board is full (draw).
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Returns true if lose or draw.
     */
    bool game_is_over(Player<char>* player);
};

/**
 * @brief Simple UI for Misère XO.
 */
class Misere_XO_UI : public UI<char> {
public:
    Misere_XO_UI();

    /**
     * @brief Creates a new player.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Reads player move from input.
     */
    Move<char>* get_move(Player<char>* player);
};

#endif
