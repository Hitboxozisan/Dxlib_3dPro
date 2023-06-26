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
		{ImageType::TrunkGaugeCeneter, "Data/Image/TrunkGaugeCenter.png"},
		{ImageType::TrunkGaugeEdge, "Data/Image/TrunkGaugeEdge.png"},
		{ImageType::TrunkGaugeBack, "Data/Image/TrunkGaugeBack.png"},
	};

	// 各画像のサイズ
	std::unordered_map<ImageType, const float> IMAGE_SIZE
	{
		{ImageType::TitleLogo, 1.0f},
		{ImageType::PlayerHpGauge, 0.8f},
		{ImageType::TrunkGaugeEdge, 0.02f},
		{ImageType::TrunkGaugeCeneter, 0.6f},
		{ImageType::TrunkGaugeBack, 1.5f},
	};
}