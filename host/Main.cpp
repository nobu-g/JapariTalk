#include "DxLib.h"

#define GUEST_IP    { 192, 168, 1, 5 }

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    char strbuf[256];   // データバッファ
    IPDATA ip;          // 接続用IPアドレスデータ
    int hNet;           // ネットワークハンドル
    int data_len;       // 受信データ量保存用変数

    SetBackgroundColor(200, 200, 200);
    ChangeWindowMode(TRUE);
    if (DxLib_Init() == -1)
        return -1;

    SetWindowText("chat - host");

    // IPアドレスを設定
    ip = GUEST_IP;

    // 通信を確立
    hNet = ConnectNetWork(ip, 9850);

    // 確立が成功した場合のみ中の処理をする
    if (hNet != -1) {
        // データ送信
        NetWorkSend(hNet, "繋がったか～！？", 17);

        // データがくるのを待つ
        while (!ProcessMessage()) {
            // 取得していない受信データ量を得る
            data_len = GetNetWorkDataLength(hNet);

            // 取得してない受信データ量が0じゃない場合はループを抜ける
            if (data_len != 0)   break;
        }

        // データ受信
        NetWorkRecv(hNet, strbuf, data_len);        // データをバッファに取得

        // 受信したデータを描画
        DrawString(0, 0, strbuf, GetColor(255, 255, 255));

        WaitKey();

        // 接続を断つ
        CloseNetWork(hNet);
    }

    DxLib_End();

    return 0;
}
