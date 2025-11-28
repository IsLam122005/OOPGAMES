// ObstaclesTTT.cpp
#include "Obstacles_TicTacToe.h"
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

/* ascii banner */
static void print_obstacles_ascii() {
    cout << CYAN <<
    "  ░██████   ░████████     ░██████   ░██████████        ░██████████░██████████░██████████\n"
    " ░██   ░██  ░██    ░██   ░██   ░██      ░██                ░██        ░██        ░██    \n"
    "░██     ░██ ░██    ░██  ░██             ░██                ░██        ░██        ░██    \n"
    "░██     ░██ ░████████    ░████████      ░██    ░██████     ░██        ░██        ░██    \n"
    "░██     ░██ ░██     ░██         ░██     ░██                ░██        ░██        ░██    \n"
    " ░██   ░██  ░██     ░██  ░██   ░██      ░██                ░██        ░██        ░██    \n"
    "  ░██████   ░█████████    ░██████       ░██                ░██        ░██        ░██    \n"
    "                                                                                        \n"
    "                                                                                        \n"
    "                                                                                        \n"
    << RESET;
}

/* constructor */
ObstaclesTTT_Board::ObstaclesTTT_Board() : Board<char>(6,6) {
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c)
            board[r][c] = '.';
}

bool ObstaclesTTT_Board::inRange(int r,int c) const {
    return r >= 0 && r < rows && c >= 0 && c < columns;
}

/* place symbol if empty (not on '#') */
bool ObstaclesTTT_Board::update_board(Move<char>* m) {
    if (!m) return false;
    int r = m->get_x();
    int c = m->get_y();
    char sym = m->get_symbol();

    if (!inRange(r,c)) return false;
    if (board[r][c] != '.') return false; // cannot place on obstacle or taken

    board[r][c] = sym;
    ++n_moves;
    return true;
}

/* check 4 in a row starting at (r,c) in direction (dr,dc) */
bool ObstaclesTTT_Board::check4At(int r,int c,int dr,int dc,char sym) const {
    for (int i = 0; i < 4; ++i) {
        int rr = r + i*dr;
        int cc = c + i*dc;
        if (!inRange(rr,cc) || board[rr][cc] != sym) return false;
    }
    return true;
}

/* any 4-in-row for player's symbol */
bool ObstaclesTTT_Board::is_win(Player<char>* player) {
    if (!player) return false;
    char sym = player->get_symbol();
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c)
            if (board[r][c] == sym)
                if (check4At(r,c,0,1,sym) || check4At(r,c,1,0,sym) ||
                    check4At(r,c,1,1,sym) || check4At(r,c,1,-1,sym))
                    return true;
    return false;
}

/*opponent has 4-in-row */
bool ObstaclesTTT_Board::is_lose(Player<char>* player) {
    if (!player) return false;
    char sym = (player->get_symbol() == 'X') ? 'O' : 'X';
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c)
            if (board[r][c] == sym)
                if (check4At(r,c,0,1,sym) || check4At(r,c,1,0,sym) ||
                    check4At(r,c,1,1,sym) || check4At(r,c,1,-1,sym))
                    return true;
    return false;
}

/* board full check */
bool ObstaclesTTT_Board::boardFull() const {
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c)
            if (board[r][c] == '.') return false;
    return true;
}

/* full and no winner */
bool ObstaclesTTT_Board::is_draw(Player<char>* /*player*/) {
    if (is_win(nullptr) || is_lose(nullptr)) return false;
    return boardFull();
}

bool ObstaclesTTT_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}

/* add up to two obstacles '#' in random empty cells */
void ObstaclesTTT_Board::add_obstacles() {
    vector<pair<int,int>> empties;
    for (int r=0;r<rows;++r)
        for (int c=0;c<columns;++c)
            if (board[r][c] == '.') empties.emplace_back(r,c);

    if (empties.empty()) return;

    unsigned seed = (unsigned)chrono::system_clock::now().time_since_epoch().count();
    static mt19937 rng(seed);

    int toAdd = min(2, (int)empties.size());
    for (int i=0;i<toAdd;++i) {
        uniform_int_distribution<int> dist(0, (int)empties.size()-1);
        int idx = dist(rng);
        auto [rr,cc] = empties[idx];
        board[rr][cc] = '#';
        empties.erase(empties.begin() + idx);
    }

    cout << YELLOW << "\nTwo new obstacles were added to the board!\n" << RESET;
}

void ObstaclesTTT_Board::play() {
    print_obstacles_ascii();
    cout << CYAN << "Welcome to Obstacles Tic-Tac-Toe (6x6, win = 4 in a row)\n\n" << RESET;

    string p1, p2;
    int type1 = 1, type2 = 1;

    // ask for players (X / O)
    cout << "Enter Player X name: ";
    getline(cin >> ws, p1);
    cout << "Choose Player X type:\n1. Human\n2. Computer\n";
    cin >> type1; while (type1!=1 && type1!=2) { cout << "invalid, enter 1 or 2: "; cin >> type1; }

    cout << "Enter Player O name: ";
    getline(cin >> ws, p2);
    cout << "Choose Player O type:\n1. Human\n2. Computer\n";
    cin >> type2; while (type2!=1 && type2!=2) { cout << "invalid, enter 1 or 2: "; cin >> type2; }

    ObstaclesTTT_Board b;

    // RNG
    unsigned seed = (unsigned)chrono::system_clock::now().time_since_epoch().count();
    static mt19937 rng(seed);

    auto disp = [&](){
        cout << "\n   ";
        for (int c=0;c<b.get_columns();++c) cout << " " << c;
        cout << "\n  " << string(b.get_columns()*2 + 3, '-') << "\n";
        for (int r=0;r<b.get_rows();++r) {
            cout << r << " |";
            for (int c=0;c<b.get_columns();++c) {
                cout << " " << b.board[r][c];
            }
            cout << "\n";
        }
        cout << "  " << string(b.get_columns()*2 + 3, '-') << "\n\n";
    };

    disp();

    int current = 1;
    int movesThisRound = 0; // when reaches 2 -> add obstacles
    while (!b.game_is_over(nullptr)) {
        string name = (current==1? p1 : p2);
        char mark = (current==1? 'X' : 'O');
        int ptype = (current==1? type1 : type2);

        int r=-1,c=-1;

        if (ptype == 1) {
            // human: read row col
            cout << name << " (" << mark << ") enter row col: ";
            if (!(cin >> r >> c)) { cin.clear(); cin.ignore(10000,'\n'); cout << "invalid input\n"; continue; }
            cin.ignore(10000,'\n'); // flush rest of line
        } else {
            // computer
            vector<pair<int,int>> empties;
            for (int rr=0; rr<b.get_rows(); ++rr)
                for (int cc=0; cc<b.get_columns(); ++cc)
                    if (b.board[rr][cc] == '.') empties.emplace_back(rr,cc);

            if (empties.empty()) break;
            uniform_int_distribution<size_t> dist(0, empties.size()-1);
            auto pr = empties[dist(rng)];
            r = pr.first; c = pr.second;
            cout << "computer " << name << " plays: " << r << " " << c << "\n";
        }

        ObstaclesTTT_Move mv(r,c,mark);
        if (!b.update_board(&mv)) { cout << RED << "Invalid move!\n" << RESET; continue; }

        disp();

        movesThisRound++;
        // after both players played once, add 2 obstacles
        if (movesThisRound >= 2) {
            b.add_obstacles();
            movesThisRound = 0;
            disp();
        }

        // check winner
        if (b.check4At(0,0,0,0,'X')) { } // no-op to avoid unused warning (we use check4At via is_win)
        if (b.is_win((current==1)? new Player<char>(name, mark, PlayerType::HUMAN) : nullptr)) {
            // we can't rely on creating an accurate Player object here for messaging; instead check via is_win by constructing a temp player
        }

        // check if current player just made a winning move
        // simpler: test is_win by creating a temp player with this symbol
        Player<char> tempP(name, mark, PlayerType::HUMAN);
        if (b.is_win(&tempP)) {
            cout << GREEN << name << " (" << mark << ") WINS!\n" << RESET;
            return;
        }

        if (b.boardFull()) {
            cout << YELLOW << "It's a draw!\n" << RESET;
            return;
        }

        current = (current==1?2:1);
    }

    cout << "Game Over!\n";
    // final result
    Player<char> pX(p1,'X',PlayerType::HUMAN), pO(p2,'O',PlayerType::HUMAN);
    if (b.is_win(&pX)) cout << GREEN << p1 << " (X) wins!\n" << RESET;
    else if (b.is_win(&pO)) cout << GREEN << p2 << " (O) wins!\n" << RESET;
    else cout << YELLOW << "Draw!\n" << RESET;
}
