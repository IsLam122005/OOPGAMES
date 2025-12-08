#ifndef NUMERICAL_TIC_TAC_TOE_H
#define NUMERICAL_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <algorithm>

/**
 * @brief Numerical Tic-Tac-Toe Board
 *
 * Board class for numerical tic-tac-toe where players
 * place numbers instead of X or O.
 *
 * @tparam T The type of numbers used on the board.
 */
template <typename T>
class NumericalBoard : public Board<T> {
protected:
    std::vector<T> used_numbers; /**< Keeps track of numbers already used */

public:
    /**
     * @brief Constructs a new NumericalBoard object.
     */
    NumericalBoard();

    /**
     * @brief Updates the board with a given move.
     *
     * @param move Pointer to the Move object containing row, col, and symbol.
     * @return true if the move is valid and applied, false otherwise.
     */
    bool update_board(Move<T>* move) override;

    /**
     * @brief Checks if the given player has won.
     *
     * @param player Pointer to the Player object.
     * @return true if the player has won, false otherwise.
     */
    bool is_win(Player<T>* player) override;

    /**
     * @brief Checks if the given player has lost.
     *
     * @param player Pointer to the Player object.
     * @return true if the player has lost, false otherwise.
     */
    bool is_lose(Player<T>* player) override;

    /**
     * @brief Checks if the game is a draw.
     *
     * @param player Pointer to the Player object.
     * @return true if the game is a draw, false otherwise.
     */
    bool is_draw(Player<T>* player) override;

    /**
     * @brief Checks if the game is over (win, lose, or draw).
     *
     * @param player Pointer to the Player object.
     * @return true if the game is over, false otherwise.
     */
    bool game_is_over(Player<T>* player) override;

    /**
     * @brief Checks if a number has already been used on the board.
     *
     * @param num The number to check.
     * @return true if the number is already used, false otherwise.
     */
    bool is_number_used(T num);
};

/**
 * @brief User Interface for Numerical Tic-Tac-Toe.
 *
 * Handles player input and creation for numerical tic-tac-toe.
 *
 * @tparam T The type of numbers used on the board.
 */
template <typename T>
class NumericalUI : public UI<T> {
public:
    /**
     * @brief Constructs a new NumericalUI object.
     */
    NumericalUI();

    /**
     * @brief Gets a move from the player.
     *
     * @param player Pointer to the Player object.
     * @return Pointer to the created Move object.
     */
    Move<T>* get_move(Player<T>* player) override;

    /**
     * @brief Creates a new player.
     *
     * @param name Player's name.
     * @param symbol The number symbol of the player.
     * @param type Player type (Human or AI).
     * @return Pointer to the created Player object.
     */
    Player<T>* create_player(std::string& name, T symbol, PlayerType type) override;
};

#endif // NUMERICAL_TIC_TAC_TOE_H
