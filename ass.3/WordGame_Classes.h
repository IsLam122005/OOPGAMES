#ifndef WORDGAME_CLASSES_H
#define WORDGAME_CLASSES_H

#include "BoardGame_Classes.h"
#include <set>
#include <fstream>
#include <sstream>
#include <cctype>
#include <iostream>
using namespace std;

/** @class WordTae_Board
 *  @brief Word-based Tic-Tac-Toe board.
 */
class WordTae_Board : public Board<char> {
private:
    char blank_symbol = '.';
    set<string> dictionary;

    /** @brief Load dictionary file. */
    void load_dictionary(string filename);

public:
    /** @brief Constructor loads dictionary and clears board. */
    WordTae_Board();

    /** @brief Apply move. */
    bool update_board(Move<char>* move) override;

    /** @brief Check win (valid word formed). */
    bool is_win(Player<char>* player) override;

    /** @brief No losing state for this game. */
    bool is_lose(Player<char>*) override { return false; }

    /** @brief Check draw. */
    bool is_draw(Player<char>* player) override;

    /** @brief Check if game ended. */
    bool game_is_over(Player<char>* player) override;
};

/** @class WordGame_UI
 *  @brief Console UI for Word Tic-Tac-Toe.
 */
class WordGame_UI : public UI<char> {
public:
    /** @brief Constructor sets title and board size. */
    WordGame_UI() : UI("Welcome to Word Tic-Tac-Toe!", 3) {}

    /** @brief Take move from player. */
    Move<char>* get_move(Player<char>* player) override {
        int x, y;
        char c;
        cout << player->get_name();
    };
};
#endif // WORDGAME_CLASSES_H