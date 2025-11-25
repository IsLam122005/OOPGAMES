#include "diamondXO.h"
#include <iostream>
using namespace std;

DiamondBoard::DiamondBoard()
    : Board(5, 5)
{
    mask = {
        {0,0,1,0,0},
        {0,1,1,1,0},
        {1,1,1,1,1},
        {0,1,1,1,0},
        {0,0,1,0,0}
    };

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            board[i][j] = (mask[i][j] ? '-' : ' ');
}

bool DiamondBoard::inside_diamond(int r, int c) {
    return (r >= 0 && r < 5 && c >= 0 && c < 5 && mask[r][c]);
}

bool DiamondBoard::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char s = move->get_symbol();

    if (!inside_diamond(r, c)) return false;
    if (board[r][c] != '-') return false;

    board[r][c] = s;
    n_moves++;
    return true;
}

bool DiamondBoard::has_k_in_row(char sym, int k) {
    int dirs[4][2] = { {1,0},{0,1},{1,1},{1,-1} };

    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (board[r][c] != sym) continue;

            for (auto& d : dirs) {
                int cnt = 0;

                for (int step = 0; step < k; step++) {
                    int nr = r + d[0] * step;
                    int nc = c + d[1] * step;

                    if (!inside_diamond(nr, nc)) break;
                    if (board[nr][nc] == sym) cnt++;
                    else break;
                }

                if (cnt == k) return true;
            }
        }
    }
    return false;
}

bool DiamondBoard::is_win(Player<char>* p) {
    char sym = p->get_symbol();

    bool has3 = has_k_in_row(sym, 3);
    bool has4 = has_k_in_row(sym, 4);

    return has3 && has4;
}

bool DiamondBoard::is_draw(Player<char>* p) {
    return (n_moves == 13);  // عدد خانات الماسة = 13
}

bool DiamondBoard::game_is_over(Player<char>* p) {
    return is_win(p) || is_draw(p);
}
