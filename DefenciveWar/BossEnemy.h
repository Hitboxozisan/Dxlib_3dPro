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

	void HitObject(CollisionTag tag) override;

	bool AttackAssault();
	bool AttackShotBullet();

	const bool IsTrunkHarfOver();
	const State GetState() const { return state; }

private:
	const float  VIBRATE_MAX = 5.0f;						// 振動振れ幅最大値
	const float  VIBRATE_MIN = -5.0f;						// 振動振れ幅最大値
	const float ASSAULT_SPEED = 3.0f;
	const float SHOT_SPEED = 3.0f;
	const float ASSAULT_DISTANCE = 300.0f;

	class Random& random;
	class ModelManager& modelMgr;
	class EnemyBulletManager& bulletMgr;
	class SupportJson& json;
	class Player* player;

	int assaultCount;
	int shotCount;
	int tp;						// 体幹量（ボスのhp）
	VECTOR startAssaultPos;
	
	void AssaultToPlayer();
	void FaceToPlayer();
	bool Vibrate();

	State state;
	std::map<TimerType, class Timer*> timer;

	// ビヘイビア関係
	class BehaviorTree* aiTree;			// ビヘイビアツリー
	class BehaviorData* behaviorData;	// ビヘイビアデータ
	class NodeBase* activeNode;			// 実行中ノード

	void BehaviorUpdate();			// ビヘイビア更新処理
	void SetupBehavior();			// ビヘイビア情報設定
};

