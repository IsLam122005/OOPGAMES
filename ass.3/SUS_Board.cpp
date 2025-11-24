// SUS_Board.cpp
#include "SUS_Board.h"
#include <iostream>
#include <cctype>
using namespace std;

/* COLORS */
#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"

SUS_Board::SUS_Board() {
    reset();
}

void SUS_Board::reset() {  // fill the entire grid with spaces
    for (auto& row : grid)
        for (char& c : row)
            c = ' ';
}

bool SUS_Board::inRange(int r, int c) {
    return (r >= 0 && r < 3 && c >= 0 && c < 3);
}

bool SUS_Board::validLetter(char ch) {
    ch = toupper(ch);
    return (ch == 'S' || ch == 'U');
}

void SUS_Board::display() const {
    cout << "\n  0 1 2\n";
    for (int r = 0; r < 3; r++) {
        cout << r << " ";
        for (int c = 0; c < 3; c++) {
            cout << (grid[r][c] == ' ' ? '.' : grid[r][c]);
            if (c < 2) cout << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool SUS_Board::place(int r, int c, char letter) {
    letter = toupper(letter);

    // validate move
    if (!validLetter(letter)) return false;
    if (!inRange(r, c)) return false;
    if (grid[r][c] != ' ') return false;

    grid[r][c] = letter;
    return true;
}

bool SUS_Board::isFull() const {  // checks if all cells are filled
    for (auto& row : grid)
        for (char c : row)
            if (c == ' ')
                return false;
    return true;
}

int SUS_Board::totalSUS() const { // check for "S U S"
    int count = 0;

    // rows
    for (int r = 0; r < 3; r++)
        if (grid[r][0] == 'S' && grid[r][1] == 'U' && grid[r][2] == 'S')
            count++;

    // cols
    for (int c = 0; c < 3; c++)
        if (grid[0][c] == 'S' && grid[1][c] == 'U' && grid[2][c] == 'S')
            count++;

    // diagonals
    if (grid[0][0] == 'S' && grid[1][1] == 'U' && grid[2][2] == 'S') count++;
    if (grid[0][2] == 'S' && grid[1][1] == 'U' && grid[2][0] == 'S') count++;

    return count;
}

int SUS_Board::countSUSAtCell(int r, int c) const {  // detect any "S U S" pattern by the laetst move
    int score = 0;

    auto S=[&](int rr,int cc){return inRange(rr,cc) && grid[rr][cc]=='S';};
    auto U=[&](int rr,int cc){return inRange(rr,cc) && grid[rr][cc]=='U';};

    // horizontal
    if (U(r,c)&&S(r,c-1)&&S(r,c+1)) score++;
    if (S(r,c)&&U(r,c+1)&&S(r,c+2)) score++;
    if (S(r,c)&&U(r,c-1)&&S(r,c-2)) score++;

    // vertical
    if (U(r,c)&&S(r-1,c)&&S(r+1,c)) score++;
    if (S(r,c)&&U(r+1,c)&&S(r+2,c)) score++;
    if (S(r,c)&&U(r-1,c)&&S(r-2,c)) score++;

    // main diag
    if (U(r,c)&&S(r-1,c-1)&&S(r+1,c+1)) score++;
    if (S(r,c)&&U(r+1,c+1)&&S(r+2,c+2)) score++;
    if (S(r,c)&&U(r-1,c-1)&&S(r-2,c-2)) score++;

    // anti diag
    if (U(r,c)&&S(r-1,c+1)&&S(r+1,c-1)) score++;
    if (S(r,c)&&U(r+1,c-1)&&S(r+2,c-2)) score++;
    if (S(r,c)&&U(r-1,c+1)&&S(r-2,c+2)) score++;

    return score;
}


void playSUS() {
    cout << RED <<
    "  _____ _   _  _____  \n"
    " /  ___| | | |/  ___| \n"
    " \\ `--.| |_| |\\ `--.  \n"
    "  `--. \\  _  | `--. \\ \n"
    " /\\__/ / | | |/\\__/ / \n"
    " \\____/\\_| |_/\\____/  \n"
    << RESET;

    cout << MAGENTA << "Welcome to SUS Game!\n\n" << RESET;

    SUS_Board b;
    int p = 1;
    int s1=0, s2=0;

    b.display();

    while (!b.isFull()) {
        int r,c;
        char L = (p==1?'S':'U');  // player 1 always uses S, player 2 uses U

        cout << CYAN << "Player " << p << " (" << L << ") enter row col: " << RESET;
        cin >> r >> c;

        if (!b.place(r,c,L)) {
            cout << RED << "Invalid move!\n" << RESET;
            continue;
        }

        int gain = b.countSUSAtCell(r,c);
        if (p==1) s1+=gain;
        else s2+=gain;

        b.display();
        cout << YELLOW << "Scores  P1=" << s1 << "  P2=" << s2 << RESET << "\n";

        p = (p==1?2:1);
    }

    cout << GREEN << "\nGAME OVER!\n" << RESET;
}
