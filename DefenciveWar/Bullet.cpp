#include "Bullet.h"
#include "ModelManager.h"
#include "Singleton.h"
#include "EffectManager.h"

Bullet::Bullet(CollisionTag tag)
	:modelMgr(Singleton<ModelManager>::GetInstance())
	,effectMgr(Singleton<EffectManager>::GetInstance())
	,Mover(tag)
{
	param.collision->data.radius = 10;
}

Bullet::~Bullet()
{
}

void Bullet::Initialize(ModelType mt)
{
	param.pos = ZERO_VECTOR;
	param.dir = ZERO_VECTOR;
	//param.tag = CollisionTag::Bullet;

	// ���f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(modelMgr.GetModelHandle(mt));
}

void Bullet::Update()
{
	//if (!exist)
	//{
	//	return;
	//}

	// �ړ�����
	Move();
	// �X�e�[�W�O����
	OutOfStage();
	// �ʒu�̐ݒ�
	MoveFinish();
	
	MV1SetRotationYUseDir(modelHandle, param.dir, 0.0f);
}

void Bullet::Draw()
{
	//if (!exist)
	//{
	//	return;
	//}

	MV1DrawModel(modelHandle);
}

void Bullet::Create(VECTOR pos, VECTOR dir, float shotSpeed)
{
	param.nextPos = pos;
	param.pos = pos;
	param.dir = dir;
	speed = shotSpeed;
	param.collision->exist = true;
	exist = true;
}

void Bullet::HitObject(CollisionTag tag)
{
	//if (!exist)
	//{
	//	return;
	//}

	if (tag == CollisionTag::Enemy)
	{
		param.collision->exist = false;
		exist = false;
		printfDx("a");
	}
}

/// <summary>
/// �ړ�����
/// </summary>
void Bullet::Move()
{
	param.nextPos = VAdd(param.nextPos, VScale(param.dir, speed));
}

/// <summary>
/// �X�e�[�W�O�ɏo���ۂ̏���
/// </summary>
void Bullet::OutOfStage()
{
	if (param.pos.x >= FIELD_POSITION_NORTH ||
		param.pos.x <= FIELD_POSITION_SOUTH ||
		param.pos.z >= FIELD_POSITION_EAST ||
		param.pos.z <= FIELD_POSITION_WEST)
	{
		// �G�t�F�N�g�̍Đ�
		//effectMgr.SetPlayEffect(EffectType::LapseBullet, param.pos, false);
		param.collision->exist = false;
		exist = false;
	}
}
