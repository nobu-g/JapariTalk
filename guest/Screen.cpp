#include "Screen.h"
#include "Talk.h"

int Screen::hFont;

Screen::Screen()
{
    hFont = CreateFontToHandle("HGSｺﾞｼｯｸM", FONT_SIZE, 0, DX_FONTTYPE_ANTIALIASING_4X4);
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
                DrawStringToHandle(SCREEN_W - (SIDE_MARGIN + RAD + talk[i].GetWidth()), pos + HALF_MARGIN + RAD + ROW_HIGHT * j, talk[i].GetRow(j).c_str(), 0x000000, hFont);
            }
        }
        else {
            DrawBaloon(talk[i], pos);
            for (int j = 0; j < talk[i].GetRowNum(); j++) {
                DrawStringToHandle(SIDE_MARGIN + RAD, pos + HALF_MARGIN + RAD + ROW_HIGHT * j, talk[i].GetRow(j).c_str(), 0x000000, hFont);
            }
        }
        pos += MARGIN + ROW_HIGHT * talk[i].GetRowNum() + RAD;
    }
}

void Screen::DrawBaloon(const Message &msg, int pos)
{
    int w = msg.GetWidth();
    int h = ROW_HIGHT * msg.GetRowNum() - RAD;
    int x = (msg.isMyMsg()) ? (SCREEN_W - SIDE_MARGIN - RAD - w) : (SIDE_MARGIN + RAD);
    int y = pos + HALF_MARGIN + RAD;
    int color = (msg.isMyMsg()) ? 0x01b901 : 0xffffff;

    // 角の丸い長方形を描く
    DrawBox(x,       y - RAD, x + w + 1,       y + h + 1 + RAD, color, TRUE);
    DrawBox(x - RAD, y,       x + w + 1 + RAD, y + h + 1,       color, TRUE);
    DrawCircle(x,     y,     RAD, color, TRUE);
    DrawCircle(x,     y + h, RAD, color, TRUE);
    DrawCircle(x + w, y,     RAD, color, TRUE);
    DrawCircle(x + w, y + h, RAD, color, TRUE);

    // 吹き出しの三角形を描く
    if (msg.isMyMsg())
        DrawTriangle(SCREEN_W - SCALE(5), y - RAD, SCREEN_W - SIDE_MARGIN, y, SCREEN_W - SIDE_MARGIN, y + SCALE(7), color, TRUE);
    else
        DrawTriangle(SCALE(5), y - RAD, SIDE_MARGIN, y, SIDE_MARGIN, y + SCALE(7), color, TRUE);

}

int Screen::GetMainFont()
{
    return hFont;
}
