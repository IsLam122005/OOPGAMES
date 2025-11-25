// File: Pyramid_X_O.h
#ifndef PYRAMID_X_O_H
#define PYRAMID_X_O_H

#include "BoardGame_Classes.h"

template <typename T>
class Pyramid_Board : public Board<T> {
public:
    // الكونستركتور
    Pyramid_Board();

    // الدوال اللي ورثناها وهنكتب اللوجيك بتاعها
    bool update_board(Move<T>* move) override;
    bool is_win(Player<T>* p) override;
    bool is_draw(Player<T>* p) override;
    bool game_is_over(Player<T>* p) override;
    bool is_lose(Player<T>* p);
};

// -----------------------------------------------------------
// هام جداً: عشان ده Template Class، لازم نربط ملف الـ cpp هنا
// لو كان كلاس عادي كنا عملنا include في الـ cpp بس
// -----------------------------------------------------------
#include "Pyramid_X_O.cpp"

#endif // PYRAMID_X_O_H