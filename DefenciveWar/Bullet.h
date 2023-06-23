#pragma once

#include "Mover.h"
#include "ModelTypeData.h"

/// <summary>
/// 弾本体
/// </summary>
class Bullet : public Mover
{
public:
	Bullet(CollisionTag tag);
	~Bullet();

	void Initialize(ModelType mt);
	void Update();
	void Draw();

	void Create(VECTOR pos, VECTOR dir, float shotSpeed);
	void HitObject(CollisionTag tag) override;

private:
	const float COLLIDE_RADIUS = 1.0f;			// 当たり判定球半径

	class ModelManager& modelMgr;
	class EffectManager& effectMgr;

	float speed;

	void Move();
	void OutOfStage();			// ステージ外処理

};

