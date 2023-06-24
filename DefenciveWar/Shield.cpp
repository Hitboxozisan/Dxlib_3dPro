#include "common.h"
#include "Shield.h"
#include "Singleton.h"
#include "EffectManager.h"

Shield::Shield(CollisionTag tag)
	:ObjectBase(tag)
	, effectMgr(Singleton<EffectManager>::GetInstance())
{
	param.collision->data.radius = COLLIDE_RADIUS;
}

Shield::~Shield()
{
}

void Shield::Initialize()
{
	
}

void Shield::Activate(VECTOR createPos)
{
	exist = true;
	effectMgr.SetPlayEffect(EffectType::Shield, createPos, true);
}

void Shield::Deactivate()
{
	exist = false;
	effectMgr.StopPlayEffect(EffectType::Shield);
}

void Shield::Update(VECTOR shieldPos)
{
	if (!exist)
	{
		return;
	}

	param.pos = shieldPos;
}

void Shield::Draw()
{
	if (!exist)
	{
		return;
	}
}
