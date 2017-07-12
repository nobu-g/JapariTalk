#include "Network.h"
#include "Talk.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/optional.hpp>
#include <boost/spirit/include/qi.hpp>

using namespace std;
using namespace boost::property_tree;
namespace qi = boost::spirit::qi;

Network::Network()
{
    ptree pt;
    read_ini("ipdata.ini", pt);

    ip = { 127, 0, 0, 1 };
    if (auto value = pt.get_optional<string>("IP")) {
        auto it = begin(value.get());

        qi::parse(
            it, end(value.get()),
            qi::ushort_ >> '.' >> qi::ushort_ >> '.' >> qi::ushort_ >> '.' >> qi::ushort_,
            ip.d1, ip.d2, ip.d3, ip.d4
        );
    }        

    if (auto value = pt.get_optional<int>("PORT"))
        port = value.get();
    else
        port = 50000;

    hNet = -1;
}

bool Network::TryConnect()
{
    static unsigned cnt = 0;

    if (cnt % 180 == 0)
        hNet = ConnectNetWork(ip, port);  // 通信を確立
    cnt++;

    return hNet != -1;
}

bool Network::isConnected()
{
    return hNet != -1;
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
