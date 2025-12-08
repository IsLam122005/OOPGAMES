#ifndef OBSTACLES_TICTACTOE
#define OBSTACLES_TICTACTOE

#include "BoardGame_Classes.h"
#include <vector>

/** @class ObstaclesTTT_Move
 *  @brief Move for Tic-Tac-Toe with obstacles.
 */
class ObstaclesTTT_Move : public Move<char> {
public:
    /** @brief Constructor. */
    ObstaclesTTT_Move(int r = -1, int c = -1, char s = 'X')
        : Move<char>(r, c, s) {}

    virtual ~ObstaclesTTT_Move() = default;
};

/** @class ObstaclesTTT_Board
 *  @brief Board logic for obstacle-based Tic-Tac-Toe.
 */
class ObstaclesTTT_Board : public Board<char> {
public:
    ObstaclesTTT_Board();
    virtual ~ObstaclesTTT_Board() = default;

    /** @brief Apply move. */
    bool update_board(Move<char>* move) override;

    /** @brief Check win. */
    bool is_win(Player<char>* player) override;

    /** @brief Check loss. */
    bool is_lose(Player<char>* player) override;

    /** @brief Check draw. */
    bool is_draw(Player<char>* player) override;

    /** @brief Check end of game. */
    bool game_is_over(Player<char>* player) override;

    /** @brief Start interactive game. */
    static void play();

private:
    /** @brief Validate board index. */
    bool inRange(int r, int c) const;

    /** @brief Randomly place up to two obstacles. */
    void add_obstacles();

    /** @brief Check 4-in-a-row in direction. */
    bool check4At(int r, int c, int dr, int dc, char sym) const;

    /** @brief Check if board is full. */
    bool boardFull() const;
};

#endif
