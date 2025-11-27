#include "FiveByFive_Classes.h"
#include "BoardGame_Classes.h"
#include <algorithm>


FiveByFive_Board::FiveByFive_Board() : Board<char>(5, 5) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            board[i][j] = blank_symbol;
        }
    }
}

bool FiveByFive_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    
    if (r < 0 || r > 4 || c < 0 || c > 4 || board[r][c] != blank_symbol)
        return false;

    board[r][c] = move->get_symbol();
    n_moves++;

    return true;
}

int FiveByFive_Board::count_triplets(char symbol) {
    int score = 0;
    int R = get_rows();
    int C = get_columns();

    for (int i = 0; i < R; i++) {
        for (int j = 0; j <= C - 3; j++) {
            if (board[i][j] == symbol && board[i][j+1] == symbol && board[i][j+2] == symbol) {
                score++;
            }
        }
    }

    for (int j = 0; j < C; j++) {
        for (int i = 0; i <= R - 3; i++) {
            if (board[i][j] == symbol && board[i+1][j] == symbol && board[i+2][j] == symbol) {
                score++;
            }
        }
    }

    for (int i = 0; i <= R - 3; i++) {
        for (int j = 0; j <= C - 3; j++) {
            if (board[i][j] == symbol && board[i+1][j+1] == symbol && board[i+2][j+2] == symbol) {
                score++;
            }
        }
    }

    for (int i = 0; i <= R - 3; i++) {
        for (int j = 2; j < C; j++) {
            if (board[i][j] == symbol && board[i+1][j-1] == symbol && board[i+2][j-2] == symbol) {
                score++;
            }
        }
    }

    return score;
}

bool FiveByFive_Board::game_is_over(Player<char>* player) {
    return n_moves == 24;
}

bool FiveByFive_Board::is_win(Player<char>* player) {
    if (game_is_over(player)) {
        char p1_symbol = player->get_symbol();
        char p2_symbol = (p1_symbol == 'X') ? 'O' : 'X';        
        int p1_score = count_triplets(p1_symbol);
        int p2_score = count_triplets(p2_symbol);

        if (p1_score > p2_score) {
            cout << "\n----------------------------------\n";
            cout << player->get_name() << " Score: " << p1_score << endl;
            cout << "Opponent Score: " << p2_score << endl;
            cout << "----------------------------------\n";
            return true;
        }
    }
    return false;
}

bool FiveByFive_Board::is_draw(Player<char>* player) {
    if (game_is_over(player)) {
        char p1_symbol = player->get_symbol();
        char p2_symbol = (p1_symbol == 'X') ? 'O' : 'X';        
        int p1_score = count_triplets(p1_symbol);
        int p2_score = count_triplets(p2_symbol);
        
        if (p1_score == p2_score) {
            cout << "\n----------------------------------\n";
            cout << "Player X Score: " << count_triplets('X') << endl;
            cout << "Player O Score: " << count_triplets('O') << endl;
            cout << "----------------------------------\n";
            return true;
        }
    }
    return false;
}
