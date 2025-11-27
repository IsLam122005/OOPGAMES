#include <iostream>
#include "SUS_Board.h"
#include "FourInRow_Board.h"
#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include "Infinity_Board.h"
#include "Pyramid_X_O.h"
#include "TicTacToe4x4.h"
#include "MisereXO_Classes.h"
#include "diamondXO.h"
#include "numerical tic-tac-toe.h"
#include "FiveByFive_Classes.h"
#include "WordGame_Classes.h"

using namespace std;

int main() {
    cout << "Welcome to FCAI Board Games!\n";
    cout << "1. X-O\n";
    cout << "2. Infinity TicTacToe\n";
    cout << "3. SUS Game\n";
    cout << "4. Four-In-A-Row\n";
    cout << "5. Pyramid Tic-Tac-Toe\n";
    cout << "6. TicTacToe4x4\n";
    cout << "7. Misere Tic Tac Toe\n";
    cout << "8. Diamond Tic Tac Toe\n";
    cout << "9. Numerical Tic-Tac-Toe\n";
    cout << "10. 5x5 Tic Tac Toe\n";
    cout << "11. Word Tic-Tac-Toe\n";
    int ch;
    cin >> ch;

    if (ch == 1) {
        UI<char>* ui = new XO_UI();
        Board<char>* board = new X_O_Board();
        Player<char>** players = ui->setup_players();
        GameManager<char> game(board, players, ui);
        game.run();
        delete board; delete players[0]; delete players[1]; delete ui;
    }
    else if (ch == 2) {
        UI<char>* ui = new XO_UI();
        Board<char>* board = new Infinity_Board();
        Player<char>** players = ui->setup_players();
        GameManager<char> game(board, players, ui);
        game.run();
        delete board; delete players[0]; delete players[1]; delete ui;
    }
    else if (ch == 3) {
        UI<char>* ui = new XO_UI();
        Board<char>* board = new SUS_Board();
        Player<char>** players = ui->setup_players();
        GameManager<char> game(board, players, ui);
        game.run();
        delete board; delete players[0]; delete players[1]; delete ui;
    }
    else if (ch == 4) {
        UI<char>* ui = new XO_UI();
        Board<char>* board = new FourInARow_Board();
        Player<char>** players = ui->setup_players();
        GameManager<char> game(board, players, ui);
        game.run();
        delete board; delete players[0]; delete players[1]; delete ui;
    }
    else if (ch == 5) {
        UI<char>* ui = new XO_UI();
        Board<char>* board = new Pyramid_Board<char>();
        Player<char>** players = ui->setup_players();
        GameManager<char> game(board, players, ui);
        game.run();
        delete board; delete players[0]; delete players[1]; delete ui;
    }
    else if (ch == 6) {
        UI<char>* ui = new TicTacToe4x4_UI<char>(3);
        Board<char>* board = new TicTacToe4x4_Board<char>();
        Player<char>** players = ui->setup_players();
        GameManager<char> game(board, players, ui);
        game.run();
        delete board; delete players[0]; delete players[1]; delete ui;
    }
    else if (ch == 7) {
        UI<char>* ui = new Misere_XO_UI();
        Board<char>* board = new Misere_XO_Board();
        Player<char>** players = ui->setup_players();
        GameManager<char> game(board, players, ui);
        game.run();
        delete board; delete players[0]; delete players[1]; delete ui;
    }
    else if (ch == 8) {
        UI<char>* ui = new DiamondUI();
        Board<char>* board = new DiamondBoard();
        Player<char>** players = ui->setup_players();
        GameManager<char> game(board, players, ui);
        game.run();
        delete board; delete players[0]; delete players[1]; delete ui;
    }
    else if (ch == 9) {
     
        UI<int>* ui = new NumericalUI<int>();
        Board<int>* board = new NumericalBoard<int>();
        Player<int>** players = ui->setup_players();
        GameManager<int> game(board, players, ui);
        game.run();
        delete board; delete players[0]; delete players[1]; delete ui;
    }
    else if (ch == 10) {
        UI<char>* ui = new FiveByFive_UI();
        Board<char>* board = new FiveByFive_Board();
        Player<char>** players = ui->setup_players();
        GameManager<char> game(board, players, ui);
        game.run();
        delete board; delete players[0]; delete players[1]; delete ui;
    }
    else if (ch == 11) {
        UI<char>* ui = new WordGame_UI();
        Board<char>* board = new WordTae_Board();
        Player<char>** players = ui->setup_players();
        GameManager<char> game(board, players, ui);
        game.run();
        delete board; delete players[0]; delete players[1]; delete ui;
    }

    return 0;
}