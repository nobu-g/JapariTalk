#pragma once

#include "DxLib.h"
#include <vector>
#include <string>
using namespace std;

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
