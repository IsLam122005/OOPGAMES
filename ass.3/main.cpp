// main.cpp
#include <iostream>
#include "SUS.h"
#include "FourInARow.h"
#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include "Infinity_Board.h"
#include "MisereXO_Classes.h"
#include "diamondXO.h"

using namespace std;

int main() {

    cout << "Welcome to FCAI Board Games!\n";
    cout << "1. X-O\n";
    cout << "2. Infinity TicTacToe\n";
    cout << "3. SUS Game\n";
    cout << "4. Four-In-A-Row\n";
    cout << "5. Misere XO\n";
    cout << "6. Diamond Tic-Tac-Toe\n";

    int ch;
    cin >> ch;

    if (ch == 1) {
        UI<char>* ui = new XO_UI();
        Board<char>* board = new X_O_Board();
        Player<char>** players = ui->setup_players();
        GameManager<char> game(board, players, ui);
        game.run();

        delete board;
        delete ui;
        delete[] players;
    }
    else if (ch == 2) {
        UI<char>* ui = new XO_UI();
        Board<char>* board = new Infinity_Board();
        Player<char>** players = ui->setup_players();
        GameManager<char> game(board, players, ui);
        game.run();

        delete board;
        delete ui;
        delete[] players;
    }
    else if (ch == 3) {
        SUS_Board::play();
    }
    else if (ch == 4) {
        FourInARow_Board::play();
    }
    else if (ch == 5) {
        Misere_XO_UI ui;
        Player<char>** players = ui.setup_players();

        Misere_XO_Board* board = new Misere_XO_Board();
        GameManager<char> manager(board, players, &ui);

        manager.run();

        delete board;
        delete[] players;
    }
    else if (ch == 6) {
        DiamondUI* ui = new DiamondUI();
        Player<char>** players = ui->setup_players();

        DiamondBoard* board = new DiamondBoard();
        GameManager<char> manager(board, players, ui);

        manager.run();

        delete board;
        delete ui;
        delete[] players;
    }

    return 0;
}
