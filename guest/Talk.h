#pragma once

#include <vector>
#include <string>
using namespace std;

enum eWho { Host, Guest };

class Message {
    string str;     // メッセージ内容
    eWho who;       // どちらのメッセージか
public:
    Message(string s, eWho w);
    const char *GetStr() { return str.c_str(); }
    eWho GetWho() { return who; }
};

extern vector<Message> talk;
