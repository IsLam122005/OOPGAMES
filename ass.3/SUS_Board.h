// SUS.h
#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"
#include <array>

/** @file SUS.h
 *  @brief Classes for the 3x3 SUS game.
 */

 /** @class SUS_Move
  *  @brief Move in SUS game (row, col, symbol).
  */
class SUS_Move : public Move<char> {
public:
    /** @brief Constructor. */
    SUS_Move(int r = -1, int c = -1, char s = 'S') : Move<char>(r, c, s) {}
    virtual ~SUS_Move() = default;
};

/** @class SUS_Board
 *  @brief SUS game board & rules.
 */
class SUS_Board : public Board<char> {
public:
    SUS_Board();
    virtual ~SUS_Board() = default;

    /** @brief Apply move. */
    virtual bool update_board(Move<char>* move) override;

    /** @brief Check win. */
    virtual bool is_win(Player<char>* player) override;

    /** @brief Check loss. */
    virtual bool is_lose(Player<char>* player) override;

    /** @brief Check draw. */
    virtual bool is_draw(Player<char>* player) override;

    /** @brief Check if game ended. */
    virtual bool game_is_over(Player<char>* player) override;

    /** @brief Start console play. */
    static void play();

private:
    int scoreS;
    int scoreU;

    /** @brief Check if position is valid. */
    static bool inRange(int r, int c);

    /** @brief Count SUS patterns around a cell. */
    int countSUSAtCell(int r, int c) const;
};

#endif // SUS_H
