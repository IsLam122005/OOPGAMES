#ifndef TICTACTOE4X4_H
#define TICTACTOE4X4_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// =============================================================
// 1. كلاس البوردة (المسؤول عن القوانين وتخزين القطع)
// =============================================================
template <typename T>
class TicTacToe4x4_Board : public Board<T> {
public:
    // الكونستركتور: بنجهز البوردة 4x4 ونرص القطع
  // الكونستركتور: بنرص القطع بطريقة متفرقة (Zig-Zag)
    // عشان نمنع الفوز الفوري من أول حركة
    TicTacToe4x4_Board() : Board<T>(4, 4) {
        this->n_moves = 0;

        // رصة اللاعب X (فوق): خانة اه وخانة لا
        this->board[0][0] = 'X';
        this->board[0][2] = 'X';
        this->board[1][1] = 'X';
        this->board[1][3] = 'X';

        // رصة اللاعب O (تحت): العكس
        this->board[2][0] = 'O';
        this->board[2][2] = 'O';
        this->board[3][1] = 'O';
        this->board[3][3] = 'O';
    }

    // دالة تنفيذ الحركة
    // Move شايل رقمين متشفرين: x = المصدر، y = الوجهة
    bool update_board(Move<T>* move) override {
        // فك الشفرة
        int from_row = move->get_x() / 10;
        int from_col = move->get_x() % 10;
        int to_row = move->get_y() / 10;
        int to_col = move->get_y() % 10;

        // 1. هل الأرقام جوه حدود البوردة؟
        if (from_row < 0 || from_row > 3 || from_col < 0 || from_col > 3 ||
            to_row < 0 || to_row > 3 || to_col < 0 || to_col > 3) {
            cout << "Error: Out of bounds!\n";
            return false;
        }

        // 2. هل دي قطعتك أصلاً؟
        if (this->board[from_row][from_col] != move->get_symbol()) {
            cout << "Error: This is not your piece (or empty cell)!\n";
            return false;
        }

        // 3. هل المكان اللي رايحله فاضي؟
        if (this->board[to_row][to_col] != 0) {
            cout << "Error: Destination is not empty!\n";
            return false;
        }

        // 4. هل الحركة خطوة واحدة بس؟ (أفقي أو رأسي)
        if (abs(to_row - from_row) + abs(to_col - from_col) != 1) {
            cout << "Error: You can only move 1 step (Up/Down/Left/Right)!\n";
            return false;
        }

        // تنفيذ الحركة
        this->board[from_row][from_col] = 0;
        this->board[to_row][to_col] = move->get_symbol();
        this->n_moves++;
        return true;
    }

    // دالة الفوز: بتدور على 3 رموز متشابهة ورا بعض
    bool is_win(Player<T>* p) override {
        T s = p->get_symbol();

        // فحص الصفوف والأعمدة
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 2; j++) { // j < 2 عشان ندور على 3 خانات (0,1,2) أو (1,2,3)
                // أفقي (جنب بعض)
                if (this->board[i][j] == s && this->board[i][j + 1] == s && this->board[i][j + 2] == s) return true;
                // رأسي (فوق بعض)
                if (this->board[j][i] == s && this->board[j + 1][i] == s && this->board[j + 2][i] == s) return true;
            }
        }

        // فحص الأقطار (المقصات)
        // فيه أماكن محددة بس ينفع يبدأ منها القطر
        // قطر رئيسي (نازل لليمين)
        if (check_diagonal(s, 0, 0, 1, 1)) return true;
        if (check_diagonal(s, 0, 1, 1, 1)) return true;
        if (check_diagonal(s, 1, 0, 1, 1)) return true;
        if (check_diagonal(s, 1, 1, 1, 1)) return true;

        // قطر عكسي (نازل للشمال)
        if (check_diagonal(s, 0, 3, 1, -1)) return true;
        if (check_diagonal(s, 0, 2, 1, -1)) return true;
        if (check_diagonal(s, 1, 3, 1, -1)) return true;
        if (check_diagonal(s, 1, 2, 1, -1)) return true;

        return false;
    }

    // دالة مساعدة عشان نختصر كود الأقطار
    bool check_diagonal(T s, int r, int c, int dr, int dc) {
        return (this->board[r][c] == s &&
            this->board[r + dr][c + dc] == s &&
            this->board[r + 2 * dr][c + 2 * dc] == s);
    }

    bool is_draw(Player<T>* p) override { return false; }
    bool game_is_over(Player<T>* p) override { return is_win(p); }
    bool is_lose(Player<T>* p) { return false; }
};

// =============================================================
// 2. كلاس الـ UI (المسؤول عن التفكير والذكاء)
// =============================================================
template <typename T>
class TicTacToe4x4_UI : public UI<T> {
public:
    // التعديل: ضفنا رسالة ترحيب عشان نرضي الكونستركتور بتاع الـ UI
    // وضفنا (unsigned int) عشان نلغي التحذير الأصفر
    TicTacToe4x4_UI(int w) : UI<T>("Welcome to 4x4 Tic-Tac-Toe", w) {
        srand(static_cast<unsigned int>(time(0)));
    }

    Move<T>* get_move(Player<T>* p) override {
        // ------------------------------------
        // أ) لو اللاعب إنسان (Human)
        // ------------------------------------
        if (p->get_type() == PlayerType::HUMAN) {
            int r1, c1, r2, c2;
            cout << "\nPlayer " << p->get_name() << " (" << p->get_symbol() << ")\n";
            cout << "Select Piece (Row Col): ";
            cin >> r1 >> c1;
            cout << "Move to (Row Col): ";
            cin >> r2 >> c2;
            // بنشفر الإحداثيات (المصدر والوجهة) ونبعتهم
            return new Move<T>(r1 * 10 + c1, r2 * 10 + c2, p->get_symbol());
        }

        // ------------------------------------
        // ب) لو اللاعب كمبيوتر (Computer)
        // ------------------------------------
        else {
            vector<vector<T>> grid = p->get_board_ptr()->get_board_matrix();
            T s = p->get_symbol();

            // قائمة هنحوش فيها كل الحركات المتاحة
            struct Option { int r1, c1, r2, c2; };
            vector<Option> valid_moves;

            // 1. ندور في كل مكان في البوردة
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    // لو لقينا قطعة بتاعت الكمبيوتر
                    if (grid[i][j] == s) {
                        // نشوف جيرانها (فوق، تحت، يمين، شمال)
                        int dr[] = { -1, 1, 0, 0 };
                        int dc[] = { 0, 0, -1, 1 };

                        for (int k = 0; k < 4; k++) {
                            int ni = i + dr[k];
                            int nj = j + dc[k];
                            // لو الجار ده جوه البوردة وفاضي
                            if (ni >= 0 && ni < 4 && nj >= 0 && nj < 4 && grid[ni][nj] == 0) {
                                // سجل الحركة دي إنها "متاحة"
                                valid_moves.push_back({ i, j, ni, nj });
                            }
                        }
                    }
                }
            }

            // 2. نختار حركة عشوائية من القائمة (عشان ميبقاش متوقع)
            if (!valid_moves.empty()) {
                int index = rand() % valid_moves.size();
                Option op = valid_moves[index];
                return new Move<T>(op.r1 * 10 + op.c1, op.r2 * 10 + op.c2, s);
            }

            // لو مفيش حركات خالص (نادر جداً)، نرجع حركة وهمية
            return new Move<T>(-1, -1, s);
        }
    }

    // دالة إنشاء اللاعب (مطلوبة للتمبلت)
    Player<T>* create_player(string& name, T symbol, PlayerType type) override {
        return new Player<T>(name, symbol, type);
    }
};

#endif