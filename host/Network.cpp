#include "Network.h"
#include "../guest/Talk.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/optional.hpp>

using namespace std;
using namespace boost::property_tree;

Network::Network()
{
    ptree pt;
    read_ini("portdata.ini", pt);

    if (auto value = pt.get_optional<int>("PORT"))
        port = value.get();
    else
        port = 50000;

    hNet = -1;
}

void Network::StartListen()
{
    PreparationListenNetWork(port);
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
    int data_len;                   // 受信データ量保存用変数
    char strbuf[MAX_STR_LEN] = {};  // データバッファ

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
