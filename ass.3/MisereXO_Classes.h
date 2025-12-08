#ifndef MISERE_XO_CLASSES_H
#define MISERE_XO_CLASSES_H


#include "BoardGame_Classes.h" // If in the same directory

using namespace std;

// ======================= Misère X-O Board ==========================
class Misere_XO_Board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    Misere_XO_Board();

    bool update_board(Move<char>* move);

    // هنا اللي يعمل 3 في صف هو اللي بيخسر
    bool is_win(Player<char>* player) { return false; }

    bool is_lose(Player<char>* player);

    bool is_draw(Player<char>* player);

    bool game_is_over(Player<char>* player);
};

// ======================= Misère X-O UI ==========================
class Misere_XO_UI : public UI<char> {
public:
    Misere_XO_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type);

    Move<char>* get_move(Player<char>* player);
};

#endif
