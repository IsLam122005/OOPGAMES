#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

// حجم اللوحة للعبة 3
const int SIZE3 = 5;

class Game3_Triplets {
private:
  char board[SIZE3][SIZE3];
  int moves_count;
  char current_player;

  // تهيئة اللوحة (جميع الخلايا فارغة)
  void initializeBoard() {
    for (int i = 0; i < SIZE3; ++i) {
      for (int j = 0; j < SIZE3; ++j) {
        board[i][j] = ' ';
      }
    }
    moves_count = 0;
    current_player = 'X';
  }

  // عرض اللوحة
  void displayBoard() const {
    cout << "\n   1   2   3   4   5\n";
    cout << "  -------------------\n";
    for (int i = 0; i < SIZE3; ++i) {
      cout << i + 1 << " | ";
      for (int j = 0; j < SIZE3; ++j) {
        cout << board[i][j] << " | ";
      }
      cout << "\n  -------------------\n";
    }
  }

  // حساب نقاط (الثلاثيات) للاعب معين
  int countTriplets(char player) const {
    int score = 0;

    // 1. فحص الصفوف (Rows)
    for (int i = 0; i < SIZE3; ++i) {
      for (int j = 0; j <= SIZE3 - 3; ++j) { // نتحرك حتى الخانة ما قبل الأخيرة بثلاثة
        if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player) {
          score++;
        }
      }
    }

    // 2. فحص الأعمدة (Columns)
    for (int j = 0; j < SIZE3; ++j) {
      for (int i = 0; i <= SIZE3 - 3; ++i) {
        if (board[i][j] == player && board[i + 1][j] == player && board[i + 2][j] == player) {
          score++;
        }
      }
    }

    // 3. فحص الأقطار الرئيسية (Main Diagonals)
    // من الأعلى لليسار إلى الأسفل لليمين
    for (int i = 0; i <= SIZE3 - 3; ++i) {
      for (int j = 0; j <= SIZE3 - 3; ++j) {
        if (board[i][j] == player && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player) {
          score++;
        }
      }
    }

    // 4. فحص الأقطار العكسية (Anti-Diagonals)
    // من الأعلى لليمين إلى الأسفل لليسار
    for (int i = 0; i <= SIZE3 - 3; ++i) {
      for (int j = SIZE3 - 1; j >= 2; --j) { // نتحرك من اليمين
        if (board[i][j] == player && board[i + 1][j - 1] == player && board[i + 2][j - 2] == player) {
          score++;
        }
      }
    }

    return score;
  }

public:
  void playGame() {
    initializeBoard();
    cout << "--- Game 3: 5x5 Tic Tac Toe (Triplets) ---\n";

    // اللعبة تنتهي بعد 24 نقلة (مربع واحد متبقي)
    while (moves_count < 24) {
      displayBoard();
      int row, col;
      cout << "Player " << current_player << " turn (" << moves_count + 1 << "/24). Enter row and column (1-5): ";

      if (!(cin >> row >> col)) {
        cin.clear(); cin.ignore(10000, '\n');
        cout << "Invalid input. Try again.\n";
        continue;
      }

      // التحقق من صحة المدخلات
      if (row >= 1 && row <= SIZE3 && col >= 1 && col <= SIZE3 && board[row - 1][col - 1] == ' ') {
        board[row - 1][col - 1] = current_player;
        moves_count++;
        current_player = (current_player == 'X') ? 'O' : 'X';
      }
      else {
        cout << "Invalid move or cell is already taken. Try again.\n";
      }
    }

    // بعد انتهاء 24 نقلة
    displayBoard();
    cout << "\nGame finished (24 moves completed).\n";

    int scoreX = countTriplets('X');
    int scoreO = countTriplets('O');

    cout << "------------------------------------\n";
    cout << "Final Scores:\n";
    cout << "Player X Triplets: " << scoreX << " points\n";
    cout << "Player O Triplets: " << scoreO << " points\n";
    cout << "------------------------------------\n";

    if (scoreX > scoreO) {
      cout << ">>> Winner is Player X! <<<\n";
    }
    else if (scoreO > scoreX) {
      cout << ">>> Winner is Player O! <<<\n";
    }
    else {
      cout << ">>> It's a Draw! <<<\n";
    }
  }
};

int main() {
    Game3_Triplets game3;
    game3.playGame();
    return 0;
}