#include "Pyramid_X_O.h"
#include <iostream>
using namespace std;

template <typename T>
Pyramid_Board<T>::Pyramid_Board() : Board<T>(3, 5) {
    this->n_moves = 0;
}

template <typename T>
bool Pyramid_Board<T>::update_board(Move<T>* move) {
    int x = move->get_x();
    int y = move->get_y();

        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
        return false;
    }

            if (x == 0 && y != 2) return false;

        if (x == 1 && (y < 1 || y > 3)) return false;

        if (this->board[x][y] != 0) {
        return false;
    }

        this->n_moves++;
    this->board[x][y] = move->get_symbol();
    return true;
}

template <typename T>
bool Pyramid_Board<T>::is_win(Player<T>* p) {
    T s = p->get_symbol();
        
            if (this->board[1][1] == s && this->board[1][2] == s && this->board[1][3] == s) return true;

        if (this->board[2][0] == s && this->board[2][1] == s && this->board[2][2] == s) return true;
    if (this->board[2][1] == s && this->board[2][2] == s && this->board[2][3] == s) return true;
    if (this->board[2][2] == s && this->board[2][3] == s && this->board[2][4] == s) return true;

            if (this->board[0][2] == s && this->board[1][2] == s && this->board[2][2] == s) return true;

            if (this->board[0][2] == s && this->board[1][1] == s && this->board[2][0] == s) return true;     if (this->board[0][2] == s && this->board[1][3] == s && this->board[2][4] == s) return true; 
    return false;
}

template <typename T>
bool Pyramid_Board<T>::is_draw(Player<T>* p) {
        return (this->n_moves == 9 && !is_win(p));
}

template <typename T>
bool Pyramid_Board<T>::game_is_over(Player<T>* p) {
    return is_win(p) || is_draw(p);
}
  
    template <typename T>
    bool Pyramid_Board<T>::is_lose(Player<T>* p) {
        return false;
    }
template class Pyramid_Board<char>;