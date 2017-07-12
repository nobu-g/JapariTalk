#pragma once

#include "DxLib.h"

#define SCREEN_W    SCALE(480)
#define SCREEN_H    SCALE(480)

#define MAX_STR_LEN     1024    // 一度に入力可能な最大文字数(半角文字単位)('\0'込み)

// DPIに応じてパーツをスケーリング
extern double scale;
#define SCALE(arg)    ((int) ((arg) * scale))

// メインクラス
class Main {
public:
    void Init();
    void Run();
    bool MessageLoop();
    void End();
};
