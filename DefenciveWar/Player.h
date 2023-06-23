#pragma once

#include "Mover.h"

class Player final : public Mover
{
public:
	Player(CollisionTag tag);
	~Player() override;

	void Initialize() override;
	void Update();
	void Draw();

	void HitObject(CollisionTag tag) override;

	const int GetHitpoint() const { return hp; }
	const int GetMaxHitpoint() const;
	const bool GetAlive() { return hp <= 0.0f; }
	
private:
	const float SPEED = 1;
	const float BULLET_SPEED = 4;
	const float SHOT_INTERVAL = 0.1f;

	class ModelManager& modelMgr;
	class EffectManager& effectMgr;
	class KeyManager& key;
	class Camera& camera;
	class BulletManager& bulletMgr;
	class SupportJson& json;

	class Timer* shotInterval;

	int hp;							// �q�b�g�|�C���g

	void Move();					// �ړ�����
	void Shot();					// �e�̔���
	void CreateShield();
};

