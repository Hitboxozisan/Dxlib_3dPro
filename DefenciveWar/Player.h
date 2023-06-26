#pragma once

#include "Mover.h"
#include "Shield.h"

class Player final : public Mover
{
public:
	Player(CollisionTag tag);
	~Player() override;

	void Initialize() override;
	void Update();
	void Draw();

	void HitObject(CollisionTag tag) override;

	const Shield* GetShield() const { return shield; }
	const float GetHitpoint() const { return hp; }
	const int GetMaxHitpoint() const;
	const bool GetAlive() { return hp <= 0.0f; }
	
private:
	const int DECREMENT_HP = 20;
	const float SPEED = 1;
	const float BULLET_SPEED = 4;
	const float SHOT_INTERVAL = 0.1f;
	const float INVINCIBLE_TIME = 1.0f;
	const float HIT_ENEMY_FORCE = 10.0f;

	class ModelManager& modelMgr;
	class EffectManager& effectMgr;
	class KeyManager& key;
	class Camera& camera;
	class BulletManager& bulletMgr;
	class SupportJson& json;

	class Timer* shotInterval;
	class Timer* invincibleTime;
	class Shield* shield;

	float hp;							// �q�b�g�|�C���g
	
	void Move();					// �ړ�����
	void Shot();					// �e�̔���
	void CreateShield();
};

