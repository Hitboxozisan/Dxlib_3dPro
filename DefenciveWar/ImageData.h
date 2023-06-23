#pragma once
#include <unordered_map>
#include <string.h>
#include "ImageTypeData.h"

namespace ImageData
{
	// 各画像のファイルパス
	std::unordered_map<ImageType, const std::string> FILE_PATH
	{
		{ImageType::TitleLogo, "Data/Image/TitleLogo.png"},
		{ImageType::PlayerHpGauge, "Data/Image/PlayerHpGauge.png"},
	};
}