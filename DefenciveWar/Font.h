#pragma once

/// <summary>
/// �t�H���g�N���X
/// �V���O���g��
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

