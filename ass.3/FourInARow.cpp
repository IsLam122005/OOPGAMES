// FourInARow.cpp
#include "FourInARow.h"
#include <iostream>
#include <random>
#include <chrono>
using namespace std;

/* COLORS */
#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"

/* ascii art */
static void print_four_ascii() {
    cout << RED <<
    " _  _        __  .__   __.         ___     \n"
    "| || |      |  | |  \\ |  |        /   \\    \n"
    "| || |_     |  | |   \\|  |       /  ^  \\   \n"
    "|__   _|    |  | |  . `  |      /  /_\\  \\  \n"
    "   | |      |  | |  |\\   |     /  _____  \\ \n"
    "   |_|      |__| |__| \\__|    /__/     \\__\\\n"
    << RESET;

    cout << BLUE <<
    ".______        ______    ____    __    ____ \n"
    "|   _  \\      /  __  \\   \\   \\  /  \\  /   / \n"
    "|  |_)  |    |  |  |  |   \\   \\/    \\/   /  \n"
    "|      /     |  |  |  |    \\            /   \n"
    "|  |\\  \\----.|  `--'  |     \\    /\\    /    \n"
    "| _| `._____| \\______/       \\__/  \\__/     \n"
    << RESET;
}

/* constructor */
FourInARow_Board::FourInARow_Board() : Board<char>(6,7), lastRow(-1), lastCol(-1), lastMark('\0') {
    for (int r=0;r<rows;++r)
        for (int c=0;c<columns;++c)
            board[r][c] = '.';
}

bool FourInARow_Board::inRange(int r,int c) const {
    return r>=0 && r<rows && c>=0 && c<columns;
}

/* drop logic: read column from move->get_y() and place mark at lowest empty row */
bool FourInARow_Board::update_board(Move<char>* m) {
    if (!m) return false;
    int col = m->get_y();
    char sym = m->get_symbol();

    if (col < 0 || col >= columns) return false;
    for (int r = rows-1; r >= 0; --r) {
        if (board[r][col] == '.') {
            board[r][col] = sym;
            lastRow = r;
            lastCol = col;
            lastMark = sym;
            ++n_moves;
            return true;
        }
    }
    return false;
}

bool FourInARow_Board::checkDirection(int r,int c,int dr,int dc,char m) const {
    int cnt = 1;
    int rr = r + dr, cc = c + dc;
    while (inRange(rr,cc) && board[rr][cc] == m) { cnt++; rr += dr; cc += dc; }
    rr = r - dr; cc = c - dc;
    while (inRange(rr,cc) && board[rr][cc] == m) { cnt++; rr -= dr; cc -= dc; }
    return cnt >= 4;
}

bool FourInARow_Board::checkWinAt(int r,int c,char m) const {
    return checkDirection(r,c,1,0,m) || checkDirection(r,c,0,1,m) ||
           checkDirection(r,c,1,1,m) || checkDirection(r,c,1,-1,m);
}

bool FourInARow_Board::boardFull() const {
    for (int c=0;c<columns;++c) if (board[0][c] == '.') return false;
    return true;
}

bool FourInARow_Board::is_win(Player<char>* player) {
    if (!player) return false;
    if (lastRow < 0) return false;
    return (player->get_symbol() == lastMark) && checkWinAt(lastRow, lastCol, lastMark);
}

bool FourInARow_Board::is_lose(Player<char>* player) {
    if (!player) return false;
    if (lastRow < 0) return false;
    return (player->get_symbol() != lastMark) && checkWinAt(lastRow, lastCol, lastMark);
}

bool FourInARow_Board::is_draw(Player<char>* /*player*/) {
    if (!boardFull()) return false;
    // full and no winner
    for (int r=0;r<rows;++r) for (int c=0;c<columns;++c)
        if (board[r][c] != '.' && checkWinAt(r,c,board[r][c])) return false;
    return true;
}

bool FourInARow_Board::game_is_over(Player<char>* /*player*/) {
    if (lastRow >= 0 && checkWinAt(lastRow,lastCol,lastMark)) return true;
    return boardFull();
}

/* ---------------- interactive play for menu usage ----------------
   asks for player names and types; computer plays random valid moves.
*/
void FourInARow_Board::play() {
    print_four_ascii();
    cout << MAGENTA << "Welcome to Four-In-A-Row!\n\n" << RESET;

    string p1, p2;
    int type1 = 1, type2 = 1;

    // ask for player X name & type
    cout << "Enter Player X name: ";
    getline(cin >> ws, p1);
    cout << "Choose Player X type:\n1. Human\n2. Computer\n";
    cin >> type1;
    while (type1 != 1 && type1 != 2) { cout << "invalid choice, enter 1 or 2: "; cin >> type1; }

    // ask for player O name & type
    cout << "Enter Player O name: ";
    getline(cin >> ws, p2);
    cout << "Choose Player O type:\n1. Human\n2. Computer\n";
    cin >> type2;
    while (type2 != 1 && type2 != 2) { cout << "invalid choice, enter 1 or 2: "; cin >> type2; }

    FourInARow_Board b;

    // rng setup
    unsigned seed = (unsigned)chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 rng(seed);

    auto disp = [&](){
    cout << "\n  0 1 2 3 4 5 6\n";
    for (int r = 0; r < b.get_rows(); ++r) {
        cout << r << " ";
        for (int c = 0; c < b.get_columns(); ++c)
            cout << b.board[r][c] << " ";
        cout << "\n";
    }
    cout << "\n";
    };

    disp();
    int current = 1;
    while (!b.game_is_over(nullptr)) {
        int col;
        string name = (current==1? p1 : p2);
        char mark = (current==1? 'X' : 'O');
        int ptype = (current==1 ? type1 : type2);

        if (ptype == 1) {
            cout << name << " (" << mark << ") choose column (0-6): ";
            if (!(cin >> col)) { cin.clear(); cin.ignore(10000,'\n'); cout << "invalid\n"; continue; }
        } else {
            // computer: choose random non-full column
            vector<int> cols;
            for (int c = 0; c < b.get_columns(); ++c)
                if (b.board[0][c] == '.') cols.push_back(c);
            if (cols.empty()) break;
            std::uniform_int_distribution<size_t> dist(0, cols.size()-1);
            col = cols[dist(rng)];
            cout << "computer " << name << " chooses column " << col << "\n";
        }

        FourInARow_Move mv(col, mark);
        if (!b.update_board(&mv)) { cout << RED << "Invalid move!\n" << RESET; continue; }

        disp();

        if (b.checkWinAt(b.lastRow, b.lastCol, b.lastMark)) {
            cout << GREEN << name << " wins!\n" << RESET;
            return;
        }
        if (b.boardFull()) {
            cout << YELLOW << "It's a tie!\n" << RESET;
            return;
        }
        current = (current==1?2:1);
    }
}
