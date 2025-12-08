#ifndef TICTACTOE4X4_H
#define TICTACTOE4X4_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

/**
 * @brief Tic-Tac-Toe 4x4 Board Class.
 * * A variation of Tic-Tac-Toe played on a 4x4 grid.
 * Each player starts with 4 tokens and moves them to get 3 in a row.
 */
template <typename T>
class TicTacToe4x4_Board : public Board<T> {
public:
    /**
     * @brief Constructor to initialize the 4x4 board.
     * Sets up the initial positions of X and O tokens.
     */
    TicTacToe4x4_Board() : Board<T>(4, 4) {
        this->n_moves = 0;

        // Player X starts at top row (0) and row (1)
        this->board[0][0] = 'X';
        this->board[0][2] = 'X';
        this->board[1][1] = 'X';
        this->board[1][3] = 'X';

        // Player O starts at bottom row (2) and row (3)
        this->board[2][0] = 'O';
        this->board[2][2] = 'O';
        this->board[3][1] = 'O';
        this->board[3][3] = 'O';
    }

    /**
     * @brief Updates the board with a player's move.
     * Moves a token from one cell to an adjacent empty cell.
     * @param move The move details (from_index, to_index, symbol).
     * @return true if move is valid, false otherwise.
     */
    bool update_board(Move<T>* move) override {
        // Move coordinates are encoded: row * 10 + col
        int from_row = move->get_x() / 10;
        int from_col = move->get_x() % 10;
        int to_row = move->get_y() / 10;
        int to_col = move->get_y() % 10;

        // Check boundaries
        if (from_row < 0 || from_row > 3 || from_col < 0 || from_col > 3 ||
            to_row < 0 || to_row > 3 || to_col < 0 || to_col > 3) {
            return false;
        }

        // Check if the source cell has the player's symbol
        if (this->board[from_row][from_col] != move->get_symbol()) {
            return false;
        }

        // Check if destination is empty
        if (this->board[to_row][to_col] != 0) {
            return false;
        }

        // Check if move is exactly 1 step (adjacent)
        if (abs(to_row - from_row) + abs(to_col - from_col) != 1) {
            return false;
        }

        // Apply the move
        this->board[from_row][from_col] = 0;
        this->board[to_row][to_col] = move->get_symbol();
        this->n_moves++;
        return true;
    }

    /**
     * @brief Checks if a player has won (3 in a row).
     */
    bool is_win(Player<T>* p) override {
        T s = p->get_symbol();

        // Check rows and columns for 3 consecutive symbols
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 2; j++) {
                if (this->board[i][j] == s && this->board[i][j + 1] == s && this->board[i][j + 2] == s) return true;
                if (this->board[j][i] == s && this->board[j + 1][i] == s && this->board[j + 2][i] == s) return true;
            }
        }

        // Check diagonals
        if (check_diagonal(s, 0, 0, 1, 1)) return true;
        if (check_diagonal(s, 0, 1, 1, 1)) return true;
        if (check_diagonal(s, 1, 0, 1, 1)) return true;
        if (check_diagonal(s, 1, 1, 1, 1)) return true;

        if (check_diagonal(s, 0, 3, 1, -1)) return true;
        if (check_diagonal(s, 0, 2, 1, -1)) return true;
        if (check_diagonal(s, 1, 3, 1, -1)) return true;
        if (check_diagonal(s, 1, 2, 1, -1)) return true;

        return false;
    }

    /**
     * @brief Helper function to check diagonal wins.
     */
    bool check_diagonal(T s, int r, int c, int dr, int dc) {
        return (this->board[r][c] == s &&
            this->board[r + dr][c + dc] == s &&
            this->board[r + 2 * dr][c + 2 * dc] == s);
    }

    bool is_draw(Player<T>* p) override { return false; }
    bool game_is_over(Player<T>* p) override { return is_win(p); }
    bool is_lose(Player<T>* p) override { return false; }
};

/**
 * @brief UI Class for 4x4 Tic-Tac-Toe.
 * Handles input for selecting a piece and moving it.
 */
template <typename T>
class TicTacToe4x4_UI : public UI<T> {
public:
    TicTacToe4x4_UI(int w) : UI<T>("Welcome to 4x4 Tic-Tac-Toe", w) {
        srand(static_cast<unsigned int>(time(0)));
    }

    /**
     * @brief Gets the player's move (Source -> Destination).
     */
    Move<T>* get_move(Player<T>* p) override {
        if (p->get_type() == PlayerType::HUMAN) {
            int r1, c1, r2, c2;
            std::cout << "\nPlayer " << p->get_name() << " (" << p->get_symbol() << ")\n";
            std::cout << "Select Piece to Move (Row Col): ";
            std::cin >> r1 >> c1;
            std::cout << "Move to (Row Col): ";
            std::cin >> r2 >> c2;
            // Return move with encoded coordinates
            return new Move<T>(r1 * 10 + c1, r2 * 10 + c2, p->get_symbol());
        }
        else {
            // Computer Random Move Logic
            std::vector<std::vector<T>> grid = p->get_board_ptr()->get_board_matrix();
            T s = p->get_symbol();

            struct Option { int r1, c1, r2, c2; };
            std::vector<Option> valid_moves;

            // Find all possible valid moves
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (grid[i][j] == s) {
                        int dr[] = { -1, 1, 0, 0 };
                        int dc[] = { 0, 0, -1, 1 };

                        for (int k = 0; k < 4; k++) {
                            int ni = i + dr[k];
                            int nj = j + dc[k];
                            if (ni >= 0 && ni < 4 && nj >= 0 && nj < 4 && grid[ni][nj] == 0) {
                                valid_moves.push_back({ i, j, ni, nj });
                            }
                        }
                    }
                }
            }

            if (!valid_moves.empty()) {
                int index = rand() % valid_moves.size();
                Option op = valid_moves[index];
                std::cout << "Computer moves from " << op.r1 << " " << op.c1 << " to " << op.r2 << " " << op.c2 << "\n";
                return new Move<T>(op.r1 * 10 + op.c1, op.r2 * 10 + op.c2, s);
            }

            return new Move<T>(-1, -1, s);
        }
    }

    Player<T>* create_player(std::string& name, T symbol, PlayerType type) override {
        return new Player<T>(name, symbol, type);
    }
};

#endif