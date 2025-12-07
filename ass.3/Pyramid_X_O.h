#ifndef PYRAMID_X_O_H
#define PYRAMID_X_O_H

#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>

/**
 * @brief Pyramid Tic-Tac-Toe Board.
 * * A variation of Tic-Tac-Toe played on a pyramid shape.
 * Row 0: 1 cell (index 2)
 * Row 1: 3 cells (indices 1, 2, 3)
 * Row 2: 5 cells (indices 0 to 4)
 */
template <typename T>
class Pyramid_Board : public Board<T> {
public:
    /**
     * @brief Constructor to initialize a 3x5 board.
     */
    Pyramid_Board();

    /**
     * @brief Updates the board with a move.
     * Validates if the move is within the pyramid structure.
     * @return true if valid, false otherwise.
     */
    bool update_board(Move<T>* move) override;

    /**
     * @brief Checks if a player has won.
     * Checks horizontal, vertical, and diagonal lines in the pyramid.
     */
    bool is_win(Player<T>* p) override;

    /**
     * @brief Checks if game is a draw (9 moves and no winner).
     */
    bool is_draw(Player<T>* p) override;

    /**
     * @brief Checks if game is over.
     */
    bool game_is_over(Player<T>* p) override;

    /**
     * @brief Lose condition (Not used in this game).
     */
    bool is_lose(Player<T>* p) override;
};

#endif