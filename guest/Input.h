#pragma once

#include <string>
using namespace std;

#define INPUT_BOX_X     SCALE(10)
#define INPUT_BOX_Y     SCALE(450)
#define INPUT_BOX_W     SCALE(400)
#define INPUT_BOX_H     SCALE(20)

class Input {
    int hInput;     // キー入力ハンドル
    int hFont;      // キー入力フォント
public:
    Input();
    ~Input();
    string Update();
    void Draw();
};
