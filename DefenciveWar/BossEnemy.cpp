#include "SupportJson.h"
#include "BossEnemy.h"
#include "BossEnemyTimerData.h"
#include "Timer.h"
#include "Random.h"
#include "Singleton.h"
#include "DeltaTime.h"
#include "ModelManager.h"
#include "Player.h"
#include "EnemyBulletManager.h"
#include "BossMagnification.h"

#include "BehaviorManager.h"
#include "NodeBase.h"
#include "ActAssault.h"
#include "ActBulletNormal.h"
#include "ActBulletShotGun.h"
#include "ActStomp.h"

#include "KeyManager.h"

using namespace BossTimer;

BossEnemy::BossEnemy(CollisionTag tag, Player* p)
	:random(Singleton<Random>::GetInstance())
	,modelMgr(Singleton<ModelManager>::GetInstance())
	,bulletMgr(Singleton<EnemyBulletManager>::GetInstance())
	,json(Singleton<SupportJson>::GetInstance())
	,key(Singleton<KeyManager>::GetInstance())
	,aiMgr(new BehaviorManager())
	,magnification(new BossMagnification)
	,Mover(tag)
{
	player = p;

	int size = static_cast<int>(TimerType::TimerAmount);
	for (int i = 0; i < size; i++)
	{
		TimerType tk = static_cast<TimerType>(i);
		timer[tk] = new Timer(TIMER[tk]);
	}

	param.collision->data.radius = json.GetFloat(JsonDataType::BossEnemy, "Radius");

	modelHandle = MV1DuplicateModel(modelMgr.GetModelHandle(ModelType::Enemy));
	MV1SetScale(modelHandle, VGet(1.0f, 1.0f, 1.0f));
	// �}�e���A���̐F��ύX
	MV1SetMaterialEmiColor(modelHandle, 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));

	// �r�w�C�r�A�c���[�ݒ�
	SetupBehavior();
}

BossEnemy::~BossEnemy()
{
}

void BossEnemy::Initialize()
{
	param.pos = json.GetVector(JsonDataType::BossEnemy, "Position");
	param.prevPos = param.pos;
	param.nextPos = param.pos;

	//actNode = nullptr;
	isGround = true;
}

void BossEnemy::Update()
{
	if (trunkpoint >= 100)
	{
		// ���S��Ԃɂ���
		exist = false;
	}
	
	// �n�ʂ����蔲���Ȃ��悤�ɂ���
	if (param.nextPos.y <= 0)
	{
		param.nextPos.y = 0;
	}

	// �ʒu�C��
	ModifyingPosition();

	// �r�w�C�r�A�X�V����
	BehaviorUpdate();

	// ���ۂ̈ړ�����
	MoveFinish();
	// ���f���̌���������
	MV1SetRotationYUseDir(modelHandle, param.dir, 0.0f);

}

void BossEnemy::Draw()
{
	// ���f���̕`��
	MV1DrawModel(modelHandle);
}

/// <summary>
/// �ڐG����
/// </summary>
/// <param name="tag"></param>
void BossEnemy::HitObject(Collision* other)
{
	VECTOR sub;

	// �v���C���[
	if (other->GetTag() == CollisionTag::Player)
	{

	}

	// �V�[���h
	if (other->GetTag() == CollisionTag::PlayerShield && !isHit)
	{
		// �Q�[�W�̏㏸
		IncrementTrunkpoint();

		// ���˕Ԃ�͂�ݒ�
		sub = VSub(param.pos, other->GetPos());
		force = VNorm(sub);
		force = VScale(force, BOUND_POWER);
		// �󒆂ɂ��邩�ǂ����ŗ͂�ݒ�
		if (param.pos.y > 0)
		{
			force;
		}
		
		isHit = true;
	}

	// �e�̐ڐG����
	if (bulletMgr.IsHitPlayer())
	{
		// �Q�[�W�̏㏸
		IncrementTrunkpoint();
	}
}

/// <summary>
/// �ːi�s��
/// </summary>
/// <returns></returns>
bool BossEnemy::AttackAssault()
{
	int maxAssault = json.GetInt(JsonDataType::BossEnemy, "AssaultCount");

	// ���񐔍U������
	if (assaultCount < maxAssault)
	{
		if (Vibrate())
		{
			AssaultToPlayer();
		}
		else
		{
			FaceToPlayer();
		}

		return false;
	}
	
	// ����s�����邽�߂ɃJ�E���g�����Z�b�g����
	assaultCount = 0;
	return true;
}

/// <summary>
/// �ΏۂɌ������Ēe�𔭎˂���
/// </summary>
/// <returns></returns>
bool BossEnemy::AttackShotBullet(bool isNormal)
{
	int maxShot = json.GetInt(JsonDataType::BossEnemy, "ShotCount");

	// �^�C�}�[�̍X�V
	timer[TimerType::ShotInterval]->Update(deltaTime.GetDeltaTime());
	
	// �v���C���[�̕���������
	FaceToPlayer();

	// �K��񐔂�e�𔭎˂���
	if (shotCount <= maxShot)
	{
		ShotBullet(isNormal);
		return false;
	}

	// ����s�����邽�߃J�E���g�����Z�b�g����
	shotCount = 0;
	return true;
}

/// <summary>
/// ���݂��U��
/// </summary>
/// <returns></returns>
bool BossEnemy::AttackStomp()
{
	int maxStomp = json.GetInt(JsonDataType::BossEnemy, "StompCount");

	// �w��񐔓��݂��U�����s��
	if (stompCount <= maxStomp)
	{
		MoveOnTarget(player->GetPos());

		// �v���C���[���Ɉړ�����
		if (isOnTarget)
		{
			if (Vibrate())
			{
				// �ړ������瓥�݂��U�����s��
				Stomp();
			}
			else
			{
				stompVec = VGet(0, 300, 0);
			}
		}

		// �n�ʂƐڐG������
		if (param.nextPos.y <= 0)
		{
			param.nextPos.y = 0;
			isGround = true;
		}

		// �n�ʂƐڐG���Ă���ꍇ
		if (isGround)
		{
			// ��莞�Ԑ��~����
			timer[TimerType::Landing]->Update(deltaTime.GetDeltaTime());

			// �N�[���^�C�����߂�����
			if (timer[TimerType::Landing]->IsTimeout())
			{
				// �e�^�C�}�[�����Z�b�g
				timer[TimerType::VibrateAttack]->Reset();
				timer[TimerType::Landing]->Reset();
				isOnTarget = false;
				isGround = false;
				++stompCount;
				// ���񐔍U������܂ŌJ��Ԃ�
			}

		}

		return false;
	}

	stompCount = 0;
	return true;
}

/// <summary>
/// �̊��ʂ������𒴂�����
/// </summary>
/// <returns></returns>
const bool BossEnemy::IsTrunkHarfOver()
{
	int maxTrunk = json.GetInt(JsonDataType::BossEnemy, "MaxTrunk");

	if (trunkpoint >= maxTrunk / 2)
	{
		return true;
	}

	return false;
}

/// <summary>
/// �ːi�U��
/// </summary>
void BossEnemy::AssaultToPlayer()
{
	VECTOR sub = VSub(param.pos, startAssaultPos);
	float inDistance = VSize(sub);
	float speed = json.GetFloat(JsonDataType::BossEnemy, "AssaultSpeed");
	float delta = deltaTime.GetDeltaTime();

	param.nextPos = VAdd(param.nextPos, VScale(param.dir, speed * delta));
	
	// �w�苗���ːi�A�L�����N�^�[�ƐڐG������
	if (inDistance >= ASSAULT_DISTANCE)
	{
		// �I������
		++assaultCount;
		// �U�����̃^�C�}�[�����Z�b�g����
		timer[TimerType::VibrateAttack]->Reset();
	}
}


void BossEnemy::ShotBullet(bool isNormal)
{

	if (timer[TimerType::ShotInterval]->IsTimeout())
	{
		VECTOR createPos = ZERO_VECTOR;

		float speed = json.GetFloat(JsonDataType::BossEnemy, "BulletSpeed");

		// �ʏ픭�˂̏ꍇ
		if (isNormal)
		{
			// �O���ɐݒu
			createPos = VAdd(param.pos, VScale(param.dir, 50.0f));
			// �^�C�}�[�����Z�b�g
			timer[TimerType::ShotInterval]->Reset();
			// �e�𐶐��E����
			bulletMgr.CreateBullet(createPos, param.dir, speed, ModelType::EnemyBullet);
			// �񐔂𑝉�������
			++shotCount;
		}
		// �V���b�g�K���̏ꍇ
		else
		{
			timer[TimerType::ShotInterval]->Reset();
			bulletMgr.CreateBulletShotGun(param.pos, param.dir, speed, ModelType::EnemyBullet);
			++shotCount;
		}
	}

}

/// <summary>
/// �v���C���[�̕���������
/// </summary>
void BossEnemy::FaceToPlayer()
{
	VECTOR sub = VSub(player->GetPos(), param.pos);
	VECTOR dir = VNorm(sub);

	param.dir = dir;
}

/// <summary>
/// ���݂���
/// </summary>
void BossEnemy::Stomp()
{
	float fallVec = json.GetFloat(JsonDataType::BossEnemy, "StompSpeed");
	stompVec.y -= fallVec;

	param.nextPos = VAdd(param.nextPos, VScale(stompVec, deltaTime.GetDeltaTime()));

}

/// <summary>
/// 
/// </summary>
void BossEnemy::IncrementTrunkpoint()
{
	

	// �Q�[�W�̏㏸
	if (player->GetShield()->IsJustDefense())
	{
		// �W���X�g�K�[�h�̏ꍇ�͑����ʂ�2�{�ɂ���
		trunkpoint += GetDecreaseMagnification() * 2;
	}
	else
	{
		trunkpoint += GetDecreaseMagnification();
	}

}

/// <summary>
/// �����ʂ�Ԃ�
/// </summary>
/// <returns></returns>
float BossEnemy::GetDecreaseMagnification()
{
	std::string state = node->GetName();
	return magnification->GetMagnification(state);
}

/// <summary>
/// �Ώۂ̐^��Ɉړ�����
/// </summary>
/// <param name="target"></param>
/// <returns></returns>
void BossEnemy::MoveOnTarget(VECTOR target)
{
	// �Ώۂ̐^��Ɉړ������ꍇ�͓��݂��U���ɓ��邽�ߏ������Ȃ�
	if (isOnTarget)
	{
		return;
	}

	float delta = deltaTime.GetDeltaTime();
	// �e�l��json�t�@�C������擾
	float highPos = json.GetFloat(JsonDataType::BossEnemy, "StompHighPos");
	float speed = json.GetFloat(JsonDataType::BossEnemy, "MoveOnTargetSpeed");
	// �w��n�_�ݒ�
	VECTOR finishPos = target;
	finishPos.y = finishPos.y + highPos;

	// �ΏۂƂ̋���
	float distance = VSize(VSub(finishPos, param.pos));
	// �������ԍX�V
	timer[TimerType::Tracking]->Update(delta);

	isGround = false;

	// �Ώۂ̏��Ɉړ�����
	VECTOR moveVec = VSub(finishPos, param.pos);
	// �w�荂�x�܂ŏ㏸����
	if (param.nextPos.y >= highPos)
	{
		moveVec.y = 0;
	}
	else
	{
		moveVec.y = highPos;
	}
	// ���K��
	moveVec = VNorm(moveVec);
	// �w��̑傫���ɕύX
	moveVec = VScale(moveVec, speed);
	
	// �ړ�
	param.nextPos = VAdd(param.nextPos, VScale(moveVec, delta));

	// �Ώۂ̐^��Ɉړ�����������͈�莞�Ԍo�߂���Ɨ������J�n����
	if (distance <= 10 ||
		timer[TimerType::Tracking]->IsTimeout())
	{
		timer[TimerType::Tracking]->Reset();
		isOnTarget = true;
	}

}

/// <summary>
/// �U��������
/// </summary>
/// <returns></returns>
bool BossEnemy::Vibrate()
{
	float delta = deltaTime.GetDeltaTime();
	float randomX = random.GetRandomFloat(VIBRATE_MIN, VIBRATE_MAX);
	float randomZ = random.GetRandomFloat(VIBRATE_MIN, VIBRATE_MAX);

	// �����_���ȕ����Ɉړ���������
	VECTOR randomForce = VGet(randomX, 0.0f, randomZ);

	timer[TimerType::VibrateAttack]->Update(deltaTime.GetDeltaTime());

	// �w��b���U��������
	if (!timer[TimerType::VibrateAttack]->IsTimeout())
	{
		param.nextPos = param.prevPos;
		param.pos = param.prevPos;

		param.nextPos = VAdd(param.nextPos, VScale(randomForce, delta));

		// �ːi�J�n�ʒu���L��
		startAssaultPos = param.pos;

		return false;
	}
	
	return true;
}

/// <summary>
/// �ڐG��̔����ŃX���C�h
/// </summary>
/// <returns></returns>
bool BossEnemy::Sliding()
{
	float delta = deltaTime.GetDeltaTime();
	// �i�s�����Ƃ͋t�����̗͂�ݒ�
	VECTOR friction = force;
	friction = VNorm(friction);
	friction = VScale(friction, REBOUND_RESISTANCE);

	force = VAdd(force, VScale(friction, delta));
	param.nextPos = VAdd(param.nextPos, VScale(force, delta));

	// �����͂� 0 �����������I������
	if (VSize(force) <= 0)
	{
		force = ZERO_VECTOR;
		isHit = false;
		return true;
	}

	return false;
}

/// <summary>
/// �r�w�C�r�A�X�V����
/// </summary>
void BossEnemy::BehaviorUpdate()
{
	//if (activeNode == NULL)
	//{
	//	activeNode = aiTree->Inference(this, behaviorData);
	//}
	//
	//if (activeNode != NULL)
	//{
	//	activeNode = aiTree->Run(this, activeNode, behaviorData);
	//}

	// �s�������肵�Ă��Ȃ��ꍇ�͍s�������肷��
	if (node == NULL)
	{
		node = aiMgr->InferenceNode();
	}
	else
	{
		node = aiMgr->Update(node);
	}
}

/// <summary>
/// �r�w�C�r�A�c���[�@�m�[�h�̐ݒ�
/// </summary>
void BossEnemy::SetupBehavior()
{
	//aiTree->AddNode("", "Root", 0, BehaviorTree::SelectRule::Priority, NULL, NULL);
	//aiTree->AddNode("Root", "Attack", 1, BehaviorTree::SelectRule::SequentialLooping, BossJudgment::GetInstance(), NULL);
	//aiTree->AddNode("Attack", "BulletNormal", 0, BehaviorTree::SelectRule::None, NULL, ActionShotBulletNormal::GetInstance());

	aiMgr->EntryNode("Root", "", 1, 1, BehaviorTree::SelectRule::Priority, NULL);
	aiMgr->EntryNode("Attack", "Root", 2, 1, BehaviorTree::SelectRule::Sequence, NULL);
	//aiMgr->EntryNode("Assault", "Attack", 3, 1, BehaviorTree::SelectRule::None, new ActAssault(this));
	//aiMgr->EntryNode("Bullet", "Attack", 3, 2, BehaviorTree::SelectRule::Random, NULL);
	aiMgr->EntryNode("Stomp", "Attack", 3, 3, BehaviorTree::SelectRule::None, new ActStomp(this));
	//aiMgr->EntryNode("BulletNormal", "Bullet", 4, 1, BehaviorTree::SelectRule::None, new ActBulletNormal(this));
	//aiMgr->EntryNode("BulletShotGun", "Bullet", 4, 1, BehaviorTree::SelectRule::None, new ActBulletShotGun(this));
}
