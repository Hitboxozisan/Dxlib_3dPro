#pragma once

#include "Mover.h"
#include "ModelTypeData.h"

/// <summary>
/// �e�{��
/// </summary>
class Bullet : public Mover
{
public:
	Bullet(CollisionTag tag, CollisionTag bulletUser);
	~Bullet();

	void Initialize(ModelType mt);
	void Update();
	void Draw();

	void Create(VECTOR pos, VECTOR dir, float shotSpeed);
	void HitObject(Collision* other) override;
	const bool IsHit() const { return isHit; }

private:
	const float COLLIDE_RADIUS = 1.0f;			// �����蔻�苅���a

	class ModelManager& modelMgr;
	class EffectManager& effectMgr;

	float speed;
	bool isHit;
	CollisionTag user;			// �e�̏��L��

	void Move();
	void OutOfStage();			// �X�e�[�W�O����

};

