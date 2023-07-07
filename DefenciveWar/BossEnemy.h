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

	const float GetTrunkPoint() { return trunkpoint; }
	const bool IsTrunkHarfOver();
	const State GetState() const { return state; }

private:
	const float  VIBRATE_MAX = 150.0f;				// �U���U�ꕝ�ő�l
	const float  VIBRATE_MIN = -150.0f;				// �U���U�ꕝ�ő�l
	const float ASSAULT_DISTANCE = 300.0f;
	const float BOUND_POWER = 1.0f;					// ���˕Ԃ���
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
	int stompCount;
	int trunkpoint;				// �̊��ʁi�{�X��hp�j
	bool isGround;				// �n�ʂƐڐG���Ă��邩
	bool isOnTarget;			// �Ώۂ̐^��Ɉړ�������
	VECTOR startAssaultPos;
	VECTOR stompVec;
	
	void AssaultToPlayer();
	void ShotBullet(bool isNormal);
	void FaceToPlayer();
	void Stomp();
	float GetDecreaseMagnification();
	void MoveOnTarget(VECTOR target);
	bool Vibrate();
	bool Sliding();

	State state;
	std::map<TimerType, class Timer*> timer;

	// �r�w�C�r�A�֌W
	class BehaviorManager* aiMgr;
	class NodeBase* node;

	void BehaviorUpdate();			// �r�w�C�r�A�X�V����
	void SetupBehavior();			// �r�w�C�r�A���ݒ�
};

