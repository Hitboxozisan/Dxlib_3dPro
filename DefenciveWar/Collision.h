#pragma once

#include "DxLib.h"
#include "CollisionTag.h"

/// <summary>
/// �����蔻�菈���N���X
/// �ڐG������󂯂��I�u�W�F�N�g�͂�������e�I�u�W�F�N�g�Ɏw�����o��
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
	void HitObject(Collision* other);

	const VECTOR GetPos() const { return data.pos; }
	const float GetRadius() const { return data.radius; }
	const bool IsExist() const { return exist; }
	const CollisionTag GetTag() const { return collideTag; }
	Collision* GetCollision() { return this; }

	bool exist;
	Data data;
private:
	const VECTOR COLLIDE_SAFE_POS = VGet(500, 0, 500);

	ObjectBase* parent;
	CollisionTag collideTag;
	
	const ObjectBase* GetParent() const { return parent; }
};

