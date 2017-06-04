#pragma once

#include "DxLib.h"
#include <vector>
#include <string>
using namespace std;

#define HOST_IP    { 127, 0, 0, 1 }
#define HOST_PORT  50000

class Network {
    vector<string> talk;
    IPDATA ip;              // 接続先IPアドレスデータ
    int hNet;               // ネットワークハンドル
public:
    Network();
    bool TryConnect();      // 相手マシンに接続を試行
    bool isConnected();     // 接続が成功したかどうか
    bool Update();          // 毎ループ実行
    void Draw();            // 描画
    void Send();            // 相手マシンにデータを送信
};
