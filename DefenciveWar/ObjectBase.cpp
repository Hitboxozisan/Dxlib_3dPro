#include "ObjectBase.h"
#include "Singleton.h"
#include "HitChacker.h"

ObjectBase::ObjectBase(CollisionTag tag)
	: collideMgr(Singleton<HitChacker>::GetInstance())
	, modelHandle(0)
	, exist(false)
	,isHit(false)
{
	param.pos = ZERO_VECTOR;
	param.nextPos = param.pos;
	param.prevPos = param.pos;
	param.dir = ZERO_VECTOR;
	param.collision = new Collision(this, tag);
	collideMgr.EntryCollide(param.collision);
}

ObjectBase::~ObjectBase()
{

}

void ObjectBase::Initialize()
{
}

void ObjectBase::HitObject(Collision* other)
{
	
}
