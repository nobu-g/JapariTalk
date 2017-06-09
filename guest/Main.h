#pragma once

#include "DxLib.h"

// DPIに応じてパーツをスケーリング
extern double scale;
#define SCALE(arg)    ((int) ((arg) * scale))

#define FONT_SIZE   SCALE(15)       // 使用する主なフォントの大きさ

// メインクラス
class Main {
public:
    void Init();
    void Run();
    bool MessageLoop();
    void End();
};
