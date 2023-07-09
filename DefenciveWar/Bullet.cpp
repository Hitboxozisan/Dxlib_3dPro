#include "Bullet.h"
#include "ModelManager.h"
#include "Singleton.h"
#include "EffectManager.h"
#include "DeltaTime.h"

Bullet::Bullet(CollisionTag tag, CollisionTag bulletUser)
	:modelMgr(Singleton<ModelManager>::GetInstance())
	,effectMgr(Singleton<EffectManager>::GetInstance())
	,Mover(tag)
	,user(bulletUser)
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
	param.collision->exist = false;
	exist = false;
	isHit = false;

	// モデルの読み込み
	modelHandle = MV1DuplicateModel(modelMgr.GetModelHandle(mt));
}

void Bullet::Update()
{
	//if (!exist)
	//{
	//	return;
	//}

	// 移動処理
	Move();
	// ステージ外処理
	OutOfStage();
	// 位置の設定
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
	isHit = false;
}

void Bullet::HitObject(Collision* other)
{
	//if (!exist)
	//{
	//	return;
	//}

	// エネミーの場合
	if (other->GetTag() == CollisionTag::Enemy &&
		other->GetTag() != user)
	{
		// エフェクトの再生

		param.collision->exist = false;
		exist = false;
		isHit = true;
	}

	// プレイヤーの場合
	if (other->GetTag() == CollisionTag::Player &&
		other->GetTag() != user)
	{
		param.collision->exist = false;
		exist = false;
		isHit = true;
	}

	// シールドの場合
	if (other->GetTag() == CollisionTag::PlayerShield)
	{
		param.collision->exist = false;
		exist = false;
		isHit = true;
	}
}

/// <summary>
/// 移動処理
/// </summary>
void Bullet::Move()
{
	float delta = deltaTime.GetDeltaTime();
	param.nextPos = VAdd(param.nextPos, VScale(param.dir, speed * delta));
}

/// <summary>
/// ステージ外に出た際の処理
/// </summary>
void Bullet::OutOfStage()
{
	if (param.pos.x >= FIELD_POSITION_NORTH ||
		param.pos.x <= FIELD_POSITION_SOUTH ||
		param.pos.z >= FIELD_POSITION_EAST ||
		param.pos.z <= FIELD_POSITION_WEST)
	{
		// エフェクトの再生
		//effectMgr.SetPlayEffect(EffectType::LapseBullet, param.pos, false);
		param.collision->exist = false;
		exist = false;
	}
}

