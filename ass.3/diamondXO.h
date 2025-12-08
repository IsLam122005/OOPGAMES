#ifndef DIAMONDXO_H
#define DIAMONDXO_H

#include "BoardGame_Classes.h"
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

/**
 * @brief Diamond-shaped 5x5 XO board with 13 playable cells.
 */
class DiamondBoard : public Board<char> {
    vector<vector<bool>> mask;  ///< diamond mask

public:
    DiamondBoard();
    /** @brief Updates the board with a player's move. */
    bool update_board(Move<char>* move) override;
    /** @brief Checks if the player has won. */
    bool is_win(Player<char>* p) override;
    /** @brief Checks if the player has lost (always false here). */
    bool is_lose(Player<char>* p) override { return false; }
    /** @brief Checks if the game is a draw for the player. */
    bool is_draw(Player<char>* p) override;
    /** @brief Checks if the game is over for the player. */
    bool game_is_over(Player<char>* p) override;
    /** @brief Checks if the given coordinates are inside the diamond. */
    bool inside_diamond(int r, int c);

private:
    bool has_k_in_row(char sym, int k);
};

/**
 * @brief Text-based UI for Diamond XO.
 */
class DiamondUI : public UI<char> {
public:
    DiamondUI() : UI("Welcome to Diamond Tic-Tac-Toe!", 2) {}

    Move<char>* get_move(Player<char>* p) override {
        // إذا الكمبيوتر، اختر خانة عشوائية صالحة
        if (p->get_type() == PlayerType::COMPUTER) {
            vector<pair<int, int>> empty_cells;
            DiamondBoard* board = dynamic_cast<DiamondBoard*>(p->get_board_ptr());
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++)
                    if (board->inside_diamond(i, j) && board->get_board_matrix()[i][j] == '-')
                        empty_cells.push_back({ i,j });

            if (empty_cells.empty()) return nullptr;

            srand(time(0));
            auto cell = empty_cells[rand() % empty_cells.size()];
            int r = cell.first;
            int c = cell.second;
            cout << p->get_name() << " (COMPUTER) chooses: " << r << " " << c << endl;
            return new Move<char>(r, c, p->get_symbol());
        }

        // اللاعب البشري: نفس الكود القديم
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
