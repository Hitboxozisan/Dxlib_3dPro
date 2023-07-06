#include "ActBulletShotGun.h"
#include "BossEnemy.h"

ActBulletShotGun::ActBulletShotGun(BossEnemy* inEnemy)
	:ActBase(inEnemy)
{
}

ActBulletShotGun::~ActBulletShotGun()
{
}

ActBase::State ActBulletShotGun::Run()
{
	if (enemy->AttackShotBullet(false))
	{
		return ActBase::State::Complete;
	}
	if (enemy->IsHit())
	{
		return ActBase::State::Failed;
	}

	return ActBase::State::Run;
}

bool ActBulletShotGun::IsExecutabel()
{
	return true;
}

bool ActBulletShotGun::IsContinue()
{
	return true;
}
