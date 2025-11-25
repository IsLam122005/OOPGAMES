#include <iostream>
#include "SUS_Board.h"
#include "FourInRow_Board.h"
#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include "Infinity_Board.h"
#include "Pyramid_X_O.h"
#include "TicTacToe4x4.h"

using namespace std;

int main() {

    cout << "Welcome to FCAI Board Games!\n";
    cout << "1. X-O\n";
    cout << "2. Infinity TicTacToe\n";
    cout << "3. SUS Game\n";
    cout << "4. Four-In-A-Row\n";
    cout << "5.  Pyramid Tic-Tac-Toe\n";
    cout << "6.TicTacToe4x4\n";
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
    else if (ch == 5) {
        // التصحيح هنا: نستخدم الكلاسات مباشرة بدل دالة py
        // هنستخدم XO_UI لأنه متاح وشغال مع الحروف
        UI<char>* ui = new XO_UI();

        // ونستخدم بوردة الهرم بتاعتنا
        Board<char>* board = new Pyramid_Board<char>();

        // ونجهز اللاعبين واللعبة
        Player<char>** players = ui->setup_players();
        GameManager<char> game(board, players, ui);

        // شغل اللعبة
        game.run();
    }
    else if (ch == 6) {
        // UI<char>* ui = new XO_UI();  <-- امسح القديم ده لو موجود

        // استخدم الجديد ده:
        UI<char>* ui = new TicTacToe4x4_UI<char>(3);

        Board<char>* board = new TicTacToe4x4_Board<char>();
        Player<char>** players = ui->setup_players();
        GameManager<char> game(board, players, ui);

        game.run();

        delete board;
        delete players[0];
        delete players[1];
        delete ui;
    }
    return 0;
}
