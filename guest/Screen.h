#pragma once

#include "DxLib.h"
#include "Main.h"
#include "Talk.h"
#include "Input.h"

#define MAXPIX_X        (SCREEN_W - 1)              // y方向の最大ピクセル座標
#define FONT_SIZE       SCALE(13)                   // 使用する主なフォントの大きさ
#define RAD             SCALE(5)                    // 吹き出し四隅の曲率半径
#define ROW_HIGHT       (FONT_SIZE + RAD)           // 1行の高さ
#define HALF_MARGIN     SCALE(5)                    // 吹き出し間の余白の半分
#define MARGIN          (HALF_MARGIN * 2)           // 吹き出し間の余白
#define SPACE           SCALE(3)                    // 各所の横方向の幅
#define PROT_W          SCALE(8)                    // 吹き出しの突起の幅
#define BOX_MARGIN      (SPACE + PROT_W)            // 吹き出し(自分)のボックスと画面端との幅
#define ICON_SIZE       SCALE(21.8)                 // 相手のアイコンのサイズ
#define ICON_SPACE      (SPACE + ICON_SIZE)         // アイコンの挿入により移動するy方向の量
#define TALKAREA_H      (INPUT_BOX_Y * 2 + INPUT_BOX_H - SCREEN_W)      // トーク表示領域の高さ

class Screen {
    static int hFont;       // 文字フォント
    static int hBackground; // 背景画像
    static int hIcon;       // 相手のトップ画のアイコン
    int offset;             // トーク表示の際の描画開始位置(y方向)
public:
    Screen();
    ~Screen();
    void Update();
    void Draw();
    void DrawBaloon(const Message &msg, int row);
    static int GetMainFont();
};
