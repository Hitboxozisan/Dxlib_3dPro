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
/// �t�H���g��������
/// main.cpp�Ŏ��s
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
		printfDx("�G���[�A�t�H���g�ǂݍ��ݎ��s");
	}
}
