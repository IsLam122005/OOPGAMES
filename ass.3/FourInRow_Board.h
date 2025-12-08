#ifndef FOURINAROW_H
#define FOURINAROW_H

#include "BoardGame_Classes.h"

/** @file FourInARow.h
 *  @brief 6x7 Four-in-a-Row game classes.
 */

 /** @class FourInARow_Move
  *  @brief Represents a move (column + symbol).
  */
class FourInARow_Move : public Move<char> {
public:
    /** @brief Constructor. */
    FourInARow_Move(int col = -1, char s = 'X') : Move<char>(-1, col, s) {}
    virtual ~FourInARow_Move() = default;
};

/** @class FourInARow_Board
 *  @brief Board + logic for Four-in-a-Row.
 */
class FourInARow_Board : public Board<char> {
public:
    FourInARow_Board();
    virtual ~FourInARow_Board() = default;

    /** @brief Apply move. */
    virtual bool update_board(Move<char>* move) override;

    /** @brief Check winner. */
    virtual bool is_win(Player<char>* player) override;

    /** @brief Check loser. */
    virtual bool is_lose(Player<char>* player) override;

    /** @brief Check draw. */
    virtual bool is_draw(Player<char>* player) override;

    /** @brief Check if game ended. */
    virtual bool game_is_over(Player<char>* player) override;

    /** @brief Start console version. */
    static void play();

private:
    int lastRow;
    int lastCol;
    char lastMark;

    /** @brief Check if cell is valid. */
    bool inRange(int r, int c) const;

    /** @brief Count marks in a direction. */
    bool checkDirection(int r, int c, int dr, int dc, char m) const;

    /** @brief Check win starting at cell. */
    bool checkWinAt(int r, int c, char m) const;

    /** @brief Check if board is full. */
    bool boardFull() const;
};

#endif // FOURINAROW_H
