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
	bool Sliding();							// ����
	bool Bounding();				// ���˕Ԃ�

	const float GetTrunkPoint() { return trunkpoint; }
	const bool IsTrunkHarfOver();
	const State GetState() const { return state; }

private:
	const float  VIBRATE_MAX = 150.0f;				// �U���U�ꕝ�ő�l
	const float  VIBRATE_MIN = -150.0f;				// �U���U�ꕝ�ő�l
	const float ASSAULT_DISTANCE = 300.0f;
	const float BOUND_POWER = 200.0f;				// ���˕Ԃ���
	const float BOUND_POWER_AIR = 500.0f;			// �󒆂ɂ���ꍇ�̒��˕Ԃ���
	const float GRAVITY = 400.0f;
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
	int trunkpoint;				// �̊��ʁi�{�X��hp�j
	bool isGround;				// �n�ʂƐڐG���Ă��邩
	bool isOnTarget;			// �Ώۂ̐^��Ɉړ�������
	bool isAttacking;			// �U������
	VECTOR startAssaultPos;
	VECTOR stompVec;
	
	void AssaultToPlayer();								// �v���C���[�Ɍ������ēːi����
	void ShotBullet(bool isNormal);						// �e�𔭎˂���
	void FaceToPlayer();								// �v���C���[�̕���������
	void Stomp();										// ���݂��U��
	void IncrementTrunkpoint();							// trunkpoint�̑���
	float GetDecreaseMagnification();					// trunkpoint�����{�����擾
	void MoveOnTarget(VECTOR target);					// �Ώۂ̐^��Ɉړ�����
	bool Vibrate();										// �U������
	

	State state;
	std::map<TimerType, class Timer*> timer;

	// �r�w�C�r�A�֌W
	class BehaviorManager* aiMgr;
	class NodeBase* node;

	void BehaviorUpdate();			// �r�w�C�r�A�X�V����
	void SetupBehavior();			// �r�w�C�r�A���ݒ�
};

