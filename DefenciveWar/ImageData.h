#pragma once
#include <unordered_map>
#include <string.h>
#include "ImageTypeData.h"

namespace ImageData
{
	// �e�摜�̃t�@�C���p�X
	std::unordered_map<ImageType, const std::string> FILE_PATH
	{
		{ImageType::TitleLogo, "Data/Image/TitleLogo.png"},
		{ImageType::PlayerHpGauge, "Data/Image/PlayerHpGauge.png"},
	};
}