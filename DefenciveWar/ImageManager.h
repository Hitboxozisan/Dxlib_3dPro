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

	int GetImage(const ImageType it) 
	{
		if (images[it] < 0)
		{
			printfDx("Image�ǂݍ��݃G���[_%d", static_cast<int>(it));
		}

		return images[it]; 
	}

	float GetImageSize(const ImageType it) { return size[it]; }
	
private:
	std::map<ImageType, int> images;
	std::map<ImageType, float> size;
};

