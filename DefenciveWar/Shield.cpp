#include "common.h"
#include "Shield.h"
#include "Singleton.h"
#include "EffectManager.h"
#include "Timer.h"
#include "DeltaTime.h"

Shield::Shield(CollisionTag tag)
	:ObjectBase(tag)
	, effectMgr(Singleton<EffectManager>::GetInstance())
	, deltaTime(Singleton<DeltaTime>::GetInstance())
	, existTimer(new Timer(JUST_DEFENSE_TIME))
	, stanTimer(new Timer(STAN_TIME))
	,coolTimer(new Timer(COOL_TIME))
{
	param.collision->data.radius = COLLIDE_RADIUS;
}

Shield::~Shield()
{
	delete existTimer;
	delete stanTimer;
}

void Shield::Initialize()
{
	trunkpoint = 0.0f;
	isBreak = false;
}

void Shield::Activate(VECTOR createPos)
{
	exist = true;
	param.collision->exist = true;
	existTimer->Reset();
	effectMgr.SetPlayEffect(EffectType::Shield, createPos, true);
}

void Shield::Deactivate()
{
	exist = false;
	param.collision->exist = false;
	effectMgr.StopPlayEffect(EffectType::Shield);
}

void Shield::Update(VECTOR shieldPos)
{
	// 自動回復
	//coolTimer->Update(deltaTime.GetDeltaTime());
	//if (coolTimer->IsTimeout() &&
	//	trunkpoint >= 0)
	//{
	//	trunkpoint -= DECREMENT_TRUNKPOINT * deltaTime.GetDeltaTime();
	//}

	// 存在しない場合は下の処理はしない
	if (!exist)
	{
		return;
	}

	coolTimer->Reset();

	existTimer->Update(deltaTime.GetDeltaTime());

	if (trunkpoint >= 100)
	{
		trunkpoint = 0;
		isBreak = true;
	}

	if (isBreak)
	{
		stanTimer->Update(deltaTime.GetDeltaTime());
		if (stanTimer->IsTimeout())
		{
			stanTimer->Reset();
			isBreak = false;
		}
	}

	param.pos = shieldPos;
}

void Shield::Draw()
{
	if (!exist)
	{
		return;
	}

	// シールド本体はエフェクトのため
	// 描画はEffectMgrが行う
}

void Shield::HitObject(Collision* other)
{
	coolTimer->Reset();

	if (other->GetTag() == CollisionTag::Enemy && !isHit)
	{
		if (existTimer->IsTimeout())
		{
			trunkpoint += INCREMENT_TRUNKPOINT;
		}
		else
		{
			trunkpoint += INCREMENT_TRUNKPOINT / 2;
		}

		isHit = true;
	}
}

bool Shield::IsJustDefense()
{
	return existTimer->IsTimeout();
}
