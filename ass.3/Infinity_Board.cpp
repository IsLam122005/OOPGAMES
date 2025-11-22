//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "Infinity_Board.h" // <-- لازم نعمل include للهيدر بتاعنا

using namespace std;

//--------------------------------------- Infinity_Board Implementation

Infinity_Board::Infinity_Board() : Board(3, 3) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool Infinity_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // 1. نتأكد إن المكان فاضي (زي X-O)
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol)) {

        // 2. نحط الحركة الجديدة
        board[x][y] = toupper(mark);
        n_moves++;

        // 3. نضيفها للطابور عشان نفتكرها
        move_history.push({ x, y });

        // 4. (اللوجيك الجديد) لو الطابور بقى فيه أكتر من 3 حركات
        if (move_history.size() > 3) {
            // هات أقدم حركة (اللي في أول الطابور)
            pair<int, int> oldest_move = move_history.front();
            move_history.pop(); // امسحها من الطابور

            // امسحها من على البورد (رجعها نقطة)
            board[oldest_move.first][oldest_move.second] = blank_symbol;
        }

        return true; // الحركة تمت بنجاح
    }
    return false; // المكان ده متاخد
}

// (دي دالة الفوز، زي X-O بالظبط)
bool Infinity_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
            (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym))
            return true;
    }

    // Check diagonals
    if ((all_equal(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) ||
        (all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym))
        return true;

    return false;
}

// (دي دالة الخسارة)
bool Infinity_Board::is_lose(Player<char>*) {
    return false; // مفيش خسارة في اللعبة دي، بس لازم نكتبها
}

// (دي دالة التعادل)
bool Infinity_Board::is_draw(Player<char>* player) {
    // اللعبة دي مببتنتهيش بتعادل، هي شغالة للأبد
    // بس عشان الفريم ورك، هنرجع false دايماً
    return false;
}

// (دي دالة نهاية اللعبة)
bool Infinity_Board::game_is_over(Player<char>* player) {
    // اللعبة بتنتهي بس لو حد كسب
    return is_win(player);
}