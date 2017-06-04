#include "Main.h"
#include "Network.h"
#include "Input.h"

void Main::Init()
{
    SetAlwaysRunFlag(TRUE);
    SetBackgroundColor(200, 200, 200);
    SetDoubleStartValidFlag(TRUE);
    ChangeWindowMode(TRUE);
    if (DxLib_Init() == -1)
        exit(1);

    SetDrawScreen(DX_SCREEN_BACK);
    SetWindowText("chat - guest");
}

void Main::Run()
{
    Network network;

    // 接続が完了するかESCキーが押されるまでループ
    while (MessageLoop() && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && !network.TryConnect()) {
        DrawString(0, 0, "接続中...", 0x000000);
    }

    // 接続されていたら次に進む
    if (network.isConnected()) {

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

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Main main_ob;

    main_ob.Init();
    main_ob.Run();
    main_ob.End();

    return 0;
}
