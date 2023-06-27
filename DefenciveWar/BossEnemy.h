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

	const float GetTrunkPoint() { return trunkpoint; }
	const bool IsTrunkHarfOver();
	const State GetState() const { return state; }

private:
	const float  VIBRATE_MAX = 5.0f;						// �U���U�ꕝ�ő�l
	const float  VIBRATE_MIN = -5.0f;						// �U���U�ꕝ�ő�l
	const float ASSAULT_SPEED = 3.0f;
	const float SHOT_SPEED = 3.0f;
	const float ASSAULT_DISTANCE = 300.0f;

	class Random& random;
	class ModelManager& modelMgr;
	class EnemyBulletManager& bulletMgr;
	class SupportJson& json;
	class KeyManager& key;
	class Player* player;

	int assaultCount;
	int shotCount;
	int trunkpoint;						// �̊��ʁi�{�X��hp�j
	VECTOR startAssaultPos;
	
	void AssaultToPlayer();
	void FaceToPlayer();
	bool Vibrate();

	State state;
	std::map<TimerType, class Timer*> timer;

	// �r�w�C�r�A�֌W
	class BehaviorTree* aiTree;			// �r�w�C�r�A�c���[
	class BehaviorData* behaviorData;	// �r�w�C�r�A�f�[�^
	class NodeBase* activeNode;			// ���s���m�[�h

	void BehaviorUpdate();			// �r�w�C�r�A�X�V����
	void SetupBehavior();			// �r�w�C�r�A���ݒ�
};

