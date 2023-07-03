#pragma once

#include <unordered_map>
#include <string>
#include "BossAttackTypeData.h"

namespace BossAttackData
{
	// �e�G�t�F�N�g�̃t�@�C���p�X
	std::unordered_map<AttackType, const std::string> EFFECT_PATH
	{
		{AttackType::Assault, "Assault"},
		{AttackType::BulletNomal, "BulletNormal"},
		{AttackType::BulletShotGun, "BulletShotGun"},
		{AttackType::Stomp, "Stomp"},
	};
}