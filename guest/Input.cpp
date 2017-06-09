#include"DxLib.h"
#include "Main.h"
#include "Input.h"
#include "Talk.h"

#define BLACK       0x000000
#define WHITE       0xFFFFFF
#define LIGHT_BLUE  0xCDE8FF
#define BLUE        0x0078D7

Input::Input()
{
    // 入力ハンドル作成＆有効化
    hInput = MakeKeyInput(MAX_INPUT_LEN, FALSE, FALSE, FALSE);
    SetActiveKeyInput(hInput);

    // 文字入力用フォント作成
    hFont = CreateFontToHandle("ＭＳ ゴシック", FONT_SIZE, 10);
    SetKeyInputStringFont(hFont);

    // IME設定
    SetKeyInputStringColor(BLACK, BLACK, WHITE, BLACK, BLACK, LIGHT_BLUE, BLACK, BLACK, BLACK, BLACK, BLACK, WHITE, BLUE, WHITE, WHITE, BLACK, BLACK);
    SetKeyInputCursorBrinkFlag(TRUE);
    SetIMEInputStringMaxLength(MAX_INPUT_LEN);
    
    SetKeyInputString("a", hInput);
    DrawKeyInputString(INPUT_BOX_X + 3, INPUT_BOX_Y + 5, hInput);   // 一度文字を描画しないと入力欄が点滅してしまう(バグ?)
    SetKeyInputString("", hInput);
}

Input::~Input()
{
    DeleteKeyInput(hInput);
    DeleteFontToHandle(hFont);
}

string Input::Update()
{
    char buf[MAX_INPUT_LEN];

    if (CheckKeyInput(hInput) == 1) {
        GetKeyInputString(buf, hInput);             // 入力内容を取得
        if (buf[0] != '\0')                         // もし空文字列でなければ
            talk.push_back(Message(buf, Guest));    // 内容を記録
        
        SetActiveKeyInput(hInput);                  // キー入力ハンドルを再び有効化
        SetKeyInputString("", hInput);              // 入力をリセット

        return string(buf);                         // 取得した文字列を返す
    }

    return string();
}

void Input::Draw()
{
    DrawBox(INPUT_BOX_X, INPUT_BOX_Y, INPUT_BOX_X + INPUT_BOX_W, INPUT_BOX_Y + INPUT_BOX_H, 0xffffff, TRUE);
    SetDrawArea(INPUT_BOX_X, INPUT_BOX_Y, INPUT_BOX_X + INPUT_BOX_W - 3, INPUT_BOX_Y + INPUT_BOX_H);
    DrawKeyInputString(INPUT_BOX_X + 5, INPUT_BOX_Y + 5, hInput);
    SetDrawArea(0, 0, SCREEN_W, SCREEN_H);
}
