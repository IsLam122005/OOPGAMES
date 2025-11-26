#include "numerical tic-tac-toe.h"
#include <iostream>
#include <set>
#include <limits>
using namespace std;

//---------------- NumericalBoard Implementation ----------------
template <typename T>
NumericalBoard<T>::NumericalBoard() : Board<T>(3, 3) {
    for (auto& row : this->board)
        fill(row.begin(), row.end(), 0);
}

// لتخزين الأرقام اللي اتلعبت
template <typename T>
bool NumericalBoard<T>::update_board(Move<T>* move) {
    static set<T> used_numbers; // ثابت لكل اللعبة
    int x = move->get_x();
    int y = move->get_y();
    T val = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3) return false;
    if (this->board[x][y] != 0) return false;
    if (used_numbers.find(val) != used_numbers.end()) return false;

    this->board[x][y] = val;
    used_numbers.insert(val);
    this->n_moves++;
    return true;
}

template <typename T>
bool NumericalBoard<T>::is_win(Player<T>* player) {
    auto& b = this->board;

    // صفوف
    for (int i = 0; i < 3; i++)
        if (b[i][0] && b[i][1] && b[i][2] && (b[i][0] + b[i][1] + b[i][2] == 15))
            return true;

    // أعمدة
    for (int i = 0; i < 3; i++)
        if (b[0][i] && b[1][i] && b[2][i] && (b[0][i] + b[1][i] + b[2][i] == 15))
            return true;

    // أقطار
    if (b[0][0] && b[1][1] && b[2][2] && (b[0][0] + b[1][1] + b[2][2] == 15))
        return true;
    if (b[0][2] && b[1][1] && b[2][0] && (b[0][2] + b[1][1] + b[2][0] == 15))
        return true;

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

//---------------- NumericalUI Implementation ----------------
template <typename T>
NumericalUI<T>::NumericalUI() : UI<T>("Welcome to Numerical Tic-Tac-Toe!", 3) {}

template <typename T>
Move<T>* NumericalUI<T>::get_move(Player<T>* player) {
    int x, y;
    T val;

    while (true) {
        // نسحب الأرقام المستخدمة من اللوحة
        set<T> used;
        auto b = player->get_board_ptr()->get_board_matrix();
        for (auto& row : b)
            for (auto& cell : row)
                if (cell != 0)
                    used.insert(cell);

        cout << player->get_name()
            << " enter row, column, value (1-9). Used:";
        for (auto u : used) cout << " " << u;
        cout << "\n> ";

        cin >> x >> y >> val;

        if (cin.fail()) {  // لو المستخدم دخل حاجة مش رقم
            cin.clear(); // تصحيح الـ stream
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input invalid! Please enter numbers only.\n";
            continue;
        }

        if (x < 0 || x >= 3 || y < 0 || y >= 3) {
            cout << "Invalid row or column! Must be 0-2.\n";
            continue;
        }

        if (val < 1 || val > 9) {
            cout << "Invalid value! Must be 1-9.\n";
            continue;
        }

        if (used.count(val)) {
            cout << "This number is already used! Try another.\n";
            continue;
        }

        return new Move<T>(x, y, val);
    }
}

template <typename T>
Player<T>* NumericalUI<T>::create_player(std::string& name, T symbol, PlayerType type) {
    return new Player<T>(name, symbol, type);
}

// Explicit template instantiation
template class NumericalBoard<int>;
template class NumericalUI<int>;
