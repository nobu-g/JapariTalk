#include "Main.h"

void Main::Init()
{
    SetAlwaysRunFlag(TRUE);
    SetBackgroundColor(200, 200, 200);
    SetDoubleStartValidFlag(TRUE);
    ChangeWindowMode(TRUE);
    if (DxLib_Init() == -1)
        exit(1);

    SetDrawScreen(DX_SCREEN_BACK);
    SetWindowText("chat - host");
}

void Main::Run()
{
    Network network;

    // 接続してくるのを待つ状態にする
    network.StartListen();

    // 接続してくるかESCキーが押されるまでループ
    while (MessageLoop() && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && !network.Listen()) {
        DrawString(0, 0, "接続中...", 0x000000);
    }

    // 接続されていたら次に進む
    if (network.isConnected()) {
        network.Establish();

        while (MessageLoop() && network.Update()) {

            network.Draw();

            static bool pre_key_status = true;
            // スペースキーが押されたときデータを送信
            if (!pre_key_status && CheckHitKey(KEY_INPUT_SPACE))
                network.Send();
            pre_key_status = (CheckHitKeyAll() != 0);
        }



        // 切断確認表示
        DrawString(0, 16, "切断しました", GetColor(255, 255, 255));
        ScreenFlip();

        WaitKey();
        WaitKey();
        WaitKey();
    }
}

bool Main::MessageLoop()
{
    return ProcessMessage() == 0 && ScreenFlip() == 0 && ClearDrawScreen() == 0;
}

void Main::End()
{
    DxLib_End();
}

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
    // 受信成功のデータを送信
    NetWorkSend(hNet, "繋がったぞ～！！", 17);
}

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Main main_ob;

    main_ob.Init();
    main_ob.Run();
    main_ob.End();

    return 0;
}
