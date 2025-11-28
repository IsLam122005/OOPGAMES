#ifndef OBSTACLES_TICTACTOE
#define OBSTACLES_TICTACTOE

#include "BoardGame_Classes.h"
#include <vector>

class ObstaclesTTT_Move : public Move<char> {
public:
    ObstaclesTTT_Move(int r = -1, int c = -1, char s = 'X') : Move<char>(r, c, s) {}
    virtual ~ObstaclesTTT_Move() = default;
};

class ObstaclesTTT_Board : public Board<char> {
public:
    ObstaclesTTT_Board();
    virtual ~ObstaclesTTT_Board() = default;

    virtual bool update_board(Move<char>* move) override;
    virtual bool is_win(Player<char>* player) override;
    virtual bool is_lose(Player<char>* player) override;
    virtual bool is_draw(Player<char>* player) override;
    virtual bool game_is_over(Player<char>* player) override;

    static void play();

private:
    bool inRange(int r,int c) const;
    void add_obstacles(); // add up to 2 obstacles randomly
    bool check4At(int r,int c,int dr,int dc,char sym) const;
    bool boardFull() const;
};

#endif
