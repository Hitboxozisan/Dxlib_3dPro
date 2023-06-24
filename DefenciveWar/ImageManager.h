#pragma once

#include "ImageTypeData.h"

/// <summary>
/// ゲーム上の2D画像管理クラス
/// シングルトン
/// </summary>
class ImageManager final
{
public:
	ImageManager();
	~ImageManager();

	int GetImage(ImageType it) 
	{
		if (images[it] < 0)
		{
			printfDx("Image読み込みエラー_%d", static_cast<int>(it));
		}

		return images[it]; 
	}
	
private:
	std::map<ImageType, int> images;
};

