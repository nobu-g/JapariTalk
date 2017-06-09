#include"DxLib.h"
#include "Main.h"
#include "Input.h"
#include "Talk.h"

Input::Input()
{
    hInput = MakeKeyInput(MAX_INPUT_LEN, FALSE, FALSE, FALSE);
    SetActiveKeyInput(hInput);

    SetFontSize(FONT_SIZE);
    SetKeyInputStringColor(0x000000, 0x000000, 0xffffff, 0x000000, 0x000000, 0xffffff, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xffffff, 0x0078d7, 0xffffff, 0xffffff, 0x000000, 0x000000);
}

Input::~Input()
{
    DeleteKeyInput(hInput);
}

string Input::Update()
{
    char buf[MAX_INPUT_LEN];

    if (CheckKeyInput(hInput) == 1) {
        GetKeyInputString(buf, hInput);         // 入力内容を取得
        talk.push_back(Message(buf, Guest));     // 内容を記録
        SetActiveKeyInput(hInput);              // キー入力ハンドルを再び有効化
        SetKeyInputString("", hInput);          // 入力をリセット

        return string(buf);                     // 取得した文字列を返す
    }

    return string();
}

void Input::Draw()
{
    DrawBox(INPUT_BOX_X, INPUT_BOX_Y, INPUT_BOX_X + INPUT_BOX_W, INPUT_BOX_Y + INPUT_BOX_H, 0xffffff, TRUE);
    
    DrawKeyInputString(INPUT_BOX_X + 3, INPUT_BOX_Y + 3, hInput);
}
