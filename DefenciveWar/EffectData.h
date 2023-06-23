#pragma once

#include <unordered_map>
#include <string.h>
#include "EffectTypeData.h"

namespace EffectData
{
	// �e�G�t�F�N�g�̃t�@�C���p�X
	std::unordered_map<EffectType, const std::string> EFFECT_PATH
	{
		{EffectType::Shield, "Data/Effect/Shield/Shield.efkefc"},
		{EffectType::Hit, "Data/Effect/Hit/Hit.efkefc"},
		{EffectType::LapseBullet, "Data/Effect/Bullet/LapseBullet.efkefc"},
	};

	std::unordered_map<EffectType, const std::string> EFFECT_TEX_PATH
	{

	};

	// �e�G�t�F�N�g�̃T�C�Y
	std::unordered_map<EffectType, float> EFFECT_SIZE
	{
		{EffectType::Shield, 7.0f},
		{EffectType::Hit, 5.0f},
		{EffectType::LapseBullet, 10.0f},
	};
}

