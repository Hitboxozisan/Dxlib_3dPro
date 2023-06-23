#pragma once

#include <unordered_map>
#include "Player.h"
#include "BossEnemy.h"

enum class ObjectType
{
	Player,
	BossEnemy,
};

/// <summary>
/// ゲームオブジェクトのデータを取得するためのクラス
/// </summary>
class ObjectData final
{
public:
	ObjectData(SceneGame* game) {};
	~ObjectData() {};

private:


};
