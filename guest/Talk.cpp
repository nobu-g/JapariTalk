#include "Talk.h"
#include "Screen.h"
#include <Windows.h>

vector<Message> talk;       // チャットログ

Message::Message(string s, eWho w)
{
    str = s;
    who = w;
    head_index.push_back(0);                // 1行目の先頭の添え字は0

    int index = 0;                          // 文字列の添え字
    int offset = 0;                         // 行の先頭を指す

    // 文字列を複数の幅 MAX_ROW_WIDTH 以下の行に分割する
    while (1) {
        index += MAX_ROW_WIDTH / FONT_SIZE; // 想定しうる1行あたりの最小文字数からスタート

        while (index < s.length()) {        // 文字列の最後に到達するまでループ
            const string sub = s.substr(offset, index - offset + 1);    // 行頭からs[index]までの文字列
            const int partial_width = GetDrawStringWidthToHandle(sub.c_str(), sub.size(), Screen::GetMainFont());
            if (partial_width > MAX_ROW_WIDTH)
                break;

            index++;
        }
        if (index >= s.length())            // 文字列sを最後まで走査し終えたとき
            break;

        if (IsDBCSLeadByte(s[index - 1]))   // s[index]がマルチバイト文字の先行バイトだった場合は補正
            index--;
        offset = index;
        head_index.push_back(index);        // s[index]が次の行の先頭になる
    }

    if (offset == 0)                        // メッセージが1行で終わったとき
        width = GetDrawStringWidthToHandle(s.c_str(), s.size(), Screen::GetMainFont());
    else
        width = MAX_ROW_WIDTH;
}

string Message::GetRow(int i) const 
{
    if (i + 1 > GetRowNum())
        return nullptr;

    int charnum;                                        // 指定された行の文字数
    if (i + 1 == GetRowNum())                           // 最後の行を指定されたとき
        charnum = str.size() - head_index[i];
    else
        charnum = head_index[i + 1] - head_index[i];    // 最後以外の行の時

   return str.substr(head_index[i], charnum);
}
