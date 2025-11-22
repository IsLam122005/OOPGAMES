/**
 * @file XO_Demo.cpp
 * @brief Entry point for the FCAI X-O (Tic-Tac-Toe) game.
 *
 * This file initializes the X-O game by creating the user interface, board, and players.
 * It then launches the game loop via the GameManager class.
 * All dynamically allocated objects are properly deleted at the end.
 */

#include <iostream> // Required for input/output operations (cout, cin)
#include <string>   // Required for string
#include <vector>   // Required for vector
#include <memory>   // Required for unique_ptr
#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include "Infinity_Board.h" // <-- لازم دي تكون موجودة

using namespace std;

int main() {

    srand(static_cast<unsigned int>(time(0)));

    cout << "Welcome to FCAI Board Games!" << endl;
    cout << "Select Game:" << endl;
    cout << "1: X-O (Demo)" << endl;
    cout << "2: Infinity Tic-Tac-Toe " << endl;

    int choice;
    cin >> choice;

    if (choice == 1) {
        // --- كود لعبة X-O ---
        UI<char>* game_ui = new XO_UI();
        Board<char>* xo_board = new X_O_Board(); // <-- دي بتشغل X-O
        Player<char>** players = game_ui->setup_players();
        GameManager<char> x_o_game(xo_board, players, game_ui);
        x_o_game.run();

        delete xo_board;
        delete game_ui;
        for (int i = 0; i < 2; ++i) { delete players[i]; }
        delete[] players;
    }
    else if (choice == 2) {
        // --- كود لعبة Infinity ---
        Board<char>* board = new Infinity_Board(); // <-- دي بتشغل Infinity
        UI<char>* ui = new XO_UI(); // بنستخدم نفس الـ UI بتاع X-O
        Player<char>** players = ui->setup_players();
        GameManager<char> game(board, players, ui);

        game.run();

        // (Cleanup)
        delete board;
        delete ui;
        for (int i = 0; i < 2; ++i) { delete players[i]; }
        delete[] players;
    }

    return 0;
}