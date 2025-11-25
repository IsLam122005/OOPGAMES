#include "Pyramid_X_O.h"
#include <iostream>
using namespace std;

// 1. تنفيذ الكونستركتور
template <typename T>
Pyramid_Board<T>::Pyramid_Board() : Board<T>(3, 5) {
    this->n_moves = 0;
}

// 2. تنفيذ دالة الحركة (قوانين الهرم)
template <typename T>
bool Pyramid_Board<T>::update_board(Move<T>* move) {
    int x = move->get_x();
    int y = move->get_y();

    // شرط 1: التأكد من حدود المصفوفة
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
        return false;
    }

    // شرط 2: قوانين شكل الهرم (الأماكن المحرمة)
    // القمة (الصف 0): مسموح عمود 2 بس
    if (x == 0 && y != 2) return false;

    // الوسط (الصف 1): مسموح أعمدة 1, 2, 3 بس
    if (x == 1 && (y < 1 || y > 3)) return false;

    // شرط 3: التأكد إن المكان فاضي (بنفترض الفراغ بـ 0)
    if (this->board[x][y] != 0) {
        return false;
    }

    // تطبيق الحركة
    this->n_moves++;
    this->board[x][y] = move->get_symbol();
    return true;
}

// 3. تنفيذ دالة الفوز
template <typename T>
bool Pyramid_Board<T>::is_win(Player<T>* p) {
    T s = p->get_symbol();
    // اختصار عشان الكود يبقى مقروء
    // بنستخدم this->board عشان نوصل للمصفوفة

    // الفوز الأفقي (Rows)
    // الصف الأوسط (1,1 -> 1,3)
    if (this->board[1][1] == s && this->board[1][2] == s && this->board[1][3] == s) return true;

    // الصف الأخير (فيه 3 احتمالات)
    if (this->board[2][0] == s && this->board[2][1] == s && this->board[2][2] == s) return true;
    if (this->board[2][1] == s && this->board[2][2] == s && this->board[2][3] == s) return true;
    if (this->board[2][2] == s && this->board[2][3] == s && this->board[2][4] == s) return true;

    // الفوز الرأسي (Column)
    // العمود الوحيد الكامل هو اللي في النص (العمود 2)
    if (this->board[0][2] == s && this->board[1][2] == s && this->board[2][2] == s) return true;

    // الفوز القطري (Diagonals)
    // X كبيرة
    if (this->board[0][2] == s && this->board[1][1] == s && this->board[2][0] == s) return true; // مائل لليسار
    if (this->board[0][2] == s && this->board[1][3] == s && this->board[2][4] == s) return true; // مائل لليمين

    return false;
}

// 4. تنفيذ دالة التعادل
template <typename T>
bool Pyramid_Board<T>::is_draw(Player<T>* p) {
    // عدد خانات الهرم 9 بس، لو اتملوا ومحدش كسب يبقى تعادل
    return (this->n_moves == 9 && !is_win(p));
}

// 5. تنفيذ دالة انتهاء اللعبة
template <typename T>
bool Pyramid_Board<T>::game_is_over(Player<T>* p) {
    return is_win(p) || is_draw(p);
}
  
    template <typename T>
    bool Pyramid_Board<T>::is_lose(Player<T>* p) {
        return false;
    }
