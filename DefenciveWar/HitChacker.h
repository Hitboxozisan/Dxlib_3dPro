#pragma once

#include <unordered_map>
#include "Collision.h"

/// <summary>
/// 当たり判定処理・対応処理を行うクラス
/// </summary>
class HitChacker final
{
public:
	HitChacker();
	~HitChacker();

	void Update();
	void Draw();
	void Chack();
	void EntryCollide(Collision* collide);
private:
	
	std::vector<Collision*> collideVec;
};

