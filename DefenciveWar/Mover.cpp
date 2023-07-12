#include "Mover.h"
#include "Singleton.h"
#include "DeltaTime.h"

Mover::Mover(CollisionTag tag)
	:force(ZERO_VECTOR)
	,deltaTime(Singleton<DeltaTime>::GetInstance())
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
	float x = param.nextPos.x;
	float z = param.nextPos.z;

	if (x <= FIELD_POSITION_WEST)
	{
		param.nextPos = VGet(FIELD_POSITION_WEST, GetPos().y, GetPos().z);
	}
	if (x >= FIELD_POSITION_EAST)
	{
		param.nextPos = VGet(FIELD_POSITION_EAST, GetPos().y, GetPos().z);
	}
	if (z <= FIELD_POSITION_SOUTH)
	{
		param.nextPos = VGet(GetPos().x, GetPos().y, FIELD_POSITION_SOUTH);
	}
	if (z >= FIELD_POSITION_NORTH)
	{
		param.nextPos = VGet(GetPos().x, GetPos().y, FIELD_POSITION_NORTH);
	}
}

void Mover::MoveFinish()
{
	// ’n–Ê‚ð‚·‚è”²‚¯‚È‚¢‚æ‚¤‚É‚·‚é
	//if (param.nextPos.y <= 0)
	//{
	//	param.nextPos.y = 0;
	//}

	param.prevPos = param.pos;
	param.pos = param.nextPos;

	// ƒ‚ƒfƒ‹‚ÌˆÊ’u‚ð³Ž®‚ÉÝ’è
	MV1SetPosition(modelHandle, param.pos);
}