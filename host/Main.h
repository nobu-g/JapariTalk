#pragma once

#include "DxLib.h"
#include <vector>
#include <string>
using namespace std;

#define PORT    50000

// ���C���N���X
class Main {
public:
    void Init();
    void Run();
    bool MessageLoop();
    void End();
};

// �ʐM�N���X
class Network {
    vector<string> talk;    // �`���b�g���O
    int hNet;               // �l�b�g���[�N�n���h��
    IPDATA ip;              // �ڑ���IP�A�h���X�f�[�^
public:
    Network();
    void StartListen();     // �ڑ���t���J�n
    bool Listen();          // �V�����ڑ��������true��Ԃ�
    bool isConnected();     // �ڑ��������������ǂ���
    void Establish();       // �ڑ����m������
    bool Update();          // �����[�v���s
    void Draw();            // �`��
    void Send();            // ����}�V���Ƀf�[�^�𑗐M
};

// �������̓N���X
class Input {

};
