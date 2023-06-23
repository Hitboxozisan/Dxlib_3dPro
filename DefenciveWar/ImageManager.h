#pragma once

#include "ImageTypeData.h"

/// <summary>
/// �Q�[�����2D�摜�Ǘ��N���X
/// �V���O���g��
/// </summary>
class ImageManager final
{
public:
	ImageManager();
	~ImageManager();

	int GetImage(ImageType it) { return images[it]; }
	
private:
	std::map<ImageType, int> images;
};

