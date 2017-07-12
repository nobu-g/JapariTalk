#include "Talk.h"
#include "Screen.h"
#include <Windows.h>
#include <map>

vector<Message> talk;                       // チャットログ
Voice *pVoice = NULL;                       // 音声クラス
unordered_map<eVoice, int> Voice::hVoice;   // 音声ハンドル

Message::Message(string s, eWho w)
{
    str = s;
    who = w;
    head_index.push_back(0);                // 1行目の先頭の添え字は0

    auto index = 0;                         // 文字列の添え字
    auto offset = 0;                        // 行の先頭を指す

    // 文字列を複数の幅 MAX_ROW_WIDTH 以下の行に分割する
    while (1) {
        index += MAX_ROW_WIDTH / FONT_SIZE; // 想定しうる1行あたりの最小文字数からスタート

        while (index < s.length()) {        // 文字列の最後に到達するまでループ
            const auto sub = s.substr(offset, index - offset + 1);    // 行頭からs[index]までの文字列
            const auto partial_width = GetDrawStringWidthToHandle(sub.c_str(), (int)sub.size(), Screen::GetMainFont());
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
        width = GetDrawStringWidthToHandle(s.c_str(), (int)s.size(), Screen::GetMainFont());
    else
        width = MAX_ROW_WIDTH;

    pVoice->Speak(s);                        // 音声を流す
}

string Message::GetRow(int i) const 
{
    if (i + 1 > GetRowNum())
        return nullptr;

    auto charnum = 0;                                   // 指定された行の文字数
    if (i + 1 == GetRowNum())                           // 最後の行を指定されたとき
        charnum = (int)str.size() - head_index[i];
    else
        charnum = head_index[i + 1] - head_index[i];    // 最後以外の行の時

   return str.substr(head_index[i], charnum);
}

Voice::Voice()
{
    if (hVoice.empty()) {
        hVoice.insert(pair<eVoice, int>(eVoice::Omakase,    LoadSoundMem("snd\\omakase.wav")));
        hVoice.insert(pair<eVoice, int>(eVoice::Sawaguhodo, LoadSoundMem("snd\\sawaguhodo.wav")));
        hVoice.insert(pair<eVoice, int>(eVoice::Suggo_i,    LoadSoundMem("snd\\suggo-i.wav")));
        hVoice.insert(pair<eVoice, int>(eVoice::Tabenaide,  LoadSoundMem("snd\\tabenaide.wav")));
        hVoice.insert(pair<eVoice, int>(eVoice::Tabenaiyo,  LoadSoundMem("snd\\tabenaiyo.wav")));
        hVoice.insert(pair<eVoice, int>(eVoice::Wa_i,       LoadSoundMem("snd\\wa-i.wav")));
        hVoice.insert(pair<eVoice, int>(eVoice::Wakaran,    LoadSoundMem("snd\\wakaran.wav")));
    }

    hPlaying = -1;
}

void Voice::Speak(string str)
{
    multimap<size_t, int> table;

    table.insert(pair<size_t, int>(min(str.find("お任せ"), str.find("おまかせ")), hVoice.at(eVoice::Omakase)));
    table.insert(pair<size_t, int>(min(str.find("騒ぐほどでも"), str.find("さわぐほどでも")), hVoice.at(eVoice::Sawaguhodo)));
    table.insert(pair<size_t, int>(min(str.find("すっごーい"), str.find("すっごい")), hVoice.at(eVoice::Suggo_i)));
    table.insert(pair<size_t, int>(min(str.find("食べないで"), str.find("たべないで")), hVoice.at(eVoice::Tabenaide)));
    table.insert(pair<size_t, int>(min(str.find("食べないよ"), str.find("たべないよ")), hVoice.at(eVoice::Tabenaiyo)));
    table.insert(pair<size_t, int>(min(str.find("わーい"), min(str.find("たのしー"), str.find("たーのしー"))), hVoice.at(eVoice::Wa_i)));
    table.insert(pair<size_t, int>(min(str.find("分からん"), str.find("わからん")), hVoice.at(eVoice::Wakaran)));

    if(begin(table)->first != -1)
        PlaySoundMem(begin(table)->second, DX_PLAYTYPE_BACK);
}
