#pragma once

#include "DxLib.h"
#include "Main.h"
#include "Talk.h"

#define FONT_SIZE       SCALE(13)           // 使用する主なフォントの大きさ
#define RAD             SCALE(5)            // 吹き出し四隅の曲率半径
#define ROW_HIGHT       (FONT_SIZE + RAD)   // 1行の高さ
#define HALF_MARGIN     SCALE(5)            // 吹き出し間の余白の半分
#define MARGIN          (HALF_MARGIN * 2)   // 吹き出し間の余白
#define SIDE_MARGIN     SCALE(13)           // 吹き出しと画面端の幅

class Screen {
    static int hFont;
public:
    Screen();
    ~Screen();
    void Update();
    void Draw();
    void DrawBaloon(const Message &msg, int row);
    static int GetMainFont();
};
