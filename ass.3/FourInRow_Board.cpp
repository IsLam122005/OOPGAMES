// FourInRow_Board.cpp
#include "FourInRow_Board.h"
#include <iostream>
using namespace std;

/* COLORS */
#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"

FourInRow_Board::FourInRow_Board() {
    reset();
}

void FourInRow_Board::reset() {
    for (auto &row : grid)
        for (char &c : row)
            c = '.';
}

bool FourInRow_Board::inRange(int r, int c) const {
    return (r >= 0 && r < 6 && c >= 0 && c < 7);
}

void FourInRow_Board::display() const {
    cout << "\n  0 1 2 3 4 5 6\n";
    for (int r = 0; r < 6; r++) {
        cout << r << " ";
        for (int c = 0; c < 7; c++) {
            cout << grid[r][c] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int FourInRow_Board::drop(int col, char m) {
    // dropping a piece in the lowest empty row in the column
    if (col < 0 || col > 6) return -1;

    for (int r = 5; r >= 0; r--) {
        if (grid[r][col] == '.') {
            grid[r][col] = m;
            return r;
        }
    }

    return -1;
}

bool FourInRow_Board::isFull() const {
    // if the top row has any '.', the board is not full
    for (int c = 0; c < 7; c++)
        if (grid[0][c] == '.') return false;
    return true;
}

bool FourInRow_Board::checkDirection(int r,int c,int dr,int dc,char m) const {
    int count=1;

    int rr=r+dr, cc=c+dc;
    while (inRange(rr,cc) && grid[rr][cc]==m) {count++; rr+=dr; cc+=dc;}

    rr=r-dr; cc=c-dc;
    while (inRange(rr,cc) && grid[rr][cc]==m) {count++; rr-=dr; cc-=dc;}

    return count>=4;
}

bool FourInRow_Board::checkWin(int r,int c,char m) const {
    // check all 4 possible win directions
    return checkDirection(r,c,1,0,m) ||
           checkDirection(r,c,0,1,m) ||
           checkDirection(r,c,1,1,m) ||
           checkDirection(r,c,1,-1,m);
}


void startFourInRow() {

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

    cout << MAGENTA << "Welcome to Four-In-A-Row!\n\n" << RESET;

    FourInRow_Board B;
    int p=1;

    B.display();

    while (true) {
        char mark = (p==1 ? 'X' : 'O');
        int col;

        cout << CYAN << "Player " << p << " (" << mark << ") choose column (0-6): " << RESET;
        cin >> col;

        int row = B.drop(col,mark);

        if (row == -1) {
            cout << RED << "Invalid move!\n" << RESET;
            continue;
        }

        B.display();

        // check if the new move caused a win
        if (B.checkWin(row,col,mark)) {
            cout << GREEN << "Player " << p << " WINS!\n" << RESET;
            break;
        }

        // check if the board is full
        if (B.isFull()) {
            cout << YELLOW << "It's a tie!\n" << RESET;
            break;
        }

        p = (p==1 ? 2 : 1);
    }
}
