#pragma once

#include <string>
using namespace std;

#define MAX_INPUT_LEN   64      // 一度に入力可能な最大文字数(半角文字単位)

#define INPUT_BOX_X     SCALE(10)
#define INPUT_BOX_Y     SCALE(450)
#define INPUT_BOX_W     SCALE(250)
#define INPUT_BOX_H     SCALE(21)

class Input {
    int hInput;     // キー入力ハンドル
public:
    Input();
    ~Input();
    string Update();
    void Draw();
};