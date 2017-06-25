#pragma once

#include "Main.h"
#include <vector>
#include <string>
using namespace std;

#define MAX_ROW_WIDTH       (SCREEN_W * 3 / 4)

enum eWho { You, Me };

class Message {
    string str;                 // メッセージ内容
    eWho who;                   // どちらのメッセージか
    int width;                  // 文字列1行の幅
    vector<int> head_index;     // 行頭になる文字が先頭から何文字目か
public:
    Message(string s, eWho w);
    string GetRow(int i) const ;    // 第i+1行目の文字列を返す
    bool isMyMsg() const {
        return who == Me;           // 自分のメッセージかどうかを返す
    }
    int GetRowNum() const {
        return head_index.size();   // 行数を返す
    }
    int GetWidth() const {
        return width;               // 1行の幅を返す
    }
};

extern vector<Message> talk;
