#include "SupportJson.h"
#include "BossEnemy.h"
//#include "BehaviorData.h"
//#include "NodeBase.h"
#include "NodeManager.h"
#include "BossEnemyTimerData.h"
#include "Timer.h"
#include "Random.h"
#include "Singleton.h"
#include "DeltaTime.h"
//#include "BossJudgment.h"
//#include "ActionAssault.h"
#include "ModelManager.h"
#include "Player.h"
#include "EnemyBulletManager.h"
//#include "ActionShotBulletNormal.h"

#include "NodeAssault.h"

#include "KeyManager.h"

using namespace BossTimer;

BossEnemy::BossEnemy(CollisionTag tag, Player* p)
	:random(Singleton<Random>::GetInstance())
	,modelMgr(Singleton<ModelManager>::GetInstance())
	,bulletMgr(Singleton<EnemyBulletManager>::GetInstance())
	,json(Singleton<SupportJson>::GetInstance())
	,key(Singleton<KeyManager>::GetInstance())
	,aiTree(new NodeManager())
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
}

void BossEnemy::Update()
{

	//if (key.CheckPressed(KEY_INPUT_0) &&
	//	trunkpoint <= 100)
	//{
	//	if (trunkpoint >= 100)
	//	{
	//		trunkpoint = 100;
	//	}
	//	trunkpoint++;
	//}
	//if (key.CheckPressed(KEY_INPUT_1) &&
	//	trunkpoint >= 0)
	//{
	//	if (trunkpoint <= 0)
	//	{
	//		trunkpoint = 0;
	//	}
	//	trunkpoint--;
	//}

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
	// �v���C���[
	if (other->GetTag() == CollisionTag::Player)
	{

	}

	if (other->GetTag() == CollisionTag::Shield)
	{

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
	
	return true;
}

/// <summary>
/// �ΏۂɌ������Ēe�𔭎˂���
/// </summary>
/// <returns></returns>
bool BossEnemy::AttackShotBullet()
{
	int maxShot = json.GetInt(JsonDataType::BossEnemy, "ShotCount");
	float speed = json.GetFloat(JsonDataType::BossEnemy, "BulletSpeed");

	// �^�C�}�[�̍X�V
	timer[TimerType::ShotInterval]->Update(deltaTime.GetDeltaTime());
	
	// �v���C���[�̕���������
	FaceToPlayer();

	// �K��񐔂�e�𔭎˂���
	if (shotCount < maxShot &&
		timer[TimerType::ShotInterval]->IsTimeout())
	{
		// �O���ɐݒu
		VECTOR createPos = VAdd(param.pos, VScale(param.dir, 50.0f));

		// �^�C�}�[�����Z�b�g
		timer[TimerType::ShotInterval]->Reset();

		// �e�𐶐��E����
		bulletMgr.CreateBullet(createPos, param.dir, speed, ModelType::EnemyBullet);
	
		// �񐔂𑝉�������
		++shotCount;

		return false;
	}

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

	param.nextPos = VAdd(param.nextPos, VScale(param.dir, speed));
	
	// �w�苗���ːi�A�L�����N�^�[�ƐڐG������
	if (inDistance >= ASSAULT_DISTANCE)
	{
		// �I������
		++assaultCount;
		// �U�����̃^�C�}�[�����Z�b�g����
		timer[TimerType::VibrateAttack]->Reset();
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
/// �U��������
/// </summary>
/// <returns></returns>
bool BossEnemy::Vibrate()
{
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

		param.nextPos = VAdd(param.nextPos, randomForce);

		// �ːi�J�n�ʒu���L��
		startAssaultPos = param.pos;

		return false;
	}
	
	return true;
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
}

/// <summary>
/// �r�w�C�r�A�c���[�@�m�[�h�̐ݒ�
/// </summary>
void BossEnemy::SetupBehavior()
{
	//aiTree->AddNode("", "Root", 0, BehaviorTree::SelectRule::Priority, NULL, NULL);
	//aiTree->AddNode("Root", "Attack", 1, BehaviorTree::SelectRule::SequentialLooping, BossJudgment::GetInstance(), NULL);
	//aiTree->AddNode("Attack", "BulletNormal", 0, BehaviorTree::SelectRule::None, NULL, ActionShotBulletNormal::GetInstance());

	//aiTree->EntryNode();

}
