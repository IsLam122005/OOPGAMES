#include <iostream>
#include "SUS_Board.h"
#include "FourInRow_Board.h"
#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include "Infinity_Board.h"

using namespace std;

int main() {

    cout << "Welcome to FCAI Board Games!\n";
    cout << "1. X-O\n";
    cout << "2. Infinity TicTacToe\n";
    cout << "3. SUS Game\n";
    cout << "4. Four-In-A-Row\n";

    int ch;
    cin >> ch;

    if (ch == 1) {
        UI<char>* ui = new XO_UI();
        Board<char>* board = new X_O_Board();
        Player<char>** players = ui->setup_players();
        GameManager<char> game(board, players, ui);
        game.run();
    }
    else if (ch == 2) {
        UI<char>* ui = new XO_UI();
        Board<char>* board = new Infinity_Board();
        Player<char>** players = ui->setup_players();
        GameManager<char> game(board, players, ui);
        game.run();
    }
    else if (ch == 3) {
        playSUS();
    }
    else if (ch == 4) {
        startFourInRow();
    }

    return 0;
}
