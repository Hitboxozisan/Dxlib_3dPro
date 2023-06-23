#pragma once

#include <unordered_map>
#include <string.h>
#include "ModelTypeData.h"

namespace ModelData
{
	// 各画像のファイルパス
	std::unordered_map<ModelType, const std::string> FILE_PATH
	{
		{ModelType::Player, "Data/Model/Player/Player.mv1"},
		{ModelType::Enemy, "Data/Model/Enemy/BossEnemy.mv1"},
		{ModelType::Ground, "Data/Model/Ground/Ground.mv1"},
		{ModelType::Bullet, "Data/Model/Bullet/PlayerBullet.mv1"},
		{ModelType::EnemyBullet, "Data/Model/Bullet/EnemyBullet.mv1"},
	};
}
