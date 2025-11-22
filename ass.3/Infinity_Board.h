// --------------------------------------------------
// دي أهم حاجة تتصلح
#ifndef INFINITY_BOARD_H
#define INFINITY_BOARD_H
// --------------------------------------------------

#include <queue>
#include <utility>
#include "BoardGame_Classes.h" // الفريم ورك الأساسي
using namespace std;

/**
 * @class Infinity_Board
 * @brief ده الكلاس الخاص بلعبة Infinity Tic-Tac-Toe
 *
 * ده بيورث من الكلاس الأم Board وبينفذ اللوجيك بتاع اللعبة
 * (بتاع مسح أقدم حركة)
 */
class Infinity_Board : public Board<char> {
private:
    char blank_symbol = '.';
    queue<pair<int, int>> move_history; // الطابور اللي بيخزن الحركات

public:
    // الكونستركتور
    Infinity_Board();

    // الدوال اللي بنعملها Override (إجبارية)
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

// --------------------------------------------------
// دي برضه مهمة
#endif // INFINITY_BOARD_H
// --------------------------------------------------