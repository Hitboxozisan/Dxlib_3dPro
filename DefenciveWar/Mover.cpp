#include "Mover.h"
#include "Singleton.h"
#include "DeltaTime.h"

Mover::Mover(CollisionTag tag)
	:deltaTime(Singleton<DeltaTime>::GetInstance())
	,ObjectBase(tag)
{
}

Mover::~Mover()
{
}

void Mover::Initialize()
{
}

void Mover::ModifyingPosition()
{
	float x = param.pos.x;
	float z = param.pos.z;

	if (x <= FIELD_POSITION_WEST)
	{
		param.pos = VGet(FIELD_POSITION_WEST, GetPos().y, GetPos().z);
	}
	if (x >= FIELD_POSITION_EAST)
	{
		param.pos = VGet(FIELD_POSITION_EAST, GetPos().y, GetPos().z);
	}
	if (z <= FIELD_POSITION_SOUTH)
	{
		param.pos = VGet(GetPos().x, GetPos().y, FIELD_POSITION_SOUTH);
	}
	if (z >= FIELD_POSITION_NORTH)
	{
		param.pos = VGet(GetPos().x, GetPos().y, FIELD_POSITION_NORTH);
	}
}

void Mover::MoveFinish()
{
	// �n�ʂ����蔲���Ȃ��悤�ɂ���
	if (param.nextPos.y <= 0)
	{
		param.nextPos.y = 0;
	}

	param.prevPos = param.pos;
	param.pos = param.nextPos;

	// ���f���̈ʒu�𐳎��ɐݒ�
	MV1SetPosition(modelHandle, param.pos);
}