#pragma once

#include "Mover.h"
#include "BossEnemyTimerType.h"
#include "BossState.h"

using namespace BossState;

class BossEnemy final : public Mover
{
public:
	BossEnemy(CollisionTag tag, class Player* p);
	~BossEnemy();

	void Initialize();
	void Update();
	void Draw();

	void HitObject(Collision* other) override;

	bool AttackAssault();
	bool AttackShotBullet(bool isNormal);
	bool AttackStomp();
	bool Sliding();							// 滑る

	const float GetTrunkPoint() { return trunkpoint; }
	const bool IsTrunkHarfOver();
	const State GetState() const { return state; }

private:
	const float  VIBRATE_MAX = 150.0f;				// 振動振れ幅最大値
	const float  VIBRATE_MIN = -150.0f;				// 振動振れ幅最大値
	const float ASSAULT_DISTANCE = 300.0f;
	const float BOUND_POWER = 200.0f;					// 跳ね返す力
	const float REBOUND_RESISTANCE = -200.0f;

	class Random& random;
	class ModelManager& modelMgr;
	class EnemyBulletManager& bulletMgr;
	class SupportJson& json;
	class KeyManager& key;
	class Player* player;
	class BossMagnification* magnification;

	int assaultCount;
	int shotCount;
	int stompCount;
	int trunkpoint;				// 体幹量（ボスのhp）
	bool isGround;				// 地面と接触しているか
	bool isOnTarget;			// 対象の真上に移動したか
	VECTOR startAssaultPos;
	VECTOR stompVec;
	
	void AssaultToPlayer();								// プレイヤーに向かって突進する
	void ShotBullet(bool isNormal);						// 弾を発射する
	void FaceToPlayer();								// プレイヤーの方向を向く
	void Stomp();										// 踏みつけ攻撃
	void IncrementTrunkpoint();							// trunkpointの増加
	float GetDecreaseMagnification();					// trunkpoint増加倍率を取得
	void MoveOnTarget(VECTOR target);					// 対象の真上に移動する
	bool Vibrate();										// 振動する
	

	State state;
	std::map<TimerType, class Timer*> timer;

	// ビヘイビア関係
	class BehaviorManager* aiMgr;
	class NodeBase* node;

	void BehaviorUpdate();			// ビヘイビア更新処理
	void SetupBehavior();			// ビヘイビア情報設定
};

