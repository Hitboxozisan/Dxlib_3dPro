#pragma once

#include "ObjectBase.h"

/// <summary>
/// シールドクラス
/// プレイヤーが保持する
/// </summary>
class Shield final : public ObjectBase
{
public:
	Shield(CollisionTag tag);
	~Shield();

	void Initialize();
	void Activate(VECTOR createPos);
	void Deactivate();
	void Update(VECTOR shieldPos);
	void Draw();

private:
	const float COLLIDE_RADIUS = 25;

	class EffectManager& effectMgr;
};

