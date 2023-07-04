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
	bool AttackShotBullet();
	bool AttackShotBulletShotGun();

	const float GetTrunkPoint() { return trunkpoint; }
	const bool IsTrunkHarfOver();
	const State GetState() const { return state; }

private:
	const float  VIBRATE_MAX = 100.0f;				// 振動振れ幅最大値
	const float  VIBRATE_MIN = -100.0f;				// 振動振れ幅最大値
	const float ASSAULT_DISTANCE = 300.0f;
	const float BOUND_POWER = 1.0f;					// 跳ね返す力
	const float REBOUND_RESISTANCE = -1.0f;

	class Random& random;
	class ModelManager& modelMgr;
	class EnemyBulletManager& bulletMgr;
	class SupportJson& json;
	class KeyManager& key;
	class Player* player;
	class BossMagnification* magnification;

	int assaultCount;
	int shotCount;
	int trunkpoint;						// 体幹量（ボスのhp）
	VECTOR startAssaultPos;
	
	void AssaultToPlayer();
	void ShotBullet();
	void FaceToPlayer();
	float GetDecreaseMagnification();
	bool Vibrate();
	bool Sliding();

	State state;
	std::map<TimerType, class Timer*> timer;

	// ビヘイビア関係
	//class BehaviorTree* aiTree;			// ビヘイビアツリー
	//class BehaviorData* behaviorData;		// ビヘイビアデータ
	//class NodeBase* activeNode;			// 実行中ノード
	class BehaviorManager* aiMgr;
	//class ActBase* actNode;				// 実行中のノード
	class NodeBase* node;

	void BehaviorUpdate();			// ビヘイビア更新処理
	void SetupBehavior();			// ビヘイビア情報設定
};

