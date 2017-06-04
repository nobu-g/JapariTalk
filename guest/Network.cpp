#include "Network.h"

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
