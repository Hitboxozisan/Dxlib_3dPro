#pragma once

/// <summary>
/// フォントクラス
/// シングルトン
/// </summary>
class Font
{
public:
	Font();
	~Font();

	void SetFont(std::string fontName, int inSize, int inThick, int fontType);
	const int GetFont() const { return fontHandle; }

private:
	int fontHandle;
};

