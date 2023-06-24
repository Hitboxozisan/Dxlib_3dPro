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
	// �R���W������ێ�����I�u�W�F�N�g���Ȃ��ꍇ��
	// ���W��ʂ̂Ƃ���Ɉړ�������
	//if (!parent->IsExist())
	//{
	//	data.pos = COLLIDE_SAFE_POS;
	//}

	// �����蔻����W�X�V
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

	// ���̃I�u�W�F�N�g�Ƃ̋�����
	// ���݂��̔��a�̍��v���߂���ΐڐG���Ă���
	if (distance < radTotal)
	{
		return true;
	}

	return false;
}

/// <summary>
/// �ڐG����
/// </summary>
/// <param name="tag"></param>
void Collision::HitObject(CollisionTag tag)
{
	// �e�I�u�W�F�N�g�̐ڐG����
	parent->HitObject(tag);
}
