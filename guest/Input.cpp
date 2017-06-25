#include"DxLib.h"
#include "Input.h"
#include "Talk.h"
#include "Screen.h"

#define BLACK       0x000000
#define WHITE       0xFFFFFF
#define LIGHT_BLUE  0xCDE8FF
#define BLUE        0x0078D7

Input::Input()
{
    // 入力ハンドル作成＆有効化
    hInput = MakeKeyInput(MAX_INPUT_LEN - 1, FALSE, FALSE, FALSE);
    SetActiveKeyInput(hInput);

    // 文字入力用フォント作成
    hFont = CreateFontToHandle("HGSｺﾞｼｯｸM", FONT_SIZE, 0, DX_FONTTYPE_ANTIALIASING_4X4);
    SetKeyInputStringFont(hFont);

    // IME設定
    SetKeyInputStringColor(BLACK, BLACK, WHITE, BLACK, BLACK, LIGHT_BLUE, BLACK, BLACK, BLACK, BLACK, BLACK, WHITE, BLUE, WHITE, WHITE, BLACK, BLACK);
    SetIMEInputStringMaxLength(MAX_INPUT_LEN - 1);
    
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
            talk.push_back(Message(buf, Me));       // 内容を記録
        
        SetActiveKeyInput(hInput);                  // キー入力ハンドルを再び有効化
        SetKeyInputString("", hInput);              // 入力をリセット

        return string(buf);                         // 取得した文字列を返す
    }

    return string();
}

void Input::Draw()
{
    DrawBox(INPUT_BOX_X, INPUT_BOX_Y, INPUT_BOX_X + INPUT_BOX_W, INPUT_BOX_Y + INPUT_BOX_H, 0xffffff, TRUE);
    DrawBox(INPUT_BOX_X - 1, INPUT_BOX_Y - 1, INPUT_BOX_X + INPUT_BOX_W + 1, INPUT_BOX_Y + INPUT_BOX_H + 1, 0xb0b0b0, FALSE);

    static bool pre_active_flag = false;

    // ウインドウが非アクティブになったらカーソルの点滅を止める
    if(pre_active_flag != (bool)GetWindowActiveFlag())
        SetKeyInputCursorBrinkFlag(!pre_active_flag);

    SetDrawArea(INPUT_BOX_X, INPUT_BOX_Y, INPUT_BOX_X + INPUT_BOX_W - 3, INPUT_BOX_Y + INPUT_BOX_H);
    DrawKeyInputString(INPUT_BOX_X + 5, INPUT_BOX_Y + 5, hInput);
    SetDrawArea(0, 0, SCREEN_W, SCREEN_H);

    pre_active_flag = GetWindowActiveFlag();
}
