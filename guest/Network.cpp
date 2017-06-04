#include "Network.h"

Network::Network()
{
    ip = HOST_IP;  // IPアドレスを設定
    hNet = -1;
}

bool Network::TryConnect()
{
    static unsigned cnt = 0;

    if (cnt % 180 == 0)
        hNet = ConnectNetWork(ip, HOST_PORT);  // 通信を確立
    cnt++;

    return hNet != -1;
}

bool Network::isConnected()
{
    return hNet != -1;
}

bool Network::Update()
{
    int data_len;           // 受信データ量保存用変数
    char strbuf[256];       // データバッファ

    data_len = GetNetWorkDataLength(hNet);

    // 取得していない受信データ量が0以外のとき
    if (data_len != 0) {
        NetWorkRecv(hNet, strbuf, data_len);            // データをバッファに取得
        talk.push_back(strbuf);
    }

    // 通信が切断された場合falseを返す
    if (GetLostNetWork() == hNet)
        return false;

    return true;
}

void Network::Draw()
{
    for (int i = 0; i < talk.size(); i++)
        DrawString(0, i * 20, talk[i].c_str(), GetColor(255, 255, 255));
}

void Network::Send()
{
    // データ送信
    NetWorkSend(hNet, "繋がったか～！？", 17);
}
