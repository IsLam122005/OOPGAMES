#include <iostream>
#include <cctype>
#include "MisereXO_Classes.h"

using namespace std;

// ======================= Misère X-O Board ==========================

Misere_XO_Board::Misere_XO_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool Misere_XO_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    if (board[x][y] != blank_symbol)
        return false;

    n_moves++;
    board[x][y] = toupper(mark);
    return true;
}

bool Misere_XO_Board::is_lose(Player<char>* player) {
    char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a == sym;
        };

    // Rows + Columns
    for (int i = 0; i < 3; i++) {
        if (all_equal(board[i][0], board[i][1], board[i][2])) return true;
        if (all_equal(board[0][i], board[1][i], board[2][i])) return true;
    }

    // Diagonals
    if (all_equal(board[0][0], board[1][1], board[2][2])) return true;
    if (all_equal(board[0][2], board[1][1], board[2][0])) return true;

    return false;
}

bool Misere_XO_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_lose(player));
}

bool Misere_XO_Board::game_is_over(Player<char>* player) {
    return is_lose(player) || is_draw(player);
}

// ======================= Misère X-O UI ==========================

Misere_XO_UI::Misere_XO_UI() : UI<char>("Misère Tic Tac Toe Game", 3) {}

Player<char>* Misere_XO_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* Misere_XO_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "Enter move (0-2 0-2): ";
        cin >> x >> y;
    }
    else {
        // Random AI
        x = rand() % 3;
        y = rand() % 3;
    }
    return new Move<char>(x, y, player->get_symbol());
}
