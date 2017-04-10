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
    SetWindowText("chat - guest");
}

void Main::Run()
{
    Network network;

    // �ڑ����������邩ESC�L�[���������܂Ń��[�v
    while (MessageLoop() && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && !network.TryConnect()) {
        DrawString(0, 0, "�ڑ���...", 0x000000);
    }

    // �ڑ�����Ă����玟�ɐi��
    if (network.isConnected()) {

        while (MessageLoop() && network.Update()) {

            network.Draw();

            static bool pre_key_status = true;
            // �X�y�[�X�L�[�������ꂽ�Ƃ��f�[�^�𑗐M
            if (!pre_key_status && CheckHitKey(KEY_INPUT_SPACE))
                network.Send();
            pre_key_status = (CheckHitKeyAll() != 0);
        }



        // �ؒf�m�F�\��
        DrawString(0, 16, "�ؒf���܂���", GetColor(255, 255, 255));
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
    ip = HOST_IP;  // IP�A�h���X��ݒ�
    hNet = -1;
}

bool Network::TryConnect()
{
    static unsigned cnt = 0;

    if (cnt % 180 == 0)
        hNet = ConnectNetWork(ip, HOST_PORT);  // �ʐM���m��
    cnt++;

    return hNet != -1;
}

bool Network::isConnected()
{
    return hNet != -1;
}

bool Network::Update()
{
    int data_len;           // ��M�f�[�^�ʕۑ��p�ϐ�
    char strbuf[256];       // �f�[�^�o�b�t�@

    data_len = GetNetWorkDataLength(hNet);

    // �擾���Ă��Ȃ���M�f�[�^�ʂ�0�ȊO�̂Ƃ�
    if (data_len != 0) {
        NetWorkRecv(hNet, strbuf, data_len);            // �f�[�^���o�b�t�@�Ɏ擾
        talk.push_back(strbuf);
    }

    // �ʐM���ؒf���ꂽ�ꍇfalse��Ԃ�
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
    // �f�[�^���M
    NetWorkSend(hNet, "�q���������`�I�H", 17);
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
