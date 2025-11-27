#include "WordGame_Classes.h"
#include "BoardGame_Classes.h"
#include <algorithm>

void WordTae_Board::load_dictionary(string filename) {
    ifstream file(filename);
    string word;
    if (file.is_open()) {
        while (getline(file, word)) {
            if (word.length() == 3) {
                transform(word.begin(), word.end(), word.begin(), ::toupper);
                dictionary.insert(word);
            }
        }
        file.close();
        cout << "Dictionary loaded successfully. Total words: " << dictionary.size() << endl;
    } else {
        cout << "ERROR: Could not open dictionary file: " << filename << endl;
    }
}

WordTae_Board::WordTae_Board() : Board<char>(3, 3) {
    load_dictionary("dic.txt"); 
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = blank_symbol;
        }
    }
}

bool WordTae_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char symbol = move->get_symbol();
    
    if (r < 0 || r > 2 || c < 0 || c > 2 || board[r][c] != blank_symbol)
        return false;

    if (symbol != 'X' && symbol != 'O') {
        board[r][c] = toupper(symbol);
    } else {
        board[r][c] = symbol; 
    }
    
    n_moves++;
    return true;
}
bool WordTae_Board::is_win(Player<char>* player) {
    if (n_moves < 3) return false;

    for (int i = 0; i < 3; i++) {
        string word = "";
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == blank_symbol) break;
            word += toupper(board[i][j]);
        }
        if (word.length() == 3 && dictionary.count(word)) return true;
    }

    for (int j = 0; j < 3; j++) {
        string word = "";
        for (int i = 0; i < 3; i++) {
            if (board[i][j] == blank_symbol) break;
            word += toupper(board[i][j]);
        }
        if (word.length() == 3 && dictionary.count(word)) return true;
    }

    string diag1 = "";
    for (int i = 0; i < 3; i++) {
        if (board[i][i] == blank_symbol) break;
        diag1 += toupper(board[i][i]);
    }
    if (diag1.length() == 3 && dictionary.count(diag1)) return true;

    string diag2 = "";
    for (int i = 0; i < 3; i++) {
        if (board[i][2-i] == blank_symbol) break;
        diag2 += toupper(board[i][2-i]);
    }
    if (diag2.length() == 3 && dictionary.count(diag2)) return true;

    return false;
}

bool WordTae_Board::is_draw(Player<char>* player) {
    return n_moves == 9 && !is_win(player) && !is_win(player); // فحص is_win مرتين للتأكد من فوز اللاعب الآخر
}

bool WordTae_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}