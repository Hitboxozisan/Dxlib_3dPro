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

	void HitObject(Collision* other) override;

	Shield* GetShield() const { return shield; }
	const float GetHitpoint() const { return hp; }
	const int GetMaxHitpoint() const;
	const bool GetAlive() { return hp <= 0.0f; }
	
private:
	const int DECREMENT_HP = 20;
	const float SHOT_INTERVAL = 0.1f;
	const float INVINCIBLE_TIME = 2.0f;
	const float HIT_ENEMY_FORCE = 10.0f;
	const float BOUND_POWER = 200.0f;
	const float REBOUND_RESISTANCE = -200.0f;


	class ModelManager& modelMgr;
	class EffectManager& effectMgr;
	class KeyManager& key;
	class Camera& camera;
	class BulletManager& bulletMgr;
	class SupportJson& json;

	class Timer* shotInterval;
	class Timer* invincibleTime;
	class Shield* shield;

	float hp;							// ƒqƒbƒgƒ|ƒCƒ“ƒg
	bool isInvincible;					// –³“Gó‘Ô‚©
	
	void Move();					// ˆÚ“®ˆ—
	void Shot();					// ’e‚Ì”­ŽË
	void CreateShield();
	bool Sliding();
};

