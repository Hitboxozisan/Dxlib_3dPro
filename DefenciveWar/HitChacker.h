#pragma once

#include <unordered_map>
#include "Collision.h"

/// <summary>
/// �����蔻�菈���E�Ή��������s���N���X
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

