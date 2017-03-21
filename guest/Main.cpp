#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    char strbuf[256];   // データバッファ
    int hNet, hLost;    // ネットワークハンドル
    int data_len;       // 受信データ量保存用変数
    IPDATA ip;          // 接続先IPアドレスデータ

    SetBackgroundColor(200, 200, 200);
    ChangeWindowMode(TRUE);
    if (DxLib_Init() == -1)
        return -1;

    SetWindowText("chat - guest");

    // 接続してくるのを待つ状態にする
    PreparationListenNetWork(9850);

    // 接続してくるかESCキーが押されるまでループ
    hNet = -1;
    while (!ProcessMessage() && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
        // 新しい接続があったらそのネットワークハンドルを得る
        hNet = GetNewAcceptNetWork();
        if (hNet != -1)  break;
    }

    // 接続されていたら次に進む
    if (hNet != -1) {
        // 接続の受付を終了する
        StopListenNetWork();

        // 接続してきたマシンのIPアドレスを得る
        GetNetWorkIP(hNet, &ip);

        // データが送られて来るまで待つ
        while (!ProcessMessage()) {
            // 取得していない受信データ量が0以外のときはループから抜ける
            if (GetNetWorkDataLength(hNet) != 0) break;
        }

        // データ受信
        data_len = GetNetWorkDataLength(hNet);  // データの量を取得
        NetWorkRecv(hNet, strbuf, data_len);    // データをバッファに取得

        // 受信したデータを描画
        DrawString(0, 0, strbuf, GetColor(255, 255, 255));

        // 受信成功のデータを送信
        NetWorkSend(hNet, "繋がったぞ～！！", 17);

        // 相手が通信を切断するまで待つ
        while (!ProcessMessage()) {
            // 新たに切断されたネットワークハンドルを得る
            hLost = GetLostNetWork();

            // 切断された接続が今まで通信してた相手だった場合ループを抜ける
            if (hLost == hNet)   break;
        }

        // 切断確認表示
        DrawString(0, 16, "切断しました", GetColor(255, 255, 255));

        WaitKey();
    }

    DxLib_End();

    return 0;
}
