#pragma once

#include "DxLib.h"

#define SCREEN_W    SCALE(480)
#define SCREEN_H    SCALE(480)

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
