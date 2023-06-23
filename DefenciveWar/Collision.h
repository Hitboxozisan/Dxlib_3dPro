#pragma once

#include "DxLib.h"
#include "CollisionTag.h"

/// <summary>
/// 当たり判定処理クラス
/// 接触判定を受けたオブジェクトはここから各オブジェクトに指示を出す
/// </summary>
class Collision final
{
public:
	Collision(class ObjectBase* obj, const CollisionTag tag);
	~Collision();
	
	struct Data
	{
		VECTOR pos;
		float radius;
	};

	void Update();
	void DrawCollision();
	const bool Chack(class Collision* other);
	void HitObject(CollisionTag tag);

	const VECTOR GetPos() const { return data.pos; }
	const float GetRadius() const { return data.radius; }
	const bool IsExist() const { return exist; }
	const CollisionTag GetTag() const { return collideTag; }

	bool exist;
	Data data;
private:
	ObjectBase* parent;
	CollisionTag collideTag;
	

	const ObjectBase* GetParent() const { return parent; }
};

