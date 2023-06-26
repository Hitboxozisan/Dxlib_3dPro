#include "common.h"
#include "ImageManager.h"
#include "EnumIterator.h"
#include "ImageData.h"

using namespace ImageData;

ImageManager::ImageManager()
{
	// 列挙型のイテレータを作成
	typedef EnumIterator<ImageType, ImageType::TitleLogo, ImageType::ImageAmount> itItr;

	for (auto itr : itItr())
	{
		images[itr] = LoadGraph(FILE_PATH[itr].c_str());
	}

	for (auto itr : itItr())
	{
		size[itr] = IMAGE_SIZE[itr];
	}

}

ImageManager::~ImageManager()
{

}
