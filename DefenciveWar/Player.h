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
	const float INVINCIBLE_TIME = 1.0f;

	class ModelManager& modelMgr;
	class EffectManager& effectMgr;
	class KeyManager& key;
	class Camera& camera;
	class BulletManager& bulletMgr;
	class SupportJson& json;

	class Timer* shotInterval;
	class Timer* invincibleTime;
	class Shield* shield;

	int hp;							// ヒットポイント
	bool isHit;

	void Move();					// 移動処理
	void Shot();					// 弾の発射
	void CreateShield();
};

