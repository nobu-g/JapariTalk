#pragma once

#include "DxLib.h"
#include <vector>
#include <string>
using namespace std;

#define HOST_IP    { 127, 0, 0, 1 }
#define HOST_PORT  50000

class Network {
    vector<string> talk;
    IPDATA ip;              // �ڑ���IP�A�h���X�f�[�^
    int hNet;               // �l�b�g���[�N�n���h��
public:
    Network();
    bool TryConnect();      // ����}�V���ɐڑ������s
    bool isConnected();     // �ڑ��������������ǂ���
    bool Update();          // �����[�v���s
    void Draw();            // �`��
    void Send();            // ����}�V���Ƀf�[�^�𑗐M
};
