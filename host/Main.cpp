#include "DxLib.h"

#define GUEST_IP    { 192, 168, 1, 5 }

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    char strbuf[256];   // �f�[�^�o�b�t�@
    IPDATA ip;          // �ڑ��pIP�A�h���X�f�[�^
    int hNet;           // �l�b�g���[�N�n���h��
    int data_len;       // ��M�f�[�^�ʕۑ��p�ϐ�

    SetBackgroundColor(200, 200, 200);
    ChangeWindowMode(TRUE);
    if (DxLib_Init() == -1)
        return -1;

    SetWindowText("chat - host");

    // IP�A�h���X��ݒ�
    ip = GUEST_IP;

    // �ʐM���m��
    hNet = ConnectNetWork(ip, 9850);

    // �m�������������ꍇ�̂ݒ��̏���������
    if (hNet != -1) {
        // �f�[�^���M
        NetWorkSend(hNet, "�q���������`�I�H", 17);

        // �f�[�^������̂�҂�
        while (!ProcessMessage()) {
            // �擾���Ă��Ȃ���M�f�[�^�ʂ𓾂�
            data_len = GetNetWorkDataLength(hNet);

            // �擾���ĂȂ���M�f�[�^�ʂ�0����Ȃ��ꍇ�̓��[�v�𔲂���
            if (data_len != 0)   break;
        }

        // �f�[�^��M
        NetWorkRecv(hNet, strbuf, data_len);        // �f�[�^���o�b�t�@�Ɏ擾

        // ��M�����f�[�^��`��
        DrawString(0, 0, strbuf, GetColor(255, 255, 255));

        WaitKey();

        // �ڑ���f��
        CloseNetWork(hNet);
    }

    DxLib_End();

    return 0;
}
