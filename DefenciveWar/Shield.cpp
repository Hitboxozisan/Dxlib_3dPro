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
	existTimer->Reset();
	effectMgr.SetPlayEffect(EffectType::Shield, createPos, true);
}

void Shield::Deactivate()
{
	exist = false;
	effectMgr.StopPlayEffect(EffectType::Shield);
}

void Shield::Update(VECTOR shieldPos)
{
	// ������
	//coolTimer->Update(deltaTime.GetDeltaTime());
	//if (coolTimer->IsTimeout() &&
	//	trunkpoint >= 0)
	//{
	//	trunkpoint -= DECREMENT_TRUNKPOINT * deltaTime.GetDeltaTime();
	//}

	// ���݂��Ȃ��ꍇ�͉��̏����͂��Ȃ�
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
			stanTimer->IsTimeout();
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

	// �V�[���h�{�̂̓G�t�F�N�g�̂���
	// �`���EffectMgr���s��
}

void Shield::HitObject(CollisionTag tag)
{
	coolTimer->Reset();

	if (tag == CollisionTag::Enemy)
	{
		if (existTimer->IsTimeout())
		{
			trunkpoint += INCREMENT_TRUNKPOINT;
		}
		else
		{
			trunkpoint += INCREMENT_TRUNKPOINT / 2;
		}
	}
}
