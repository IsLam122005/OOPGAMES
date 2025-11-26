// SUS.cpp
#include "SUS.h"
#include <iostream>
#include <cctype>
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

/* ASCII art helper (kept here per your request) */
static void print_sus_ascii() {
    cout << RED <<
    "  _____ _   _  _____  \n"
    " /  ___| | | |/  ___| \n"
    " \\ `--.| |_| |\\ `--.  \n"
    "  `--. \\  _  | `--. \\ \n"
    " /\\__/ / | | |/\\__/ / \n"
    " \\____/\\_| |_/\\____/  \n"
    << RESET;
}

/* Constructor: call base Board constructor with 3x3 */
SUS_Board::SUS_Board() : Board<char>(3, 3), scoreS(0), scoreU(0) {
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c)
            board[r][c] = ' ';
}

bool SUS_Board::inRange(int r, int c) {
    return (r >= 0 && r < 3 && c >= 0 && c < 3);
}

/* count S-U-S sequences that involve cell (r,c) */
int SUS_Board::countSUSAtCell(int r, int c) const {
    int sc = 0;
    auto S = [&](int rr,int cc){ return inRange(rr,cc) && board[rr][cc] == 'S'; };
    auto U = [&](int rr,int cc){ return inRange(rr,cc) && board[rr][cc] == 'U'; };

    // horizontal
    if (U(r,c) && S(r,c-1) && S(r,c+1)) ++sc;
    if (S(r,c) && U(r,c+1) && S(r,c+2)) ++sc;
    if (S(r,c) && U(r,c-1) && S(r,c-2)) ++sc;

    // vertical
    if (U(r,c) && S(r-1,c) && S(r+1,c)) ++sc;
    if (S(r,c) && U(r+1,c) && S(r+2,c)) ++sc;
    if (S(r,c) && U(r-1,c) && S(r-2,c)) ++sc;

    // diagonal
    if (U(r,c) && S(r-1,c-1) && S(r+1,c+1)) ++sc;
    if (S(r,c) && U(r+1,c+1) && S(r+2,c+2)) ++sc;
    if (S(r,c) && U(r-1,c-1) && S(r-2,c-2)) ++sc;

    // anti-diagonal
    if (U(r,c) && S(r-1,c+1) && S(r+1,c-1)) ++sc;
    if (S(r,c) && U(r+1,c-1) && S(r+2,c-2)) ++sc;
    if (S(r,c) && U(r-1,c+1) && S(r-2,c+2)) ++sc;

    return sc;
}

/* engine-compatible update_board */
bool SUS_Board::update_board(Move<char>* m) {
    if (!m) return false;
    int r = m->get_x();
    int c = m->get_y();
    char sym = static_cast<char>(toupper(m->get_symbol()));

    if (!inRange(r,c)) return false;
    if (board[r][c] != ' ') return false;

    // mapping: engine symbols X->S, O->U; also accept S/U directly
    char placed;
    if (sym == 'X') placed = 'S';
    else if (sym == 'O') placed = 'U';
    else if (sym == 'S' || sym == 'U') placed = sym;
    else return false;

    board[r][c] = placed;

    int gained = countSUSAtCell(r,c);
    if (gained > 0) {
        if (placed == 'S') scoreS += gained;
        else scoreU += gained;
    }

    ++n_moves;
    return true;
}

/* game ends when board full (per your rules) */
bool SUS_Board::game_is_over(Player<char>* /*player*/) {
    for (int r=0;r<rows;++r)
        for (int c=0;c<columns;++c)
            if (board[r][c] == ' ') return false;
    return true;
}

/* final outcome only when board full */
bool SUS_Board::is_win(Player<char>* player) {
    if (!player) return false;
    if (!game_is_over(player)) return false;
    char psym = player->get_symbol();
    char susSym = (psym == 'X') ? 'S' : (psym == 'O' ? 'U' : psym);
    if (susSym == 'S') return scoreS > scoreU;
    if (susSym == 'U') return scoreU > scoreS;
    return false;
}

bool SUS_Board::is_lose(Player<char>* player) {
    if (!player) return false;
    if (!game_is_over(player)) return false;
    char psym = player->get_symbol();
    char susSym = (psym == 'X') ? 'S' : (psym == 'O' ? 'U' : psym);
    if (susSym == 'S') return scoreS < scoreU;
    if (susSym == 'U') return scoreU < scoreS;
    return false;
}

bool SUS_Board::is_draw(Player<char>* /*player*/) {
    if (!game_is_over(nullptr)) return false;
    return scoreS == scoreU;
}

/* ----------------- interactive play() (menu-driven) ----------------- 
   this function handles ascii, asking for player names and types, and gameplay loop.
   it uses random moves for computer players.
*/
void SUS_Board::play() {
    print_sus_ascii();
    cout << MAGENTA << "Welcome to SUS Game!\n\n" << RESET;

    string p1, p2;
    int type1 = 1, type2 = 1;

    // ask for player S name & type
    cout << "Enter Player S name: ";
    getline(cin >> ws, p1);
    cout << "Choose Player S type:\n1. Human\n2. Computer\n";
    cin >> type1;
    while (type1 != 1 && type1 != 2) { cout << "invalid choice, enter 1 or 2: "; cin >> type1; }

    // ask for player U name & type
    cout << "Enter Player U name: ";
    getline(cin >> ws, p2);
    cout << "Choose Player U type:\n1. Human\n2. Computer\n";
    cin >> type2;
    while (type2 != 1 && type2 != 2) { cout << "invalid choice, enter 1 or 2: "; cin >> type2; }

    SUS_Board b; // fresh board for playing
    int current = 1;
    int s1 = 0, s2 = 0;

    // rng setup
    unsigned seed = (unsigned)chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 rng(seed);

    // display helper
    auto disp = [&](){
        cout << "\n  0 1 2\n";
        for (int r=0;r<3;++r){
            cout << r << " ";
            for (int c=0;c<3;++c){
                cout << (b.board[r][c]==' ' ? '.' : b.board[r][c]);
                if (c<2) cout << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    };

    disp();

    while (!b.game_is_over(nullptr)) {
        int r, c;
        char letter = (current==1 ? 'S' : 'U');
        string name = (current==1 ? p1 : p2);
        int ptype = (current==1 ? type1 : type2);

        if (ptype == 1) {
            // human
            cout << name << " (" << letter << ") enter row col: ";
            if (!(cin >> r >> c)) { cin.clear(); cin.ignore(10000,'\n'); cout << "invalid input\n"; continue; }
        } else {
            // computer: pick random empty cell
            vector<pair<int,int>> empties;
            for (int rr=0; rr<3; ++rr)
                for (int cc=0; cc<3; ++cc)
                    if (b.board[rr][cc] == ' ')
                        empties.emplace_back(rr,cc);

            if (empties.empty()) break;
            std::uniform_int_distribution<size_t> dist(0, empties.size()-1);
            auto pr = empties[dist(rng)];
            r = pr.first; c = pr.second;
            cout << "computer " << name << " plays: " << r << " " << c << "\n";
        }

        // create a move using engine Move<char>
        SUS_Move mv(r, c, letter);
        if (!b.update_board(&mv)) {
            cout << RED << "Invalid move!\n" << RESET;
            continue;
        }

        int gained = b.countSUSAtCell(r,c);
        if (gained > 0) {
            if (letter == 'S') s1 += gained;
            else s2 += gained;
        }

        disp();
        cout << YELLOW << "Score: " << p1 << "=" << s1 << "  " << p2 << "=" << s2 << RESET << "\n";

        current = (current==1 ? 2 : 1);
    }

    cout << "Game Over!\n";
    if (s1 > s2) cout << p1 << " wins!\n";
    else if (s2 > s1) cout << p2 << " wins!\n";
    else cout << "Tie!\n";
}
