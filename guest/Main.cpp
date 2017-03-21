#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    char strbuf[256];   // �f�[�^�o�b�t�@
    int hNet, hLost;    // �l�b�g���[�N�n���h��
    int data_len;       // ��M�f�[�^�ʕۑ��p�ϐ�
    IPDATA ip;          // �ڑ���IP�A�h���X�f�[�^

    SetBackgroundColor(200, 200, 200);
    ChangeWindowMode(TRUE);
    if (DxLib_Init() == -1)
        return -1;

    SetWindowText("chat - guest");

    // �ڑ����Ă���̂�҂�Ԃɂ���
    PreparationListenNetWork(9850);

    // �ڑ����Ă��邩ESC�L�[���������܂Ń��[�v
    hNet = -1;
    while (!ProcessMessage() && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
        // �V�����ڑ����������炻�̃l�b�g���[�N�n���h���𓾂�
        hNet = GetNewAcceptNetWork();
        if (hNet != -1)  break;
    }

    // �ڑ�����Ă����玟�ɐi��
    if (hNet != -1) {
        // �ڑ��̎�t���I������
        StopListenNetWork();

        // �ڑ����Ă����}�V����IP�A�h���X�𓾂�
        GetNetWorkIP(hNet, &ip);

        // �f�[�^�������ė���܂ő҂�
        while (!ProcessMessage()) {
            // �擾���Ă��Ȃ���M�f�[�^�ʂ�0�ȊO�̂Ƃ��̓��[�v���甲����
            if (GetNetWorkDataLength(hNet) != 0) break;
        }

        // �f�[�^��M
        data_len = GetNetWorkDataLength(hNet);  // �f�[�^�̗ʂ��擾
        NetWorkRecv(hNet, strbuf, data_len);    // �f�[�^���o�b�t�@�Ɏ擾

        // ��M�����f�[�^��`��
        DrawString(0, 0, strbuf, GetColor(255, 255, 255));

        // ��M�����̃f�[�^�𑗐M
        NetWorkSend(hNet, "�q���������`�I�I", 17);

        // ���肪�ʐM��ؒf����܂ő҂�
        while (!ProcessMessage()) {
            // �V���ɐؒf���ꂽ�l�b�g���[�N�n���h���𓾂�
            hLost = GetLostNetWork();

            // �ؒf���ꂽ�ڑ������܂ŒʐM���Ă����肾�����ꍇ���[�v�𔲂���
            if (hLost == hNet)   break;
        }

        // �ؒf�m�F�\��
        DrawString(0, 16, "�ؒf���܂���", GetColor(255, 255, 255));

        WaitKey();
    }

    DxLib_End();

    return 0;
}
