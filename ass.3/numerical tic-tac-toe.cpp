#include "numerical tic-tac-toe.h"
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
NumericalBoard<T>::NumericalBoard() : Board<T>(3, 3) {
    for (auto& row : this->board)
        fill(row.begin(), row.end(), 0);
    used_numbers.clear();
}

template <typename T>
bool NumericalBoard<T>::is_number_used(T num) {
    return find(used_numbers.begin(), used_numbers.end(), num) != used_numbers.end();
}

template <typename T>
bool NumericalBoard<T>::update_board(Move<T>* move) {
    int x = move->get_x();
    int y = move->get_y();
    T val = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3) return false;
    if (this->board[x][y] != 0) return false;

        if (is_number_used(val)) return false;

    this->board[x][y] = val;
    used_numbers.push_back(val);
    this->n_moves++;
    return true;
}

template <typename T>
bool NumericalBoard<T>::is_win(Player<T>* player) {
    auto& b = this->board;
    
        for (int i = 0; i < 3; i++)
        if (b[i][0] && b[i][1] && b[i][2] && (b[i][0] + b[i][1] + b[i][2] == 15)) return true;

        for (int i = 0; i < 3; i++)
        if (b[0][i] && b[1][i] && b[2][i] && (b[0][i] + b[1][i] + b[2][i] == 15)) return true;

        if (b[0][0] && b[1][1] && b[2][2] && (b[0][0] + b[1][1] + b[2][2] == 15)) return true;
    if (b[0][2] && b[1][1] && b[2][0] && (b[0][2] + b[1][1] + b[2][0] == 15)) return true;

    return false;
}

template <typename T>
bool NumericalBoard<T>::is_lose(Player<T>* player) { return false; }

template <typename T>
bool NumericalBoard<T>::is_draw(Player<T>* player) {
    return this->n_moves >= 9 && !is_win(player);
}

template <typename T>
bool NumericalBoard<T>::game_is_over(Player<T>* player) {
    return is_win(player) || is_draw(player);
}

template <typename T>
NumericalUI<T>::NumericalUI() : UI<T>("Welcome to Numerical Tic-Tac-Toe!", 3) {}

template <typename T>
Move<T>* NumericalUI<T>::get_move(Player<T>* player) {
    int x, y;
    T val;

            int moves_count = 0;
        auto matrix = player->get_board_ptr()->get_board_matrix();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (matrix[i][j] != 0) moves_count++;
        }
    }

        bool isPlayer1 = (moves_count % 2 == 0);

    vector<int> allowed;
    if (isPlayer1) allowed = { 1,3,5,7,9 };     else allowed = { 2,4,6,8 };             
    NumericalBoard<T>* numBoard = dynamic_cast<NumericalBoard<T>*>(player->get_board_ptr());

    while (true) {
        cout << player->get_name() << " (" << (isPlayer1 ? "Odd" : "Even") << ") choose from: ";

                bool first = true;
        for (int a : allowed) {
            if (numBoard && !numBoard->is_number_used(a)) {
                if (!first) cout << ", ";
                cout << a;
                first = false;
            }
        }
        cout << "\nEnter row col value: ";

        cin >> x >> y >> val;

        if (cin.fail()) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Numbers only.\n"; continue;
        }

        if (x < 0 || x >= 3 || y < 0 || y >= 3) { cout << "Invalid coordinates (0-2)!\n"; continue; }

        bool is_allowed_val = false;
        for (int a : allowed) if (a == val) is_allowed_val = true;

        if (!is_allowed_val) {
            cout << "Invalid value! You must play " << (isPlayer1 ? "Odd (1,3..)" : "Even (2,4..)") << "\n";
            continue;
        }

        if (numBoard && numBoard->is_number_used(val)) {
            cout << "Number already used!\n"; continue;
        }

                        if (player->get_board_ptr()->get_board_matrix()[x][y] != 0) {
            cout << "Cell not empty!\n"; continue;
        }

        return new Move<T>(x, y, val);
    }
}

template <typename T>
Player<T>* NumericalUI<T>::create_player(std::string& name, T symbol, PlayerType type) {
    return new Player<T>(name, symbol, type);
}

template class NumericalBoard<int>;
template class NumericalUI<int>;