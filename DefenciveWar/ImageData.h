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
		{ImageType::TrunkGaugeCeneter, "Data/Image/TrunkGaugeCenter.png"},
		{ImageType::TrunkGaugeEdge, "Data/Image/TrunkGaugeEdge.png"},
		{ImageType::TrunkGaugeBack, "Data/Image/TrunkGaugeBack.png"},
	};

	// �e�摜�̃T�C�Y
	std::unordered_map<ImageType, const float> IMAGE_SIZE
	{
		{ImageType::TitleLogo, 1.0f},
		{ImageType::PlayerHpGauge, 0.8f},
		{ImageType::TrunkGaugeEdge, 0.02f},
		{ImageType::TrunkGaugeCeneter, 0.6f},
		{ImageType::TrunkGaugeBack, 1.5f},
	};
}