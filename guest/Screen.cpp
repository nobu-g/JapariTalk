#include "Screen.h"
#include "Talk.h"

int Screen::hFont;

Screen::Screen()
{
    hFont = CreateFontToHandle("HGSｺﾞｼｯｸM", FONT_SIZE, 0, DX_FONTTYPE_ANTIALIASING_4X4);
    switch (SCALE(480)) {
    case 480:   hIcon = LoadGraph("talkicon96.png");    break;
    case 600:   hIcon = LoadGraph("talkicon120.png");   break;
    case 720:   hIcon = LoadGraph("talkicon144.png");   break;
    }
}

Screen::~Screen()
{
    DeleteFontToHandle(hFont);
}

void Screen::Update()
{
}

void Screen::Draw()
{
    int pos = 0;            // 描画し終えたy方向のピクセル数

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
}

void Screen::DrawBaloon(const Message &msg, int pos)
{
    int w = msg.GetWidth();
    int h = ROW_HIGHT * msg.GetRowNum() - RAD;
    int x = (msg.isMyMsg()) ? (MAXPIX_X - BOX_MARGIN - RAD - w) : (ICON_SPACE + BOX_MARGIN + RAD);
    int y = pos + HALF_MARGIN + RAD;
    int color = (msg.isMyMsg()) ? 0x01b901 : 0xffffff;

    // 角の丸い長方形を描く
    DrawBox(x,       y - RAD, x + w + 1,       y + h + 1 + RAD, color, TRUE);
    DrawBox(x - RAD, y,       x + w + 1 + RAD, y + h + 1,       color, TRUE);
    DrawCircleAA(x,     y,     RAD, 32, color, TRUE);
    DrawCircleAA(x,     y + h, RAD, 32, color, TRUE);
    DrawCircleAA(x + w, y,     RAD, 32, color, TRUE);
    DrawCircleAA(x + w, y + h, RAD, 32, color, TRUE);

    // 吹き出しの三角形を描く
    if (msg.isMyMsg())
        DrawTriangleAA(MAXPIX_X - SPACE + 1, y - RAD / 2, MAXPIX_X - BOX_MARGIN + 1, y, MAXPIX_X - BOX_MARGIN + 1, y + SCALE(7), color, TRUE);
    else
        DrawTriangleAA(SPACE + ICON_SPACE, y - RAD / 2, ICON_SPACE + BOX_MARGIN, y, ICON_SPACE + BOX_MARGIN, y + SCALE(7), color, TRUE);
}

int Screen::GetMainFont()
{
    return hFont;
}
