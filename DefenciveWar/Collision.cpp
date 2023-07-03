#include "common.h"
#include "Collision.h"
#include "ObjectBase.h"

Collision::Collision(class ObjectBase* obj, const CollisionTag tag)
	:parent(obj)
	,collideTag(tag)
	,exist(true)
{
}

Collision::~Collision()
{
}

void Collision::Update()
{
	// コリジョンを保持するオブジェクトがない場合は
	// 座標を別のところに移動させる
	if (!IsExist())
	{
		data.pos = COLLIDE_SAFE_POS;
		return;
	}

	// 当たり判定座標更新
	data.pos = parent->GetPos();
}

void Collision::DrawCollision()
{
	DrawSphere3D(data.pos, data.radius, 10, GREEN, GREEN, FALSE);
}

const bool Collision::Chack(Collision* other)
{
	float distance = VSize(VSub(data.pos, other->GetPos()));
	float radTotal = data.radius + other->GetRadius();

	// 他のオブジェクトとの距離が
	// お互いの半径の合計より近ければ接触している
	if (distance < radTotal)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 接触処理
/// </summary>
/// <param name="tag"></param>
void Collision::HitObject(Collision* other)
{
	// 各オブジェクトの接触処理
	parent->HitObject(other);
}
