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

	void Initialize() override;
	void Activate(VECTOR createPos);
	void Deactivate();
	void Update(VECTOR shieldPos);
	void Draw();

	void HitObject(CollisionTag tag) override;

	void SetTrunk(float a) {
		if (a == 1)trunkpoint++;
		if (a == -1)trunkpoint--;
	}
	const float GetTrunkpoint() const { return trunkpoint; }
	const bool IsBreak() const { return isBreak; }
private:
	const float COLLIDE_RADIUS = 25;
	const float INCREMENT_TRUNKPOINT = 20.0f;
	const float DECREMENT_TRUNKPOINT = 50.0f;
	const float JUST_DEFENSE_TIME = 1.0f;
	const float STAN_TIME = 10.0f;
	const float COOL_TIME = 2.0f;

	class EffectManager& effectMgr;
	class DeltaTime& deltaTime;
	class Timer* existTimer;			// 存在時間
	class Timer* stanTimer;				// 破壊時間
	class Timer* coolTimer;				// 自動回復時間

	float trunkpoint;
	bool isBreak;
};

