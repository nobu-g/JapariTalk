#include "Screen.h"
#include "Talk.h"

int Screen::hFont = -1;
int Screen::hBackground = -1;
int Screen::hIcon = -1;

Screen::Screen()
{
    if(hFont == -1)
        hFont = CreateFontToHandle("HGSｺﾞｼｯｸM", FONT_SIZE, 0, DX_FONTTYPE_ANTIALIASING_4X4);
    
    if (hBackground == -1) {
        switch (SCALE(480)) {
        case 480:   hBackground = LoadGraph("img\\background96.png");   break;
        case 600:   hBackground = LoadGraph("img\\background120.png");  break;
        case 720:   hBackground = LoadGraph("img\\background144.png");  break;
        }
    }
    if (hIcon == -1) {
        switch (SCALE(480)) {
        case 480:   hIcon = LoadGraph("img\\talkicon96.png");   break;
        case 600:   hIcon = LoadGraph("img\\talkicon120.png");  break;
        case 720:   hIcon = LoadGraph("img\\talkicon144.png");  break;
        }
    }

    offset = 0;
}

Screen::~Screen()
{
    DeleteFontToHandle(hFont);
}

int GetTalkHight()
{
    auto result = 0;

    for (int i = 0; i < talk.size(); i++)
        result += MARGIN + ROW_HIGHT * talk[i].GetRowNum() + RAD;

    return result;
}

void Screen::Update()
{
    static int buff;                    // 移動量をバッファリングしておく
    int talkhight;                      // トークを全て表示したときの高さ
    static int pre_talkhight;           // 前ループの総トークの高さ
    static bool pre_keystate = false;   // いずれかのキーが押されていたか

    if ((talkhight = GetTalkHight()) > TALKAREA_H - SCALE(50)) {
        auto moveunit = GetMouseWheelRotVol();
        moveunit += (CheckHitKey(KEY_INPUT_UP) == 1) && !pre_keystate;
        moveunit -= (CheckHitKey(KEY_INPUT_DOWN) == 1) && !pre_keystate;
        buff += moveunit * (MARGIN + FONT_SIZE + RAD * 2) * 2;

        if (talkhight > pre_talkhight)
            buff = (TALKAREA_H - talkhight) - offset;

        offset += buff / 3;
        buff -= buff / 3;
        if (offset > 0) {
            offset = 0;
            buff = 0;
        }
        else if (offset < TALKAREA_H - talkhight - SCALE(50)) {
            offset = TALKAREA_H - talkhight - SCALE(50);
            buff = 0;
        }
    }

    pre_talkhight = talkhight;
    pre_keystate = (CheckHitKeyAll() != 0);
}

void Screen::Draw()
{
    auto pos = offset;         // 描画し終えたy方向のピクセル数

    SetDrawArea(0, 0, SCREEN_W, SCREEN_H);

    DrawGraph(0, 0, hBackground, FALSE);        // 背景

    for (int i = 0; i < talk.size(); i++) {
        if (talk[i].isMyMsg()) {
            DrawBaloon(talk[i], pos);
            for (int j = 0; j < talk[i].GetRowNum(); j++) {
                DrawStringToHandle(MAXPIX_X - (BOX_MARGIN + RAD + talk[i].GetWidth()), pos + HALF_MARGIN + RAD + ROW_HIGHT * j, talk[i].GetRow(j).c_str(), 0x000000, hFont);
            }
        }
        else {
            DrawBaloon(talk[i], pos);
            // 相手のアイコンを描く
            DrawGraph(SPACE, pos + HALF_MARGIN, hIcon, TRUE);
            for (int j = 0; j < talk[i].GetRowNum(); j++) {
                DrawStringToHandle(ICON_SPACE + BOX_MARGIN + RAD, pos + HALF_MARGIN + RAD + ROW_HIGHT * j, talk[i].GetRow(j).c_str(), 0x000000, hFont);
            }
        }
        pos += MARGIN + ROW_HIGHT * talk[i].GetRowNum() + RAD;
    }

    SetDrawArea(0, 0, SCREEN_W, SCREEN_H);
}

void Screen::DrawBaloon(const Message &msg, int pos)
{
    int w = msg.GetWidth() + RAD * 2;
    int h = ROW_HIGHT * msg.GetRowNum() + RAD;
    int x = (msg.isMyMsg()) ? (MAXPIX_X - BOX_MARGIN - w) : (ICON_SPACE + BOX_MARGIN);
    int y = pos + HALF_MARGIN;
    int color = (msg.isMyMsg()) ? 0x90c31f : 0xffffff;  // 0x01b901:緑

    // 角の丸い長方形を描く
    DrawRoundRectAA(x, y, x + w + 1, y + h + 1, RAD, RAD, 32, color, TRUE);

    // 吹き出しの三角形を描く
    if (msg.isMyMsg())
        DrawTriangleAA(MAXPIX_X - SPACE + 1, y + RAD / 2, MAXPIX_X - BOX_MARGIN + 1, y + RAD, MAXPIX_X - BOX_MARGIN + 1, y + RAD + SCALE(7), color, TRUE);
    else
        DrawTriangleAA(SPACE + ICON_SPACE, y + RAD / 2, ICON_SPACE + BOX_MARGIN, y + RAD, ICON_SPACE + BOX_MARGIN, y +RAD + SCALE(7), color, TRUE);
}

int Screen::GetMainFont()
{
    return hFont;
}
