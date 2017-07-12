#pragma once

#include "Main.h"
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

#define MAX_ROW_WIDTH       (SCREEN_W * 3 / 4)
#define VOICE_NUM           7

enum eWho { You, Me };
enum eVoice { Omakase, Sawaguhodo, Suggo_i, Tabenaide, Tabenaiyo, Wa_i, Wakaran };

class Message {
    string str;                 // メッセージ内容
    eWho who;                   // どちらのメッセージか
    int width;                  // 文字列1行の幅
    vector<int> head_index;     // 行頭になる文字が先頭から何文字目か
public:
    Message(string s, eWho w);
    string GetRow(int i) const ;        // 第i+1行目の文字列を返す
    bool isMyMsg() const {
        return who == Me;               // 自分のメッセージかどうかを返す
    }
    int GetRowNum() const {
        return (int)head_index.size();  // 行数を返す
    }
    int GetWidth() const {
        return width;                   // 1行の幅を返す
    }
};

class Voice {
    static unordered_map<eVoice, int> hVoice;   // 音声ハンドル
    int hPlaying;                               // 現在再生中の音声
public:
    Voice();
    void Speak(string str);
};

extern vector<Message> talk;
extern Voice *pVoice;