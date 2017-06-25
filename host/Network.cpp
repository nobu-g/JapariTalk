#include "Network.h"
#include "../guest/Talk.h"

Network::Network()
{
    hNet = -1;
}

void Network::StartListen()
{
    PreparationListenNetWork(PORT);
}

bool Network::Listen()
{
    hNet = GetNewAcceptNetWork();

    return hNet != -1;
}

bool Network::isConnected()
{
    return hNet != -1;
}

void Network::Establish()
{
    // 接続の受付を終了する
    StopListenNetWork();

    // 接続してきたマシンのIPアドレスを得る
    GetNetWorkIP(hNet, &ip);
}

bool Network::Update()
{
    int data_len;           // 受信データ量保存用変数
    char strbuf[256] = {};  // データバッファ

    data_len = GetNetWorkDataLength(hNet);

    // 取得していない受信データ量が0以外のとき
    if (data_len != 0) {
        NetWorkRecv(hNet, strbuf, data_len);            // データをバッファに取得
        talk.push_back(Message(strbuf, You));
    }

    // 通信が切断された場合falseを返す
    if (GetLostNetWork() == hNet)
        return false;

    return true;
}

void Network::Send(string &msg)
{
    // データ送信
    NetWorkSend(hNet, msg.c_str(), (int)msg.length() + 1);
}
