#include "common.h"
#include "Font.h"

Font::Font()
	:fontHandle(0)
{
}

Font::~Font()
{
}

/// <summary>
/// フォント生成する
/// main.cppで実行
/// </summary>
/// <param name="fontName"></param>
/// <param name="inSize"></param>
/// <param name="inThick"></param>
/// <param name="fontType"></param>
void Font::SetFont(std::string fontName, int inSize, int inThick, int fontType)
{
	fontHandle = CreateFontToHandle(fontName.c_str(), inSize, inThick, fontType);
	if (fontHandle < 0)
	{
		printfDx("エラー、フォント読み込み失敗");
	}
}
