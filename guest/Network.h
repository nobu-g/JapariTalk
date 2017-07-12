#pragma once

#include "DxLib.h"
#include <vector>
#include <string>
using namespace std;

class Network {
    IPDATA ip;              // 接続先IPアドレスデータ
    int port;               // 接続先ホストのポート番号
    int hNet;               // ネットワークハンドル
public:
    Network();
    bool TryConnect();      // 相手マシンに接続を試行
    bool isConnected();     // 接続が成功したかどうか
    bool Update();          // 毎ループ実行
    void Send(string &msg); // 相手マシンにデータを送信
};
