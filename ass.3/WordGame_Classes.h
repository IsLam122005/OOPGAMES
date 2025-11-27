#ifndef WORDGAME_CLASSES_H
#define WORDGAME_CLASSES_H

#include "BoardGame_Classes.h"
#include <set>
#include <fstream>
#include <sstream>
#include <cctype>
#include <iostream>
using namespace std;

class WordTae_Board : public Board<char> {
private:
    char blank_symbol = '.';
    set<string> dictionary;
    void load_dictionary(string filename);

public:
    WordTae_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; };
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

// إضافة الـ UI هنا
class WordGame_UI : public UI<char> {
public:
    WordGame_UI() : UI("Welcome to Word Tic-Tac-Toe!", 3) {}

    Move<char>* get_move(Player<char>* player) override {
        int x, y;
        char c;
        cout << player->get_name() << ", enter row (0-2), col (0-2), and character: ";
        cin >> x >> y >> c;
        return new Move<char>(x, y, toupper(c));
    }

    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        return new Player<char>(name, symbol, type);
    }
};

#endif